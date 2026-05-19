#include "protocols.h"

#include <endian.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *pack_core_stat(char *msg, const struct core_stat_protocol *stat){
  if(!msg || !stat){
    return nullptr;
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

  return (char *)(ptr[10]);
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
    fill_ptr = pack_core_stat(fill_ptr, &(stat->cores_stat[i]));
    //fill_ptr += size_core_stat(nullptr);
  }

  return msg;
}
