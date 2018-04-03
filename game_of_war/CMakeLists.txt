cmake_minimum_required (VERSION 2.6)

project(war CXX)

set(CMAKE_CXX_FLAGS "-std=c++1z")

set(SOURCES 
	main.cpp 
	bitCard.hpp
	bitCard.cpp)
	
add_executable(war ${SOURCES})
