cmake_minimum_required(VERSION 3.0)

project(test.out)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES 
	src/Main.cpp
	src/SharedMemory.cpp
)

#include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})

# find_package(Boost REQUIRED)
# target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

#if (CMAKE_COMPILER_IS_GNUCC)
#	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
#elseif (MSVC)
#	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
#endif()

