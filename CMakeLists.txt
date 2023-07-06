cmake_minimum_required(VERSION 3.15.0)

project(lrnx VERSION 0.1 LANGUAGES C)

file(GLOB SOURCES "core/*.c" "core/*/*.c" "sdl/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC core core/accessories core/datamanager core/interpreter core/libraries core/machine core/overlay sdl)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} SDL2::Main)

if(NOT MSVC)
	target_link_libraries(${PROJECT_NAME} m)
endif()
