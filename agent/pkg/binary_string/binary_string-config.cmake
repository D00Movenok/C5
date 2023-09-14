# created from scratch
project(binary_string)

set(BINARY_STRING_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(BINARY_STRING_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(BINARY_STRING_TESTS_DIR ${CMAKE_CURRENT_LIST_DIR}/tests)

if(NOT TARGET ${PROJECT_NAME})
  add_library(${PROJECT_NAME} ${BINARY_STRING_SOURCE_DIR}/binary_string.c)

  target_include_directories(${PROJECT_NAME} PUBLIC ${BINARY_STRING_INCLUDE_DIR})

  #############################################
  # Unit tests
  #############################################

  find_package(Check REQUIRED)
  include_directories(${CHECK_INCLUDE_DIRS})
  link_directories(${CHECK_LIBRARY_DIRS})

  set(tests
    common
  )

  foreach (test IN LISTS tests)
    string(REPLACE "/" "_" test_sanitized ${test})

    add_executable(${test_sanitized} ${BINARY_STRING_TESTS_DIR}/${test}.c)
    target_link_libraries(${test_sanitized} ${PROJECT_NAME} ${CHECK_LIBRARIES})

    add_test(NAME ${PROJECT_NAME}/${test} COMMAND ${test_sanitized})
  endforeach()
endif()
