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
    if(target == nullptr){
        return;
    }

    target->source_buf = nullptr;
    target->client = nullptr;
    target->mutex = nullptr;
    target->cond_wait = nullptr;
    target->ready_to_send = nullptr;
}

void udp_exchange_loop(struct thread_context *thread);

#endif // UDP_MONITOR_H
