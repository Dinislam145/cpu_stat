cmake_minimum_required(VERSION 3.16)

project(cpu_stat LANGUAGES C)

add_executable(cpu_stat main.c
    parser/stat_parser.h parser/stat_parser.c)

include(GNUInstallDirs)
install(TARGETS cpu_stat
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
