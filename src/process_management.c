#include <stdio.h>
#include <stdlib.h>
#include "process_management.h"

// Simulate the retrieval of the number of active processes.
int get_process_count() {
    return 5;  // Placeholder value; replace with actual system calls if needed.
}

// Simulate the retrieval of process data.
Process* get_process_list(int num_processes) {
    Process *processes = malloc(num_processes * sizeof(Process));
    if (!processes) {
        fprintf(stderr, "Memory allocation error for process list.\n");
        return NULL;
    }
    for (int i = 0; i < num_processes; i++) {
        processes[i].pid = i + 1;
        processes[i].burst_time = rand() % 10 + 1;    // Burst time between 1 and 10.
        processes[i].io_wait_time = rand() % 5;         // I/O wait time between 0 and 4.
        processes[i].cpu_usage = (float)(rand() % 100) / 100.0f; // CPU usage between 0.0 and 1.0.
    }
    return processes;
}

// First-Come-First-Serve (FCFS) scheduling: process in order.
void schedule_fcfs(Process *processes, int num_processes) {
    printf("Executing FCFS scheduling:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d executed (Burst Time: %d)\n", processes[i].pid, processes[i].burst_time);
    }
}

// Shortest Job Next (SJN) scheduling: sort by burst time and execute.
void schedule_sjn(Process *processes, int num_processes) {
    printf("Executing SJN scheduling:\n");
    // Simple selection sort by burst time.
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

// Round Robin (RR) scheduling: simulate time slicing.
void schedule_rr(Process *processes, int num_processes) {
    printf("Executing Round Robin scheduling:\n");
    const int time_quantum = 3;
    int *remaining = malloc(num_processes * sizeof(int));
    if (!remaining) {
        fprintf(stderr, "Memory allocation error for Round Robin scheduling.\n");
        return;
    }
    for (int i = 0; i < num_processes; i++) {
        remaining[i] = processes[i].burst_time;
    }
    int done;
    do {
        done = 1;
        for (int i = 0; i < num_processes; i++) {
            if (remaining[i] > 0) {
                done = 0;
                int exec = (remaining[i] > time_quantum) ? time_quantum : remaining[i];
                printf("Process %d executed for %d time units.\n", processes[i].pid, exec);
                remaining[i] -= exec;
            }
        }
    } while (!done);
    free(remaining);
}
