#include <stdio.h>

#include "parser/stat_parser.h"

int main()
{
    printf("Hello World!\n");

    stat_parser("/proc/stat");

    return 0;
}
