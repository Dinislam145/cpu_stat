#ifndef UDP_SENDER_H
#define UDP_SENDER_H

#include <netinet/in.h>

struct UdpClient{
    int socket_d;
    struct sockaddr_in server_info;
};

bool init_udp_client(struct UdpClient *target);
void close_udp_client(struct UdpClient *target);

int send_msg(struct UdpClient *client, const char *msg, int msg_len);

#endif // UDP_SENDER_H
