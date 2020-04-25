#!/bin/bash
# Generated using BSHA - Build .sh assembler for C+
# GitHub: https://github.com/AlexeyFilich/toolbox/tree/master/bsha

if [ "$1" == "--full" ] || [ "$1" == "-f" ]; then
    rm -rf build
fi

[ ! -d build ] && mkdir build
[ ! -d build/sources ] && mkdir build/sources

printf -- "\e[1;32m-- \e[1;4;32mStarting build process\e[0m\n"

printf -- "\e[1;32m-- Compiler: \e[1;4;93mg++\e[0m\n"

printf -- "\e[1;32m-- Global flags: \e[1;97m-std=c++17 \e[0m\n"

printf -- "\e[1;32m-- Include path:\n"
printf -- "\e[1;32m[1] \e[1;97minclude/"
printf -- "\e[0m\n"

printf -- "\e[1;32m-- Library path:\n"
printf -- "\e[0m\n"

printf -- "\e[1;32m-- Building \e[1;4;97mtest/main.cpp\e[0m\n"
[ -f build/main.out ] && rm build/main.out
g++ -I"include/" -std=c++17 -o build/main.out test/main.cpp 
if [ ! -f build/main.out ]
then
    echo > build/sources/test/main.hash
    printf -- "\e[1;91m-- Compilation failed!\e[0m\n"
    exit 1
fi


mv build/main.out bin/main
