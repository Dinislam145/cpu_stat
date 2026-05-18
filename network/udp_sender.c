#include "udp_sender.h"

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

bool init_udp_client(struct UdpClient *target, int port, const char *addr){
  if(target == nullptr){
      return false;
  }

  target->socket_d = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&target->server_info, 0, sizeof(target->server_info));

  target->server_info.sin_family = AF_INET;
  target->server_info.sin_port = port;
  target->server_info.sin_addr.s_addr = inet_addr(addr);

  if(target->socket_d < 0){
      return false;
  }

  return true;
}

void close_udp_client(struct UdpClient *target){
  if(target == nullptr){
      return;
  }

  close(target->socket_d);
}

int send_msg(struct UdpClient *client, const char *msg, int msg_len){
  if(client == nullptr){
      return -1;
  }

  int bytes_sent = sendto(client->socket_d, msg, msg_len, 0, (struct sockaddr*)(&client->server_info), sizeof(client->server_info));

  if(bytes_sent < 0){
    close_udp_client(client);
  }

  return bytes_sent;
}
