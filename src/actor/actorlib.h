#ifndef SRC_ACTOR_ACTORLIB_H_
#define SRC_ACTOR_ACTORLIB_H_

struct Proc {
  lua_State *L;
  pthread_t thread;
  MutexLock lock;
  Condition cond;
  const char *channel;
  struct Proc *next, *prev;
};

#endif
