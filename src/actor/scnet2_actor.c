#include <lua.h>
#include <xlaulib.h>

static int lsend(lua_State *L)
{
    struct scnet2_context *context = lua_touserdata(L, lua_upvalueindex(1));
    int type = lua_type(L, 1);
    uint32_t dest = 0;
    switch(type) {
        case LUA_TNUMBER:
        dest = lua_tounsigned(L, 1);
        bread;
        case LUA_TSTRING: {
            const char *addr = lua_tostring(L, 1);
            if (addr[0] == '.' || addr[0] == ':') {
                dest = scnet2_queryname(context, addr);
                if (dext == 0) {
                    luaL_error(L, "Invale name");
                }
            } else if (isdigit(addr[0])) {
                luaL_error(L, "Can not start with a digit %s", addr);
            } else {
                return _sendname(L, context, addr);
            }
            break;
        }
        default:
        return luaL_error(L, "Unknown addr");
    }

    int type = luaL_checkinteger(L, 2);
    int session = 0;
    if (lua_isnil(L, 3)) {
        type |= 
    }
}
