cmake_minimum_required(VERSION 2.8.7)
project(restorrente)

#sets compile flags
set(CMAKE_CXX_FLAGS "--coverage -fprofile-arcs -ftest-coverage -std=c++0x -O0 -ggdb -Wall -Werror -pedantic ${CMAKE_CXX_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "-lrt")

set (CMAKE_SHARED_LINKER_FLAGS "-lrt")

#adds the source and header files recursively
file(GLOB_RECURSE SOURCES "./*.cpp" "./*.c")
file(GLOB_RECURSE HEADERS "./*.h")

#adds directories with headers recursively
set(DIRS "")
foreach (_header ${HEADERS})
    get_filename_component(_dir ${_header} PATH)
    list(APPEND DIRS ${_dir})
endforeach ()
list(REMOVE_DUPLICATES DIRS)
include_directories(${DIRS})

add_executable(restorrente ${SOURCES} processes/Waiter.cpp processes/Waiter.h domain/Order.h utils/Semaphore.h utils/Semaphore.cpp OrdersQueue.cpp OrdersQueue.h Kitchen.cpp Kitchen.h WaitersQueue.cpp WaitersQueue.h DishesQueue.cpp DishesQueue.h)
set_target_properties(restorrente PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(restorrente)
