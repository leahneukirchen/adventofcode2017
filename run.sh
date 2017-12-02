#!/bin/sh -e

DAY=${1?which day}

: ${CXX:=g++}
: ${CXXFLAGS= -O2 -std=c++1z -g}
$CXX -Wall -Wextra $CXXFLAGS day$DAY.cc
./a.out <day$DAY
