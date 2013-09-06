#include <base/thread.h>

static Proc *sendQueue = NULL;
static Proc *recvQueue = NULL;

MutexLock lock;

static Proc *getProc(lua_State *L) {
  Proc *p;
  lua_getfield(L, LUA_REGISTYINDEX, "__SELF");
  p = static_cast<Proc *>(lua_touserdata(L, -1));
  lua_pop(L, 1);
  return p;
}

static void movevalues(lua_State *from, lua_State *to) {
  int n = lua_gettop(from);
  int i = 2;
  for(; i <= n; i++) {
    lua_pushstring(to, lua_tostring(from, i));
  }
}

static Proc *searchQueue(const char *channel, Proc **list) {
  Proc *tmp = *list;
  if (*tmp == NULL)
    return NULL;
  do {
    if (strcmp(tmp->channel, channel) == 0) {
      if (tmp == *list) {
        *list = (tmp == tmp->next) ? NULL : tmp->next;
      }
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      return tmp;
    }
    tmp = tmp->next;
  }while(tmp != *list);
  return NULL;
}

static void waitOnQueue(lua_State *L, const char *channel, Proc **list) {
  Proc *p = getProc(L);
  if (*list == NULL) {
    *list = p;
    p->prev = p->next = p;
  } else {
    Proc *tmp = *list;
  //  for (; tmp != *list; tmp = tmp->next);
    p->prev = tmp->perv;
    p->next = tmp;
    tmp->next->perv = tmp->perv->next = p;
  }
  p->channel = channel;
  {
    MutexLockGuard guard(p->lock);
    do {
      // Wait for other thread to take out the p->channel
      p->cond.wait(); 
    } whild(p->channel);
  }
  return ;
}
static void register(lua_State *L, const char *name, lua_CFunction f) {
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "preload");
  lua_pushcfunction(L, f);
  lua_setfield(L, -2, name);// preload[name] = f
  lua_pop(L, 2);
}
static void openlib(lua_State *L) {
  //lua_cpcall(L, luaopen_base, NULL);
  lua_pushcfunction(L, luaopen_base);
  lua_pcall(L, 0, 0, 0);
  //lua_cpcall(L, luaopen_package, NULL);
  lua_pushcfunction(L, luaopen_package);
  lua_pcall(L, 0, 0, 0);

  register(L, "io", luaopen_io);
  register(L, "os", luaopen_os);
  register(L, "table", luaopen_table);
  register(L, "string", luaopen_string);
  register(L, "math", luaopen_math);
  register(L, "debug", luaopen_debug);
}
static void lthread(void *arg) {
  lua_State *L = static_cast<lua_State *>(arg);
  //  Proc *self = static_cast<Proc *>lua_newuserdata(L, sizeof(*self));
  //  self->thread = pthread_self();
  //  luaL_openlibs(L);
  openlib(L);
  //  lua_cpcall(L, luaopen_lscnet2, NULL);
  lua_pushcfunction(L, luaopen_lscnet2, 0)
  if (lua_pcall(L, 0, 0, 0) != 0)
    fprintf(stderr, "thread error: %s", lua_tostring(L, -1));
  lua_close(L);
  return NULL;
}

static int lsend(lua_State *L) {
  const char *channel = lua_checkstring(L, 1);
  Proc *p;
  {
    MutexLockGuard guard(gLock);
    p = searchQueue(channel, &recvQueue);
    if (p){
      movevalues(L, p->L);
      p->channel = NULL;
      p->cond.signal();
    } else {
      waitOnQueue(L, channel, &sendQueue);
    }
  }
  return 0;
}

static int lreceive(lua_State *L) {
  const char *channel = lua_checkstring(L, 1);
  Proc *p;
  {
    MutexLockGuard guard(gLock);
    p = searchQueue(channel, &sendQueue);
    if (p) {
      movevalues(p->L, L);
      p->channel = NULL;
      p->cond.signal();
    } else {
      waitOnQueue(L, channel, &recvQueue);
    }
  }

  return lua_gettop(L) - 1;
}

static int lexit(lua_State *L) {
  pthread_exit(NULL);
  return 0;
}
static void *lstart(lua_State *L) {
  const char *chunk = luaL_checkstring(L, 1);
  lua_State *newL = luaL_newstate();

  if (newL == NULL) {
    luaL_error(L, "unable to create state");
  }

  if (luaL_loadstring(newL, chunk) != 0) {
    luaL_error(L, "error starting threads: %s", lua_tostring(newL, -1));
  }

  Thread thread(lthread, newL);
  thread.start();
  //thread.detach();

  return 0;
}

int luaopen_lscnet2(lua_State *L) {
  luaL_reg lfuncs[] = {
    {"start", lstart},
    {"send", lsend},
    {"receive", lreceive},
    {"exit", lexit},
    {NULL, NULL}
  };
  Proc *self = static_cast<Proc *>lua_newuserdata(L, sizeof(*self));
  lua_setfield(L, LUA_REGISTRYINDEX, "__SELF");
  self->L = L;
  self->thread = pthread_self();
  self->channel = NULL;
  luaL_register(L, "lscnet2", lfuncs);
  return 1;
}
