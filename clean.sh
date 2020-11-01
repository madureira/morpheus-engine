#!/bin/bash

set -e
if [ "$(uname)" == "Darwin" ]; then
    ./Tools/mac/premake/premake5 clean
else
    ./Tools/linux/premake/premake5 clean
fi
