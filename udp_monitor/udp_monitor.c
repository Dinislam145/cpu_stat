#include <stdio.h>
#include <stdlib.h>

#include "udp_monitor.h"
#include "threads/thread_control.h"
#include "network/udp_sender.h"
#include "network/exchange/protocols.h"

void udp_exchange_loop(struct thread_context *thread){
  struct UdpExchangeArgs *arg = (struct UdpExchangeArgs*)(thread->arg);

  pthread_mutex_t *mutex = (pthread_mutex_t*)(arg->mutex);
  pthread_cond_t *cond_wait = (pthread_cond_t*)(arg->cond_wait);

  char *msg = NULL;
  while(!atomic_load(&thread->stop)){
    pthread_mutex_lock(mutex);
    while(*(arg->ready_to_send) != true){
      pthread_cond_wait(cond_wait, mutex);
    }
    free(msg);
    msg = pack_cpu_stat(arg->source_buf);
    int bytes_sent = send_msg(arg->client, msg, size_cpu_stat(arg->source_buf));
    *(arg->ready_to_send) = false;
    pthread_mutex_unlock(mutex);
  }

  thread->state = FINISHED;
}
