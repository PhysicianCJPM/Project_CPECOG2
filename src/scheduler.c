#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"
#include "metrics.h"
#include "ann_inference.h"
#include "process_management.h"

// Structure to represent a process
typedef struct {
    int pid;
    int burst_time;
    int io_wait_time;
    float cpu_usage;
} Process;

// Function to choose the best scheduling algorithm using ANN
const char* choose_scheduling_algorithm(Process *processes, int num_processes) {
    // Collect system metrics
    float avg_cpu_usage = get_avg_cpu_usage();
    float avg_burst_time = get_avg_burst_time(processes, num_processes);
    float avg_io_wait = get_avg_io_wait_time(processes, num_processes);
    
    // Use ANN to predict the best scheduling algorithm
    return predict_best_algorithm(avg_cpu_usage, avg_burst_time, avg_io_wait);
}

void schedule_processes(Process *processes, int num_processes) {
    // Choose the best scheduling algorithm
    const char* selected_algorithm = choose_scheduling_algorithm(processes, num_processes);
    
    printf("Using Scheduling Algorithm: %s\n", selected_algorithm);
    
    if (strcmp(selected_algorithm, "FCFS") == 0) {
        schedule_fcfs(processes, num_processes);
    } else if (strcmp(selected_algorithm, "SJN") == 0) {
        schedule_sjn(processes, num_processes);
    } else if (strcmp(selected_algorithm, "RR") == 0) {
        schedule_rr(processes, num_processes);
    } else {
        printf("Unknown scheduling algorithm. Defaulting to FCFS.\n");
        schedule_fcfs(processes, num_processes);
    }
}

int main() {
    int num_processes = get_process_count();
    Process *processes = get_process_list(num_processes);
    
    if (processes == NULL) {
        fprintf(stderr, "Error retrieving process list.\n");
        return 1;
    }
    
    schedule_processes(processes, num_processes);
    
    free(processes);
    return 0;
}
