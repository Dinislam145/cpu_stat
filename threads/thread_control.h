#ifndef THREAD_CONTROL_H
#define THREAD_CONTROL_H

#include <pthread.h>
#include <stdatomic.h>

enum THREAD_STATE{
    INVALID = -1,
    RUNNING,
    STOPING,
    FAILED,
    FINISHED
};

struct thread_context {
    pthread_t thread;
    char name[32];
    void *arg;
    void *func;
    atomic_bool stop;
    enum THREAD_STATE state;
};

void init_thread_context(struct thread_context *target, char *name, void *arg, void *func);

void create_thread(struct thread_context *thread);

void stop_thread(struct thread_context *thread);

#endif // THREAD_CONTROL_H
