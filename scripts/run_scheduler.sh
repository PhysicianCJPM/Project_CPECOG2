#!/bin/bash
# This script automates the pipeline:
# 1. Collects fresh Windows system metrics.
# 2. Builds the project.
# 3. Runs the scheduler, which uses pre-trained ANN weights (ann_weights.bin) to determine the scheduling algorithm.

# Create the output directory if it doesn't exist.
OUTPUT_DIR="output"
mkdir -p "$OUTPUT_DIR"

echo "Collecting fresh Windows system metrics..."
./scripts/data_collector.sh

echo "Building the project..."
make clean && make
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

echo "Running the Intelligent Process Scheduler..."
# Redirect scheduler output to output/scheduler_output.log
./scheduler | tee "$OUTPUT_DIR/scheduler_output.log"
