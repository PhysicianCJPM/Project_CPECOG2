#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct {
    int pid;
    int burst_time;
    int io_wait_time;
    float cpu_usage;
} Process;

// Function prototypes
int get_process_count();
Process* get_process_list(int num_processes);
void schedule_fcfs(Process *processes, int num_processes);
void schedule_sjn(Process *processes, int num_processes);
void schedule_rr(Process *processes, int num_processes);

#endif // PROCESS_MANAGEMENT_H