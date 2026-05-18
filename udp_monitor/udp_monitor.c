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

  while(!atomic_load(&thread->stop)){
    pthread_mutex_lock(mutex);
    while(*(arg->ready_to_send) != true){
      printf("Waiting!\n");
      //fflush(stdout);
      pthread_cond_wait(cond_wait, mutex);
    }
    char *msg = pack_cpu_stat(arg->source_buf);
    int bytes_sent = send_msg(arg->client, msg, size_cpu_stat(arg->source_buf));
    *(arg->ready_to_send) = false;
    pthread_mutex_unlock(mutex);
    free(msg);

    printf("Sent %d bytes!\n", bytes_sent);
    fflush(stdout);
  }

  thread->state = FINISHED;
}
