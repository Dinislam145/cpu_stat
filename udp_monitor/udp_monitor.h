#ifndef UDP_MONITOR_H
#define UDP_MONITOR_H

struct thread_context;
struct UdpClient;
struct cpu_stat_protocol;

struct UdpExchangeArgs{
    struct cpu_stat_protocol *source_buf;
    struct UdpClient *client;
    void *mutex;
    void *cond_wait;
    bool *ready_to_send;
};

static inline void init_udp_exchange_args(struct UdpExchangeArgs *target){
    if(target == NULL){
        return;
    }

    target->source_buf = NULL;
    target->client = NULL;
    target->mutex = NULL;
    target->cond_wait = NULL;
    target->ready_to_send = NULL;
}

void udp_exchange_loop(struct thread_context *thread);

#endif // UDP_MONITOR_H
