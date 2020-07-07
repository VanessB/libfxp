# Минимальная версия CMake.
cmake_minimum_required(VERSION 3.7.2)

# Проект.
project(FXP)

# Директория заголовочных файлов.
include_directories(include)
#include_directories(include/fxp)

# Файлы исходного кода.
file(GLOB_RECURSE SOURCES "source/*.c") # - Automatically.

add_executable(FXP ${SOURCES}) # Using variable SOURCES.

# Флаги
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -O0 -g3 -ggdb --std=c11")
# set(CMAKE_C_FLAGS_SANITIZE "${CMAKE_C_FLAGS_SANITIZE} -Wall -Wextra -Wpedantic -O3 -fsanitize=undefined --std=c11")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wextra -Wpedantic -Winline -O3 --std=c11")

# Библиотеки
target_link_libraries(FXP m)
