#ifndef METRICS_H
#define METRICS_H

#include "process_management.h"

// Returns the average CPU usage from system metrics (dummy implementation).
float get_avg_cpu_usage();

// Computes and returns the average burst time from the given processes.
float get_avg_burst_time(Process *processes, int num_processes);

// Computes and returns the average I/O wait time from the given processes.
float get_avg_io_wait_time(Process *processes, int num_processes);

#endif // METRICS_H
