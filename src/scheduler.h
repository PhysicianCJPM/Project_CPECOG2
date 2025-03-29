#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_management.h"

// Choose the best scheduling algorithm using ANN inference.
const char* choose_scheduling_algorithm(Process *processes, int num_processes);

// Schedule processes using the chosen algorithm.
void schedule_processes(Process *processes, int num_processes);

#endif // SCHEDULER_H
