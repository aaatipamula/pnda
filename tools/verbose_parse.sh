#!/bin/bash

PARSE_BIN="./bin/debug_parse"

if [ -z $PARSE_BIN ] || [ ! -f $PARSE_BIN ]; then
  echo "Missing $PARSE_BIN."
  exit 1
fi

for file in $(ls ./tests); do
  $PARSE_BIN ./tests/$file
done
