#!/bin/bash

if [ ! -d "build" ]; then
  # Control will enter here if $DIRECTORY exists.
  mkdir "build"
fi

cd build || exit

cmake ..
cmake --build .

cp wavetables /usr/bin/

