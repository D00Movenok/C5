# created from scratch
project(log)

set(LOG_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(LOG_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

if(NOT TARGET ${PROJECT_NAME})
  add_library(${PROJECT_NAME} ${LOG_SOURCE_DIR}/log.c)

  target_include_directories(${PROJECT_NAME} PUBLIC ${LOG_INCLUDE_DIR})
endif()
