cmake_minimum_required(VERSION 3.4)
project(genoFreq)


#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC -fopenmp -W -Wall -pedantic -O3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,-lboost_iostreams")

find_package(Boost REQUIRED COMPONENTS system filesystem)


file(GLOB SOURCES 
"src/genoFreq.cpp"
"main.cpp"
)


include_directories(include)

add_executable(genoFreq ${SOURCES})
target_link_libraries(genoFreq boost_iostreams)