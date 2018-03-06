cmake_minimum_required (VERSION 2.6)


project (rational)

set(CMAKE_CXX_FLAGS "-std=c++1z")

add_executable(rational 
	main.cpp
	rational.cpp)