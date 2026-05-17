#include "udp_monitor.h"

#include "threads/thread_control.h"
#include "network/udp_sender.h"

void udp_exchange_args(struct thread_context *thread){
  struct UdpClient *arg = (struct UdpClient*)(thread->arg);

  while(!atomic_load(&thread->stop)){

  }

  thread->state = FINISHED;
}
