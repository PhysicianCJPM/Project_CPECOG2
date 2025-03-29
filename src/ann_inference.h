#ifndef ANN_INFERENCE_H
#define ANN_INFERENCE_H

// Predicts the best scheduling algorithm based on provided average metrics.
// In a production system, this would invoke an ANN model.
const char* predict_best_algorithm(float avg_cpu_usage, float avg_burst_time, float avg_io_wait);

#endif // ANN_INFERENCE_H
