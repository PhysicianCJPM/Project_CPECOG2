#include "metrics.h"

float get_avg_cpu_usage() {
    // In a real implementation, this would read the CPU usage dynamically.
    // Here we return a dummy value.
    return 0.65f;
}

float get_avg_burst_time(Process *processes, int num_processes) {
    if (num_processes == 0) return 0.0f;
    int total = 0;
    for (int i = 0; i < num_processes; i++) {
        total += processes[i].burst_time;
    }
    return (float) total / num_processes;
}

float get_avg_io_wait_time(Process *processes, int num_processes) {
    if (num_processes == 0) return 0.0f;
    int total = 0;
    for (int i = 0; i < num_processes; i++) {
        total += processes[i].io_wait_time;
    }
    return (float) total / num_processes;
}
