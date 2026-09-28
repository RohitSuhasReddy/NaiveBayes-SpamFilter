cmake_minimum_required(VERSION 3.14)
project(MiniSpamFilter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/Document.cpp
    src/Vocabulary.cpp
    src/SimpleTokeniser.cpp
    src/StopWordTokeniser.cpp
    src/NGramTokeniser.cpp
    src/RegexTokeniser.cpp
    src/NaiveBayesClassifier.cpp
    src/Evaluator.cpp
    src/ModelIO.cpp
    src/main.cpp
)

add_executable(MiniSpamFilter ${SOURCES})

# Optional: install target
# install(TARGETS MiniSpamFilter DESTINATION bin)
