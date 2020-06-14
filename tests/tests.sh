#!/bin/bash
TEST_DIR="$TESTS_DIR"
if [ "$TEST_DIR" == "" ]; then
    exit -1
fi

for i in $TEST_DIR/*; do
    if [ ! -d $i ]; then
        continue
    fi
    echo TEST: $i
    make -C $i test
done
