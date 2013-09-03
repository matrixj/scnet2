local c = require "scnet2.actor"
local session_id_coroutine = { }
local init_func = { }

local function init_all()
    local funcs = init_func
    init_func = nil
    for k, v in pairs(funcs) do
        v()
    end
end
local function init_template(start)
    init_all()
    init_func = { }
    start()
    init_all()
end
local function string_to_handle(addr)
    print(addr)
    return tonumber("0x"..string.sub(str, 2))
end

function scnet2.timeout(ti, func)
    local session = c.command("TIMEOUT", tostring(ti))
    assert(session)
    session = tonumber(session)
    local co = coroutine.create(func)
    assert(session_id_coroutine[session] == nil)
    session_id_coroutine[session] = co
end
function scnet2.start(start_func)
    c.callback(dispatch_message)
    assert(c.stat "trace")
    scnet2.timeout(0, function()
        init_template(start_func)
        scnet2.send(".launcher", "text", "")
    end)
end
function scnet2.launch(...)
    local addr = c.command("LAUNCH", table.concat({...}, " "))
    if addr then
        return string_to_handle(addr)
    end
end
function scnet2.call(addr, tp, ...)
    local p = proto[tp]
    local session = c.send(addr, p.id, nil, p.pack(...))
    return p.unpack(coroutine.yield("CALL", session))
end
function scnet2.newservice(name, ...)
    local p = table.concat({"snlua", name, ...}, " ")
    local handle = scnet2.call(".launcher", "text", p)
    if handle == "" then
        return nil
    else
        return string_to_handle(handle) 
    end
end
