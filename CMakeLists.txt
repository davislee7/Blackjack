cmake_minimum_required(VERSION 3.6)
project(blackjack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Card.cpp Card.h Deck.cpp Deck.h GameTime.cpp)
add_executable(blackjack ${SOURCE_FILES})