cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(randomhao)

if(NOT DEFINED MPI_HAO)
else()
  add_definitions(-DMPI_HAO=${MPI_HAO})
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   set(CMAKE_CXX_FLAGS " ")
   set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++11 ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
endif()


set(lib_all "")

# For Sprng library
add_definitions(-DPOINTER_SIZE=8)
find_library(sprng_lib NAMES libsprng.a PATHS /home/boruoshihao/sprng/sprng2.0/lib)
set(lib_all ${lib_all} ${sprng_lib})
string(REPLACE "lib/libsprng.a" "include" sprng_include ${sprng_lib})
include_directories(${sprng_include})

#For GMP library
find_library(gmp_lib NAMES libgmp.a PATHS /opt/gmp/lib/)
set(lib_all ${lib_all} ${gmp_lib})


include_directories(inc)

add_subdirectory(inc)

add_subdirectory(src)

add_subdirectory(test)

