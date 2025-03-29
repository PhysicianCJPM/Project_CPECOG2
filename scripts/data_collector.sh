#!/bin/bash
# This script collects real system metrics and process details.
# It stores the collected data into a file for use by the ANN model.

OUTPUT_FILE="data.log"

echo "Collecting system metrics..."

# Capture CPU metrics from /proc/stat using top in batch mode.
echo "CPU Metrics:" > "$OUTPUT_FILE"
top -bn1 | grep "Cpu(s)" >> "$OUTPUT_FILE"

echo "Collecting process metrics..."
# Capture detailed process metrics using ps.
echo -e "\nProcess Metrics:" >> "$OUTPUT_FILE"
ps -eo pid,comm,pcpu,pmem >> "$OUTPUT_FILE"

echo "Data collection complete. Metrics saved to $OUTPUT_FILE."
