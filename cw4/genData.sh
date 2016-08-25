#!/bin/bash

if [ "$1" == "sel" ]; then
    echo "Generating data with selection";
    ./cw4 data.root selectedData/data.root true;
    ./cw4 mc_background.root selectedData/mc_background.root true;
    ./cw4 mc_signal.root selectedData/mc_signal.root true;
else
    echo "Generating standard data";
    ./cw4 data.root generatedData/data.root;
    ./cw4 mc_background.root generatedData/mc_background.root;
    ./cw4 mc_signal.root generatedData/mc_signal.root;
fi
