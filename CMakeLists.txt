cmake_minimum_required(VERSION 3.16)
project(MiniSpamFilter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MiniSpamFilter
    src/Document.cpp
    src/Vocabulary.cpp
    src/SimpleTokeniser.cpp
    src/StopWordTokeniser.cpp
    src/NaiveBayesClassifier.cpp
    src/Evaluator.cpp
    src/main.cpp
)

target_include_directories(MiniSpamFilter PRIVATE include)
