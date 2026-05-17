#include "thread_control.h"
#include <string.h>

void init_thread_context(struct thread_context *target, char *name, void *arg, void *func){
  strncpy(target->name, name, sizeof(target->name));
  target->arg = arg;
  target->func = func;
  atomic_store(&target->stop, false);
  target->state = INVALID;
}

void create_thread(struct thread_context *thread){
  if(thread == NULL || thread->state == RUNNING){
    return;
  }

  if(pthread_create(&thread->thread, NULL, thread->func, thread) != 0){
    thread->state = FAILED;
    return;
  }

  thread->state = RUNNING;
}

void stop_thread(struct thread_context *thread){
  if(thread == NULL || thread->state != RUNNING){
    return;
  }

  atomic_store(&thread->stop, true);
}
