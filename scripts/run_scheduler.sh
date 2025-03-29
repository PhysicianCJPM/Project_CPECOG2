#!/bin/bash
# This script automates the entire process:
# 1. Trains the ANN model using the provided Python script.
# 2. Builds the Intelligent Process Scheduler.
# 3. Runs the scheduler.

echo "Training the ANN model..."
python3 model/train_ann.py
if [ $? -ne 0 ]; then
    echo "ANN training failed. Exiting."
    exit 1
fi

echo "Collecting fresh system metrics..."
./scripts/data_collector.sh

echo "Building the project..."
make clean && make
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

echo "Running the Intelligent Process Scheduler..."
./scheduler
