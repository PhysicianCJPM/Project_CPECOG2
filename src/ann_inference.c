#include "ann_inference.h"
#include <string.h>

// Dummy implementation of ANN-based inference.
// In a real scenario, this function would load and run a pre-trained neural network model.
// Here, we use simple threshold-based logic to select a scheduling algorithm.
const char* predict_best_algorithm(float avg_cpu_usage, float avg_burst_time, float avg_io_wait) {
    // If CPU usage is high, choose Round Robin (RR) for responsiveness.
    if (avg_cpu_usage > 0.8f) {
        return "RR";
    }
    // If the average burst time is low, prefer Shortest Job Next (SJN).
    else if (avg_burst_time < 5.0f) {
        return "SJN";
    }
    // Otherwise, default to First-Come-First-Serve (FCFS).
    else {
        return "FCFS";
    }
}
#include "ann_inference.h"
#include <string.h>

// Dummy implementation of ANN-based inference.
// In a real scenario, this function would load and run a pre-trained neural network model.
// Here, we use simple threshold-based logic to select a scheduling algorithm.
const char* predict_best_algorithm(float avg_cpu_usage, float avg_burst_time, float avg_io_wait) {
    // If CPU usage is high, choose Round Robin (RR) for responsiveness.
    if (avg_cpu_usage > 0.8f) {
        return "RR";
    }
    // If the average burst time is low, prefer Shortest Job Next (SJN).
    else if (avg_burst_time < 5.0f) {
        return "SJN";
    }
    // Otherwise, default to First-Come-First-Serve (FCFS).
    else {
        return "FCFS";
    }
}
