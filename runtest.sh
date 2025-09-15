#!/bin/bash
INPUT_FILE=$1
PROGRAM=$2

TEST_NAME=$(basename "$INPUT_FILE" .in)
EXPECTED_FILE="${INPUT_FILE%.in}.out"

RESULT=$("$PROGRAM" < "$INPUT_FILE")
EXPECTED=$(cat "EXPECTED_FILE")

if [ "$RESULT" == "$EXPECTED" ]; then
    echo "$TEST_NAME: PASS"
    exit 0
else
    echo "$TEST_NAME: FAIL"
    echo "Expected: $EXPECTED"
    echo "Result: $RESULT"
    exit 1
fi