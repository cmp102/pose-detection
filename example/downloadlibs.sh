#!/bin/sh

BASEPATH=$(dirname $0)

LIBS="cpp_confparser"

cpp_confparser="https://github.com/cmp102/cpp_confparser.git"

mkdir -p $BASEPATH/libs

for LIB in $LIBS
do
	command='git clone $'$LIB' '$BASEPATH'/libs/'$LIB
	eval $command
done
