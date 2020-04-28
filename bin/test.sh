#!/bin/bash
a="src/main.cpp"
g++ -std=c++17 $a -o main -I"include" -I"third-party/toolbox/"