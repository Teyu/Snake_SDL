
message( "Adding test environment." )

include_directories(
  ${gmock_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/inc
)

add_executable(SnakeUnitTests
  ${CMAKE_SOURCE_DIR}/src/tests/FoodTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/SnakeTest.cpp
)

target_link_libraries(SnakeUnitTests
  gtest
  gmock_main
  SnakeCore
)

add_test(
  NAME SnakeUnitTests
  COMMAND SnakeUnitTests
)
