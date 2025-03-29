#include "metrics.h"

// Return a dummy average CPU usage value.
float get_avg_cpu_usage() {
    return 0.65f;  // In a real implementation, compute actual CPU usage.
}

// Compute the average burst time for the given processes.
float get_avg_burst_time(Process *processes, int num_processes) {
    if (num_processes == 0) return 0.0f;
    int total = 0;
    for (int i = 0; i < num_processes; i++) {
        total += processes[i].burst_time;
    }
    return (float)total / num_processes;
}

// Compute the average I/O wait time for the given processes.
float get_avg_io_wait_time(Process *processes, int num_processes) {
    if (num_processes == 0) return 0.0f;
    int total = 0;
    for (int i = 0; i < num_processes; i++) {
        total += processes[i].io_wait_time;
    }
    return (float)total / num_processes;
}
