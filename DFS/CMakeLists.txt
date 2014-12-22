project(dfs)
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -g -std=c++11 -Wall")

add_executable( dfs_testing 
	       	test.cpp 
	       	graph/graph.cpp 
		graph/graph.h 
		gtest/gtest-all.cc 
		gtest/gtest.h 
		gtest/gtest_main.cc)
target_link_libraries(dfs_testing -lgmp -lgmpxx -lpthread ${Boost_LIBRARIES})
