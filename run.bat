@echo off
cd /d "%~dp0"

if not exist build mkdir build

echo [33mBuilding MiniSpamFilter...[0m
g++ -std=c++11 -I include -o build\MiniSpamFilter.exe src\Document.cpp src\Vocabulary.cpp src\SimpleTokeniser.cpp src\StopWordTokeniser.cpp src\NaiveBayesClassifier.cpp src\Evaluator.cpp src\main.cpp
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo.
echo [33mRunning...[0m
echo.
build\MiniSpamFilter.exe data\train.csv data\test.csv %*
