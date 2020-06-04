#!/bin/bash
if [ $# -eq 1 ]
then
    test_name=$1
else
    test_name="test.cpp"
fi
echo "Compiling $test_name"
g++ -std=c++17 -DTEST -g -o ${test_name%.*} $test_name $(pkg-config --env-only --cflags --libs isl)
