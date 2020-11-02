#!/bin/bash

set -e

if [ "$(uname)" == "Darwin" ]; then
    ./Tools/mac/premake/premake5 gmake2
else
    ./Tools/linux/premake/premake5 gmake2
fi
