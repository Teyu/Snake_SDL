
message( "Adding test environment." )

include_directories(
  ${gmock_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/inc
)

set (UNIT_TEST_SRC
  ${CMAKE_SOURCE_DIR}/src/tests/FoodTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/MockGame.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/MockSnake.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/PlayerTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/CollisionTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/SnakeTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/RigourSnakeTest.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/SpriteTest.cpp
)

set (SYSTEM_TEST_SRC
  ${CMAKE_SOURCE_DIR}/src/tests/MockGame.cpp
  ${CMAKE_SOURCE_DIR}/src/tests/SystemTest.cpp
)

add_executable(SnakeUnitTests
  ${UNIT_TEST_SRC}
)

add_executable(SnakeSystemTest
  ${SYSTEM_TEST_SRC}
)

target_link_libraries(SnakeUnitTests
  gtest
  gmock_main
  SnakeCore
  ${SDL_LIBRARY}
)

target_link_libraries(SnakeSystemTest
  gtest
  gmock_main
  SnakeCore
  ${SDL_LIBRARY}
)

add_test(
  NAME SnakeUnitTests
  COMMAND SnakeUnitTests
)

add_test(
  NAME SnakeSystemTest
  COMMAND SnakeSystemTest
)
