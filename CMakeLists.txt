cmake_minimum_required(VERSION 3.22)
project(wordle_guesser)

set(CMAKE_CXX_STANDARD 23)

add_executable(wordle_guesser main.cpp App.cpp App.h constants.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(wordle_guesser sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
