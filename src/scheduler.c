#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "metrics.h"
#include "ann_inference.h"
#include "process_management.h"

// Choose the best scheduling algorithm based on ANN inference.
const char* choose_scheduling_algorithm(Process *processes, int num_processes) {
    float avg_cpu = get_avg_cpu_usage();
    float avg_burst = get_avg_burst_time(processes, num_processes);
    float avg_io = get_avg_io_wait_time(processes, num_processes);
    
    return predict_best_algorithm(avg_cpu, avg_burst, avg_io);
}

// Schedule processes using the algorithm selected by the ANN.
void schedule_processes(Process *processes, int num_processes) {
    const char* algorithm = choose_scheduling_algorithm(processes, num_processes);
    printf("Selected Scheduling Algorithm: %s\n", algorithm);

    if (strcmp(algorithm, "FCFS") == 0) {
        schedule_fcfs(processes, num_processes);
    } else if (strcmp(algorithm, "SJN") == 0) {
        schedule_sjn(processes, num_processes);
    } else if (strcmp(algorithm, "RR") == 0) {
        schedule_rr(processes, num_processes);
    } else {
        printf("Unknown algorithm. Defaulting to FCFS.\n");
        schedule_fcfs(processes, num_processes);
    }
}

int main() {
    int count = get_process_count();
    Process *processes = get_process_list(count);
    if (processes == NULL) {
        fprintf(stderr, "Failed to retrieve process list.\n");
        return EXIT_FAILURE;
    }
    schedule_processes(processes, count);
    free(processes);
    return EXIT_SUCCESS;
}
