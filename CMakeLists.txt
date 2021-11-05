cmake_minimum_required(VERSION 3.21.2)

project(Dice)

add_executable(
    main
    src/main.cpp src/Dice.cpp src/Fibanachi.cpp src/Random.cpp src/DiceASCIIArt.cpp src/GameShell.cpp src/GameStates.cpp src/Player.cpp
)

file(COPY dice.txt DESTINATION .)
file(COPY game_hello.txt DESTINATION .)