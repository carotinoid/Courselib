cmake_minimum_required(VERSION 3.10)

project(Assn5)

# Add the source files in the order specified in task.json
set(SOURCES
    Bird.cpp
    BirdNode.cpp
    BirdList.cpp
    Duck.cpp
    AssassinDuck.cpp
    Goose.cpp
    DetectiveGoose.cpp
    MorticianGoose.cpp
    DodoBird.cpp
    Falcon.cpp
    GGD.cpp
    main.cpp
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})