cmake_minimum_required(VERSION 3.22)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-pointer-sign")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-incompatible-function-pointer-types")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(CMAKE_PREFIX_PATH pkg)

find_package(log REQUIRED)
find_package(protobuf-c REQUIRED)
find_package(crypto REQUIRED)
find_package(binary_string REQUIRED)

project(agent)

add_executable(${PROJECT_NAME})

target_compile_definitions(agent PUBLIC LOGLEVEL_TRACE)

target_sources(${PROJECT_NAME} PUBLIC
  ${CMAKE_SOURCE_DIR}/agent.c
)

target_link_libraries(${PROJECT_NAME}
  log
  protobuf-c
  crypto
  binary_string
)

enable_testing()

include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)
