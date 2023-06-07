cmake_minimum_required(VERSION 3.10)

project(cppcode)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(snake Fruit.cpp Game.cpp GameScreen.cpp Grid.cpp GameOverScreen.cpp main.cpp Screen.cpp MenuScreen.cpp Snake.cpp SnakeNode.cpp)


target_include_directories(snake PRIVATE ${CMAKE_SOURCE_DIR}/3rd/include)

target_link_directories(snake PRIVATE ${CMAKE_SOURCE_DIR}/3rd/lib)

target_link_libraries(snake PRIVATE sfml-audio sfml-graphics sfml-main sfml-network sfml-window sfml-system)