#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_management.h"

// Function to select the best scheduling algorithm using ANN
const char* choose_scheduling_algorithm(Process *processes, int num_processes);

// Function to schedule processes dynamically
void schedule_processes(Process *processes, int num_processes);

#endif // SCHEDULER_H
