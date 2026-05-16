#ifndef STAT_PARSER_H
#define STAT_PARSER_H

#include <stdint.h>

struct CoreStat{

};

///
/// \brief Структура статистики ЦПУ
///
struct CpuStat{
    int8_t cores_count;
    struct CoreStat cores_stat[50];
};

void init_cpu_stat(struct CpuStat *target);

///
/// \brief Вариант функции для передачи пути к любому файлу
/// \param path - путь к файлу
///
void stat_parser(const char *path);

#endif // STAT_PARSER_H
