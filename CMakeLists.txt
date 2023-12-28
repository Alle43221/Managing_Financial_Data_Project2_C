cmake_minimum_required(VERSION 3.23)
project(Managing_Financial_Data_Project2_C C)

set(CMAKE_C_STANDARD 99)
include_directories("./validation.h")

add_executable(Managing_Financial_Data_Project2_C main.c validation.c)
