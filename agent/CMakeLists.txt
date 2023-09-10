cmake_minimum_required(VERSION 3.22)

project(agent)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-pointer-sign")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-incompatible-function-pointer-types")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(CMAKE_PREFIX_PATH pkg)

find_package(log REQUIRED)
find_package(protobuf-c REQUIRED)

add_executable(agent)

target_compile_definitions(agent PUBLIC LOGLEVEL_TRACE)

target_sources(agent PUBLIC
  ${CMAKE_SOURCE_DIR}/agent.c
)

target_link_libraries(agent log protobuf-c)
