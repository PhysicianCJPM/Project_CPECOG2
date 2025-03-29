#ifndef METRICS_H
#define METRICS_H

#include "process_management.h"

// Returns a dummy average CPU usage.
float get_avg_cpu_usage();

// Computes the average burst time for the given processes.
float get_avg_burst_time(Process *processes, int num_processes);

// Computes the average I/O wait time for the given processes.
float get_avg_io_wait_time(Process *processes, int num_processes);

#endif // METRICS_H
