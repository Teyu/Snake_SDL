set(SNAKE_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/Food.cpp
  ${CMAKE_SOURCE_DIR}/src/Menu.cpp
  ${CMAKE_SOURCE_DIR}/src/Game.cpp
  ${CMAKE_SOURCE_DIR}/src/Player.cpp
  ${CMAKE_SOURCE_DIR}/src/Sprite.cpp
  ${CMAKE_SOURCE_DIR}/src/Snake.cpp
  ${CMAKE_SOURCE_DIR}/src/Framework.cpp
  ${CMAKE_SOURCE_DIR}/src/Timer.cpp
)

add_executable( Snake
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

include_directories( ${CMAKE_SOURCE_DIR}/inc )

add_library(SnakeCore STATIC
  ${SNAKE_SOURCE_FILES}
)

target_link_libraries(Snake
  SnakeCore
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(specifySDLpaths)

if(SNAKE_BUILD_TESTS)
  add_subdirectory(tests)
endif()
