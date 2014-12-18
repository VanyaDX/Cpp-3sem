cmake_minimum_required(VERSION 2.8.4)
project(POKER)
INCLUDE_DIRECTORIES(${POKER_SOURCE_DIR})

add_executable(testing_poker
	poker_testing.cpp
	game_help.cpp 
	include/player.h
	include/holdem_poker.h 
	src/holdem_poker.cpp
	include/cards.h 
	src/cards.cpp
	include/player_man.h 
	src/player_man.cpp
	include/table.h 
	src/table.cpp
	include/textui.h
	src/textui.cpp
	gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc
)

add_executable(holdem_poker
	main.cpp 
	game_help.cpp
	include/player.h
	include/holdem_poker.h 
	src/holdem_poker.cpp
	include/cards.h 
	src/cards.cpp
	include/player_man.h 
	src/player_man.cpp
	include/table.h 
	src/table.cpp
	include/textui.h
	src/textui.cpp
)



  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -std=c++0x")


target_link_libraries(holdem_poker)
target_link_libraries(testing_poker -lgmp -lgmpxx -lpthread)
