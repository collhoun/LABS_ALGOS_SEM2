cmake_minimum_required(VERSION 3.14)
project(Lab5 CXX C)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для MinGW на Windows - включаем поддержку Pthreads
if(MINGW)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()

# Find threading library
find_package(Threads REQUIRED)

# 1. Подключаем модуль для скачивания контента
include(FetchContent)

# 2. Описываем, откуда брать gtest и google benchmark
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.8.1.zip
)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.7.1
)

# Для Windows: предотвращаем конфликт с настройками среды выполнения (очень важно!)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Отключаем проблемные опции для MinGW
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_LTO OFF CACHE BOOL "" FORCE)

# Для MinGW отключаем regex
if(MINGW)
  set(HAVE_STD_REGEX OFF CACHE BOOL "" FORCE)
  set(HAVE_GNU_POSIX_REGEX OFF CACHE BOOL "" FORCE) 
  set(HAVE_POSIX_REGEX OFF CACHE BOOL "" FORCE)
endif()

# 3. Делаем библиотеки доступной
FetchContent_MakeAvailable(googletest googlebenchmark)

# 4. Создаем ваш исполняемый файл с тестами
add_executable(my_tests tests/test.cpp src/graph.c src/edge_array.c)

# 5. Создаем исполняемый файл для simple_benchmark
add_executable(simple_benchmark src/simple_benchmark.cpp src/graph.c src/edge_array.c)

# 5. Связываем ваш проект с библиотеками gtest
# gtest_main — это готовая точка входа (не нужно писать main() самому)
target_link_libraries(my_tests gtest_main Threads::Threads)

# 6. Связываем бенчмарки с библиотекой benchmark
target_link_libraries(simple_benchmark benchmark::benchmark Threads::Threads)

# 7. Включаем поддержку тестов в CMake
include(GoogleTest)
gtest_discover_tests(my_tests)