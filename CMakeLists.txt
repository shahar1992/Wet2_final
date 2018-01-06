cmake_minimum_required(VERSION 3.7)
project(Wet2_final)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        Gladiator.cpp Gladiator.h
        TrainingGroup.h TrainingGroup.cpp
        List.h
        SplayTree.h
        MinHeap.h MinHeap.cpp
        library2.h library2.cpp
        HashChains.h
        Colosseum.h Colosseum.cpp
        main2.cpp
        )
#set(SOURCE_FILES SplayTree_test.cpp SplayTree.h)
add_executable(Wet2_final ${SOURCE_FILES})