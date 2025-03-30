#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_management.h"

// Now the function prototype includes an extra parameter for average CPU usage.
const char* choose_scheduling_algorithm(Process *processes, int num_processes, float avg_cpu);

// Schedule processes using the chosen algorithm.
void schedule_processes(Process *processes, int num_processes);

#endif // SCHEDULER_H
