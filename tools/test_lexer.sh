#!/bin/bash

if [ -z $1 ] || [ ! -f $1 ]; then
  echo "Missing testing binary."
  exit 1
fi

prog=$1

for file in $(ls ./tests); do
  $prog file > /dev/null 2>&1

  if [ $? -ne 0 ]; then
    echo "ERROR: Failed test on ${file}"
    exit $?
  fi
done

