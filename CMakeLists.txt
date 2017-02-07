cmake_minimum_required(VERSION 3.6)
project(DeltaTerminal)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static")

set(CMAKE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Sources")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/bin")
message(STATUS ${CMAKE_MODULE_PATH})

set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/sfml-2.4.1")
set(CEREAL_ROOT "${CMAKE_CURRENT_LIST_DIR}/Cereal-1.2.1")

find_package(SFML REQUIRED
		audio
		graphics
		window
		system
		network
		)

message(STATUS "SFML Dependencies : " ${SFML_DEPENDENCIES})
message(STATUS "SFML LIBRARIES : " ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR} ${CEREAL_ROOT})
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/*.[ch]pp)

add_executable(DeltaTerminal ${SOURCE_FILES})
target_link_libraries(DeltaTerminal ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})