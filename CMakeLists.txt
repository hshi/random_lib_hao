cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(randomhao)

#For find module path
set(CMAKE_MODULE_PATH "${MODULE_EXTRA_PATH}" ${CMAKE_MODULE_PATH})

#For definitions
add_definitions(${COMPILER_EXTRA_DEF})

set(lib_all "")

#For sprng
add_definitions(-DPOINTER_SIZE=8)
find_package(sprng REQUIRED)
include_directories(${sprng_include_dirs})
set(lib_all ${lib_all} ${sprng_libraries})

#For GMP library
find_package(gmp REQUIRED)
set(lib_all ${lib_all} ${gmp_libraries})


include_directories(inc)

add_subdirectory(inc)

add_subdirectory(src)

add_subdirectory(test)

