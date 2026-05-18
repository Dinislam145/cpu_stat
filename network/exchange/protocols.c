#include "protocols.h"

#include <endian.h>
#include <stdlib.h>

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

char *pack_cpu_stat(const struct cpu_stat_protocol *stat){
  if(!stat){
    return nullptr;
  }

  size_t total_size = size_cpu_stat(stat);

  char *msg = malloc(total_size);
  if(!msg){
    return nullptr;
  }

  //.....

  return msg;
}
