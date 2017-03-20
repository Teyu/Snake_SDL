
message( "Adding test environment." )

include_directories(
  ${gmock_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/inc
)

add_executable(SnakeUnitTests
  ${CMAKE_SOURCE_DIR}/src/tests/FoodTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/GameTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/PlayerTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/SnakeTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/RigourSnakeTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/Sample.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/SpriteTest.cpp
)

# TODO: add executable SnakeSystemTest

target_link_libraries(SnakeUnitTests
  gtest
  gmock_main
  SnakeCore
  ${SDL_LIBRARY}
)

add_test(
  NAME SnakeUnitTests
  COMMAND SnakeUnitTests
)
