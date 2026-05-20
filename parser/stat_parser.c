#include "stat_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void debug_core_stat(const struct CoreStat *stat){
  printf("\tuser: %lu\n", stat->user);
  printf("\tnice: %lu\n", stat->nice);
  printf("\tsystem: %lu\n", stat->system);
  printf("\tidle: %lu\n", stat->idle);
  printf("\tiowait: %lu\n", stat->iowait);
  printf("\tirq: %lu\n", stat->irq);
  printf("\tsoftirq: %lu\n", stat->softirq);
  printf("\tsteal: %lu\n", stat->steal);
  printf("\tguest: %lu\n", stat->guest);
  printf("\tguest_nice: %lu\n", stat->guest_nice);
}

void init_cpu_stat(struct CpuStat *target){
    target->cores_count = 0;
}

void debug_cpu_stat(const struct CpuStat *stat){
  printf("Cores: %d\n", stat->cores_count);

  for(int i = 0; i < stat->cores_count + 1; i++){
    printf("Core: %d\n", i);
    debug_core_stat(&(stat->cores_stat[i]));
  }

  printf("\n");
  fflush(stdout);
}

///
/// \brief Сереализовать параметры загрузки ЦПУ в структуру
/// \param target
/// \param str
///
void parse_cpu_values(struct CoreStat *target, char *str){
  target->user = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->nice = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->system = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->idle = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->iowait = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->irq = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->softirq = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->steal = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->guest = strtoull(strtok(NULL, " \t\n"), NULL, 10);
  target->guest_nice = strtoull(strtok(NULL, " \t\n"), NULL, 10);
}

void stat_parser(const char *path, struct CpuStat *target){
  //struct CpuStat res;
  //init_cpu_stat(&res);

  if(target == NULL){
    return;
  }

  FILE *file = fopen(path, "r");
  char *line = NULL;
  size_t len = 0;
  size_t read = 0;

  while((read = getline(&line, &len, file)) != -1){
    if(strncmp(line, "cpu", 3) == 0){ // Только статистика ЦПУ
      char *token = strtok(line, " \t\n");
      if(strcmp(token, "cpu")){
        target->cores_count++;
      }

      parse_cpu_values(&(target->cores_stat[target->cores_count]), line);
    }
  }

  fclose(file);
}
