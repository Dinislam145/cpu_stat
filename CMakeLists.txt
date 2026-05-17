cmake_minimum_required(VERSION 3.16)

project(cpu_stat LANGUAGES C)

add_executable(cpu_stat main.c
    parser/stat_parser.h parser/stat_parser.c
    cpu_monitor/monitor.h cpu_monitor/monitor.c
    threads/thread_control.h threads/thread_control.c)

include(GNUInstallDirs)
install(TARGETS cpu_stat
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(cpu_stat PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
