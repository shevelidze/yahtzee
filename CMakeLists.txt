cmake_minimum_required(VERSION 3.20.2)

project(Dice)


file(GLOB helloworld_SRC
     "src/*.cpp"
)

add_executable(
    main
    ${helloworld_SRC}
)

file(COPY dice.txt DESTINATION .)
file(COPY game_hello.txt DESTINATION .)