cmake_minimum_required(VERSION 3.4)
project(genoFreq)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC -fopenmp -W -Wall -pedantic -O3 -oFast")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")


file(GLOB SOURCES 
"src/genoFreq.cpp"
"main.cpp"
)

include_directories(include)
include_directories(lib/parallel-hashmap)
include_directories(lib/gzstream)
add_executable(genoFreq ${SOURCES})
target_link_libraries(genoFreq z)