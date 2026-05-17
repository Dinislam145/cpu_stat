#ifndef UDP_MONITOR_H
#define UDP_MONITOR_H

struct thread_context;
struct UdpClient;

struct UdpExchangeArgs{
    char *source_buf;
    struct UdpClient *client;
};

static inline void init_udp_client_args(struct UdpExchangeArgs *target){
    if(target == nullptr){
        return;
    }

    target->source_buf = nullptr;
    target->client = nullptr;
}

void udp_exchange_args(struct thread_context *thread);

#endif // UDP_MONITOR_H
