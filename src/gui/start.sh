#!/bin/bash

# Setup path and build dir.
cd ../../config
mkdir build
cd build

# Build and configure gui app.
cmake .. -DCMAKE_PREFIX_PATH="$HOME/Qt/6.9.1/gcc_64/lib/cmake"

# Run makefile.
make

# Run the gui app.
echo "------------------------------------------------------------"
./CentiCore

