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
        type |= PTYPE_TAG_NEWSESSION;
    } else {
        session = luaL_checkinteger(L, 3);
    }

    int mtype = lua_type(L, 4);
    switch(mtype) {
        case LUA_TSTRING: {
            size_t l = 0;
            void *msg = (void *)lua_tolstring(L, 4, &l);
            if (l == 0) {
                msg = NULL;
            }
            session = scnet2_send(context, 0, dest, type, session, msg, len);
            break;
        }
        case LUA_TLIGHTUSERDATA: {
            void *msg = lua_touserdata(L, 4);
            int sz = luaL_checkinteger(L, 5);
            session = scnet2_send(context, 0, dest, type | PTYPE_TAG_DONTCOPY, session, msg, sz);
            break;
        }
        default:
            luaL_error(L, "type not reconize");
    }
    if (session < 0) {
        luaL_error(L, "session < 0");
    } 
    lua_pushinteger(L, session);
    printf("There are %d elem in stack\n", lua_gettop(L));
    return 1;
}
