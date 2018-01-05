cmake_minimum_required(VERSION 3.7)
project(Wet2_final)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        Gladiator.cpp Gladiator.h
        TrainingGroup.cpp TrainingGroup.h
        List.h
        SplayTree.h
        MinHeap.h MinHeap.cpp
        library2.h
        HashChains.h SplayTree_test.cpp
        )
add_executable(Wet2_final ${SOURCE_FILES})