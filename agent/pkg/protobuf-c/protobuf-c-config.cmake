# taken from here https://github.com/protobuf-c/protobuf-c
project(protobuf-c)

set(PROTOBUFC_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(PROTOBUFC_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

if(NOT TARGET ${PROJECT_NAME})
  add_library(${PROJECT_NAME} ${PROTOBUFC_SOURCE_DIR}/protobuf-c.c)

  target_include_directories(${PROJECT_NAME} PUBLIC ${PROTOBUFC_INCLUDE_DIR})
endif()
