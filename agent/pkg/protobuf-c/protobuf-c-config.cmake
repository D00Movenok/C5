# taken from here https://github.com/protobuf-c/protobuf-c
project(protobuf-c)

set(PROTOBUFC_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(PROTOBUFC_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

if(NOT TARGET protobuf-c)
  add_library(protobuf-c ${PROTOBUFC_SOURCE_DIR}/protobuf-c.c)

  target_include_directories(protobuf-c PUBLIC ${PROTOBUFC_INCLUDE_DIR})
endif()
