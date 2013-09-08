#include "scnet2_actor.h"
#include "scnet2_scheduler.h"

sturct actor *actor_new(lua_State *L, const char *file) {
    luaL_requiref(L, "actor.c.socket", socket_lib, 0);
    lua_pop(L, 1);

    env_getenv(L, "actor_map");
    int actor_map = lua_absindex(L, -1);

    luaL_requiref(L, "actor.c", actor_lib, 0)
    struct actor *a = actor_create();
    c->L = L;
    actor_touserdata(L, actor_map, a);// ?

    lua_setfield(L, -2, "self");

    env_getenv(L, "system_pointer");
    struct actor *sys = lua_touserdata(L, -1);
    lua_pop(L, 1);

    if (sys) {
        actor_touserdata(L, actor_map, sys);
        lua_setfield(L, -2, "system");
    }

    lua_pop(L, 2);
    lua_pushlightuserdata(L, a);
    env_setenv(L, "actor_pointer");

    int error = luaL_loadfile(L, file);
    if (error) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        goto err_goto;
    }

    error = lua_pcall(L, 0, 0, 0);
    if (error) {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        goto err_goto;
    } 

    lua_pushcfunction(L, traceback);
    lua_pushcfunction(L, data_unpack);
    env_getenv(L, "dispatcher");
    if (!lua_isfunction(L, -1)) {
        sprintf(stderr, "dispatch is not a function:%s\n", lua_tostring(L, -1));
        goto err_goto;
    }
    env_getenv(L, "actor_map");
    lua_pushlightuserdata(L, a);
    lua_pushcclosure(L, lcallback, 5);
    return a;

}
