cmake_minimum_required(VERSION 3.12)
project(ProjetoSO C)

set(CMAKE_C_STANDARD 99)

add_executable(ProjetoSO Monitor.c Header.h util.c Simulator.c)