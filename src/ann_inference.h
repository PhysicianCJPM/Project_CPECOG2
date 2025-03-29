#ifndef ANN_INFERENCE_H
#define ANN_INFERENCE_H

// Predict the best scheduling algorithm using ANN-based inference.
// Returns one of "RR", "SJN", or "FCFS".
const char* predict_best_algorithm(float avg_cpu_usage, float avg_burst_time, float avg_io_wait);

#endif // ANN_INFERENCE_H
