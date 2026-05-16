#include "stat_parser.h"

#include <stdio.h>
#include <string.h>

void init_cpu_stat(struct CpuStat *target){
    target->cores_count = 0;
}

void stat_parser(const char *path){
  struct CpuStat res;
  init_cpu_stat(&res);

  FILE *file = fopen(path, "r");
  char *line = NULL;
  size_t len = 0;
  size_t read = 0;

  while((read = getline(&line, &len, file)) != -1){
    if(strncmp(line, "cpu", 3) == 0){ // Только статистика ЦПУ
      res.cores_count++;
      printf("%s", line);
    }
  }
}
