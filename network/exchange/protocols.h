#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <stdint.h>
#include <stddef.h>

struct core_stat_protocol{
    uint64_t user;
    uint64_t nice;
    uint64_t system;
    uint64_t idle;
    uint64_t iowait;
    uint64_t irq;
    uint64_t softirq;
    uint64_t steal;
    uint64_t guest;
    uint64_t guest_nice;
};

static inline size_t size_core_stat(const struct core_stat_protocol *prot){
    return 10 * sizeof(uint64_t);
}

void pack_core_stat(char *msg, const struct core_stat_protocol *stat);
void unpack_core_stat(const char *msg, struct core_stat_protocol *stat);


struct cpu_stat_protocol{
    uint16_t cores_count;
    struct core_stat_protocol *cores_stat;
};

static inline void init_cpu_stat_protocol(struct cpu_stat_protocol *prot){
    prot->cores_stat = NULL;
    prot->cores_count = 0;
}

static inline size_t size_cpu_stat(const struct cpu_stat_protocol *prot){
    if(!prot){
        return 0;
    }

    return sizeof(prot->cores_count) + (1 + prot->cores_count) * size_core_stat(NULL);
}

char *pack_cpu_stat(const struct cpu_stat_protocol *stat);
void unpack_cpu_stat(const char *msg, struct cpu_stat_protocol *stat);

#endif // PROTOCOLS_H
