#!/bin/sh

files="$files `find python -name '*.py'`"
files="$files `find src -name '*.cpp'`"
files="$files `find src -name '*.h'`"

cat $files | wc -l

