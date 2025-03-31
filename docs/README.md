# Intelligent Process Scheduler

## Overview
The **Intelligent Process Scheduler** is a system that dynamically selects the best CPU scheduling algorithm based on system metrics using an Artificial Neural Network (ANN). The scheduler collects system data, predicts the optimal scheduling strategy, and organizes process execution efficiently.

## Features
- **Automated Process Scheduling**: Uses an ANN to determine the best scheduling algorithm.
- **System Metrics Collection**: Gathers CPU usage, burst time, and I/O wait time.
- **Multi-Language Implementation**:
  - **Python**: ANN training and inference.
  - **Shell Scripts**: Automates execution.
  - **C Programming**: Handles low-level scheduling logic.
- **Custom ANN Model**: Pre-trained weights stored in `model/ann_weights.bin`.

## Project Structure
```
📂 intelligent-process-scheduler
├── 📂 model
│   ├── train_ann.py           # ANN training script
│   ├── ann_weights.bin        # Pre-trained model weights
│
├── 📂 scripts
│   ├── data_collector.sh      # Collects system metrics and saves to log file
│   ├── run_scheduler.sh       # Runs the process scheduler
│
├── 📂 src
│   ├── scheduler.c            # Main scheduling logic
│   ├── scheduler.h            # Header file Main scheduling logic
│   ├── process_management.c   # Process handling & management
│   ├── process_management.h   # Header file for Process handling & management
│   ├── metrics.c              # System metrics handling
│   ├── metrics.h              # Header file for System metrics handling
│   ├── ann_inference.c        # ANN-based decision-making
│   ├── ann_inference.h        # Header file for ANN-based decision-making
│   ├── scheduler.h            # Header file for scheduler functions
│
├── 📂 output
│   ├── data.log               # System metrics log
│   ├── scheduler_output.log   # Logs process scheduling results
│
├── Makefile                   # Compiles the C source files
├── README.md                  # Project documentation
```

## Installation
### Prerequisites
- **Python 3.8+** (for ANN training & inference)
- **GCC** (for compiling C source code)
- **TensorFlow** (for ANN model training)
- **Make** (to build C components)
- **Bash** (for running shell scripts)

### Setup
1. Clone the repository:
   ```sh
   git clone https://github.com/your-repo/intelligent-process-scheduler.git
   cd intelligent-process-scheduler
   ```

2. Install Python dependencies:
   ```sh
   pip install -r requirements.txt
   ```

3. Compile the C source files:
   ```sh
   make
   ```

## Usage
### 1. Collect System Metrics
Run the script to gather CPU usage, burst time, and I/O wait time:
```sh
./scripts/data_collector.sh
```
This will generate `output/data.log` with system metrics.

### 2. Run the Process Scheduler
Execute the main scheduler script:
```sh
./scripts/run_scheduler.sh
```
This will:
- Load system metrics from `data.log`
- Use the ANN model to determine the best scheduling algorithm
- Execute the scheduling strategy
- Log results in `output/scheduler_output.log`

## Training the ANN Model
If you want to retrain the ANN model with new data:
```sh
python model/train_ann.py
```
This will generate a new `ann_weights.bin` file.

## Troubleshooting
- **CUDA Warning: GPU Not Found**
  - If using TensorFlow without GPU, ignore this warning.
- **Git Errors (Filename Too Long)**
  - Enable long paths in Windows:
    ```sh
    git config --global core.longpaths true
    ```
- **Makefile Errors**
  - Ensure GCC is installed: `sudo apt install gcc` (Linux) or install MinGW (Windows).

## Contributors
- **Calee Jann "Lee" P. Mangunay** - Project Lead
- **Jarvis Servino** - ANN Model Optimization
- **Samantha Aldaba** - C Implementation

## License
This project is licensed under the MIT License.

---
*For questions or contributions, contact [calee_mangunay@dlsu.edu.ph](mailto:calee_mangunay@dlsu.edu.ph).*

