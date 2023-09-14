# created from scratch
find_package(binary_string REQUIRED)

project(crypto)

set(CRYPTO_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(CRYPTO_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(CRYPTO_TESTS_DIR ${CMAKE_CURRENT_LIST_DIR}/tests)

if(NOT TARGET ${PROJECT_NAME})
  add_library(${PROJECT_NAME}
    ${CRYPTO_SOURCE_DIR}/cipher/common.c
    ${CRYPTO_SOURCE_DIR}/cipher/aes.c
    ${CRYPTO_SOURCE_DIR}/modes/cbc.c
    ${CRYPTO_SOURCE_DIR}/padding/pkcs7.c
  )

  target_include_directories(${PROJECT_NAME} PUBLIC ${CRYPTO_INCLUDE_DIR})

  target_link_libraries(${PROJECT_NAME} binary_string)

  #############################################
  # Unit tests
  #############################################

  find_package(Check REQUIRED)
  include_directories(${CHECK_INCLUDE_DIRS})
  link_directories(${CHECK_LIBRARY_DIRS})

  set(tests
    cipher/aes
    modes/cbc
    padding/pkcs7
  )

  foreach (test IN LISTS tests)
    string(REPLACE "/" "_" test_sanitized ${test})

    add_executable(${test_sanitized} ${CRYPTO_TESTS_DIR}/${test}.c)
    target_link_libraries(${test_sanitized}
      ${PROJECT_NAME}
      ${CHECK_LIBRARIES}
      binary_string
    )

    add_test(NAME ${PROJECT_NAME}/${test} COMMAND ${test_sanitized})
  endforeach()
endif()
