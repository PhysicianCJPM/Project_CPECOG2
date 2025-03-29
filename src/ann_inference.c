#include "ann_inference.h"
#include <string.h>

// Dummy ANN inference using simple thresholds.
// In a real scenario, this would run a pre-trained neural network model.
const char* predict_best_algorithm(float avg_cpu_usage, float avg_burst_time, float avg_io_wait) {
    if (avg_cpu_usage > 0.8f) {
        return "RR";   // High CPU usage: Round Robin for responsiveness.
    } else if (avg_burst_time < 5.0f) {
        return "SJN";  // Low burst time: Shortest Job Next.
    } else {
        return "FCFS"; // Default to First-Come-First-Serve.
    }
}
