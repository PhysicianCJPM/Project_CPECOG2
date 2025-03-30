#!/bin/bash
# This script collects Windows system metrics and process details,
# and saves the data into "output/data.log".

# Create the output directory if it doesn't exist.
OUTPUT_DIR="output"
mkdir -p "$OUTPUT_DIR"

OUTPUT_FILE="$OUTPUT_DIR/data.log"

echo "Collecting Windows system metrics and process details..."

# Collect CPU metrics using PowerShell (Win32_Processor's LoadPercentage)
echo "CPU Metrics:" > "$OUTPUT_FILE"
powershell.exe -Command "Get-WmiObject -Class Win32_Processor | Select-Object -ExpandProperty LoadPercentage" >> "$OUTPUT_FILE"

# Collect Windows process list using tasklist.exe
echo -e "\nWindows Process Metrics:" >> "$OUTPUT_FILE"
tasklist.exe >> "$OUTPUT_FILE"

echo "Data collection complete. Metrics saved to $OUTPUT_FILE."
