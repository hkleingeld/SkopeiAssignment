#!/bin/bash

if [ ! -f $1 ]; then
    echo "Could not find binary! Check if your program compiles!"
    exit -1;
fi
test_binary="$1"

secret=$(dd if=/dev/urandom bs=1 count=10 2>/dev/null)
check=$(./$test_binary "$secret")

if [ "$secret" == "$check" ]; then
    echo "Success! Commit your changes onto a solution branch and push them"
else 
    echo "Not successful! Change src/editme.c and/or include/editme.h"
fi
