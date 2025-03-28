#include <stdio.h>
#include <stdlib.h>
#include "process_management.h"

// Function to get the number of active processes
int get_process_count() {
    // Simulate retrieval of process count (replace with actual system call if needed)
    return 5; // Placeholder value
}

// Function to retrieve a list of processes
Process* get_process_list(int num_processes) {
    Process *processes = (Process*) malloc(num_processes * sizeof(Process));
    if (!processes) {
        fprintf(stderr, "Memory allocation failed for process list.\n");
        return NULL;
    }
    
    // Simulate process data (Replace with actual process retrieval logic)
    for (int i = 0; i < num_processes; i++) {
        processes[i].pid = i + 1;
        processes[i].burst_time = rand() % 10 + 1;    // Burst time between 1 and 10
        processes[i].io_wait_time = rand() % 5;         // I/O wait time between 0 and 4
        processes[i].cpu_usage = (float)(rand() % 100) / 100.0f;  // CPU usage between 0.0 and 1.0
    }
    
    return processes;
}

// First-Come-First-Serve (FCFS) scheduling
void schedule_fcfs(Process *processes, int num_processes) {
    printf("Scheduling using First-Come-First-Serve (FCFS)\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d executed (Burst Time: %d)\n", processes[i].pid, processes[i].burst_time);
    }
}

// Shortest Job Next (SJN) scheduling
void schedule_sjn(Process *processes, int num_processes) {
    printf("Scheduling using Shortest Job Next (SJN)\n");
    
    // Simple selection sort to order processes by burst time
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[j].burst_time < processes[i].burst_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d executed (Burst Time: %d)\n", processes[i].pid, processes[i].burst_time);
    }
}

// Round Robin (RR) scheduling
void schedule_rr(Process *processes, int num_processes) {
    printf("Scheduling using Round Robin (RR)\n");
    
    const int time_quantum = 3;
    int remaining[num_processes];  // Array to track remaining burst times
    
    // Initialize remaining burst times
    for (int i = 0; i < num_processes; i++) {
        remaining[i] = processes[i].burst_time;
    }
    
    int done;
    // Continue looping until all processes have completed execution
    do {
        done = 1;
        for (int i = 0; i < num_processes; i++) {
            if (remaining[i] > 0) {
                done = 0;
                int exec_time = (remaining[i] > time_quantum) ? time_quantum : remaining[i];
                printf("Process %d executed for %d time units\n", processes[i].pid, exec_time);
                remaining[i] -= exec_time;
            }
        }
    } while (!done);
}
