#include "protocols.h"

#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void pack_core_stat(char *msg, const struct core_stat_protocol *stat){
  if(!msg || !stat){
    return;
  }

  uint64_t *ptr = (uint64_t*)msg;

  ptr[0] = htobe64(stat->user);
  ptr[1] = htobe64(stat->nice);
  ptr[2] = htobe64(stat->system);
  ptr[3] = htobe64(stat->idle);
  ptr[4] = htobe64(stat->iowait);
  ptr[5] = htobe64(stat->irq);
  ptr[6] = htobe64(stat->softirq);
  ptr[7] = htobe64(stat->steal);
  ptr[8] = htobe64(stat->guest);
  ptr[9] = htobe64(stat->guest_nice);
}

void unpack_core_stat(const char *msg, struct core_stat_protocol *stat){
  if(!msg || !stat){
    return;
  }

  const uint64_t *ptr = (const uint64_t*)msg;

  stat->user       = be64toh(ptr[0]);
  stat->nice       = be64toh(ptr[1]);
  stat->system     = be64toh(ptr[2]);
  stat->idle       = be64toh(ptr[3]);
  stat->iowait     = be64toh(ptr[4]);
  stat->irq        = be64toh(ptr[5]);
  stat->softirq    = be64toh(ptr[6]);
  stat->steal      = be64toh(ptr[7]);
  stat->guest      = be64toh(ptr[8]);
  stat->guest_nice = be64toh(ptr[9]);
}

char *pack_cpu_stat(const struct cpu_stat_protocol *stat){
  if(!stat){
    return nullptr;
  }

  size_t total_size = size_cpu_stat(stat);

  char *msg = malloc(total_size);
  char *fill_ptr = msg;
  if(!msg){
    return nullptr;
  }

  {
    uint16_t net_val = htobe16(stat->cores_count);
    memcpy(fill_ptr, &net_val, sizeof(net_val));
    fill_ptr += sizeof(net_val);
  }

  for(int i = 0; i <= stat->cores_count; i++){
    pack_core_stat(fill_ptr, &(stat->cores_stat[i]));
    fill_ptr += size_core_stat(nullptr);
  }

  return msg;
}

void unpack_cpu_stat(const char *msg, struct cpu_stat_protocol *stat){
  if(!msg || !stat){
    return;
  }

  const char *ptr = msg;

  uint16_t net_val;
  memcpy(&net_val, ptr, sizeof(net_val));
  ptr += sizeof(net_val);
  stat->cores_count = be16toh(net_val);
  stat->cores_stat = malloc((1 + stat->cores_count) * sizeof(struct core_stat_protocol));

  for(int i = 0; i <= stat->cores_count; i++){
      unpack_core_stat(ptr, &(stat->cores_stat[i]));
      ptr += size_core_stat(nullptr);
  }
}
