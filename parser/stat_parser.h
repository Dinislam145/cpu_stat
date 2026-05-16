#ifndef STAT_PARSER_H
#define STAT_PARSER_H

#include <stdint.h>

///
/// \brief Структурка для статистики ядра
///
struct CoreStat{
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

void debug_core_stat(const struct CoreStat *stat);

///
/// \brief Структура статистики ЦПУ
///
struct CpuStat{
    int8_t cores_count; ///< Физическое количество ядер (без общей статистики)
    struct CoreStat cores_stat[50]; ///< Массив структурок статистички ядер (размер равен cores_count + 1)
};

void init_cpu_stat(struct CpuStat *target);

void debug_cpu_stat(const struct CpuStat *stat);

///
/// \brief Вариант функции для передачи пути к любому файлу
/// \param path - путь к файлу
///
void stat_parser(const char *path);

#endif // STAT_PARSER_H
