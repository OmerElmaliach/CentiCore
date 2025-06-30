#!/bin/bash

# Setup path and build dir.
cd ..
rm -rf build
mkdir build
cd build

# Build and configure gui app.
cmake .. -DCMAKE_PREFIX_PATH="$HOME/Qt/6.9.1/gcc_64/lib/cmake" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON


# Run makefile.
make -j$(nproc)

# Run the gui app.
echo "------------------------------------------------------------"
./CentiCore

