#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "metrics.h"
#include "ann_inference.h"
#include "process_management.h"

#define MAX_LINE 1024

// Reads the CPU usage metric from the "output/data.log" file.
float load_avg_cpu_usage(const char* filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Failed to open %s\n", filename);
        return 0.65f;  // fallback default
    }
    char line[MAX_LINE];
    float cpu_usage = 0.65f;
    int found = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "CPU Metrics:") != NULL) {
            if (fgets(line, sizeof(line), f)) {
                if (sscanf(line, "%f", &cpu_usage) == 1) {
                    found = 1;
                    break;
                }
            }
        }
    }
    fclose(f);
    if (!found) {
        fprintf(stderr, "CPU usage not found in %s. Using default 0.65.\n", filename);
    }
    // Convert percentage to fraction (assuming the metric is provided as a percentage).
    return cpu_usage / 100.0f;
}

// Reads process details from the "output/data.log" file (Windows Process Metrics section).
Process* load_processes_from_file(const char* filename, int* out_count) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Failed to open %s\n", filename);
        *out_count = 0;
        return NULL;
    }
    char line[MAX_LINE];
    int found = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "Windows Process Metrics:") != NULL) {
            found = 1;
            break;
        }
    }
    if (!found) {
        fprintf(stderr, "Windows Process Metrics section not found in %s.\n", filename);
        fclose(f);
        *out_count = 0;
        return NULL;
    }
    // Skip header lines (assumes at least 2 header lines).
    fgets(line, sizeof(line), f);
    fgets(line, sizeof(line), f);
    
    int count = 0;
    long pos = ftell(f);
    while (fgets(line, sizeof(line), f)) {
        if (strlen(line) > 1) {
            count++;
        }
    }
    fseek(f, pos, SEEK_SET);
    
    Process *processes = malloc(count * sizeof(Process));
    if (!processes) {
        fprintf(stderr, "Memory allocation error for processes.\n");
        fclose(f);
        *out_count = 0;
        return NULL;
    }
    
    int idx = 0;
    while (fgets(line, sizeof(line), f) && idx < count) {
        char *token = strtok(line, " \t");
        if (!token) continue;
        token = strtok(NULL, " \t");
        if (!token) continue;
        int pid = atoi(token);
        processes[idx].pid = pid;
        // Simulate burst time (1 to 10) and I/O wait time (0 to 4).
        processes[idx].burst_time = rand() % 10 + 1;
        processes[idx].io_wait_time = rand() % 5;
        // CPU usage will be set later based on overall metric.
        processes[idx].cpu_usage = 0.65f;
        idx++;
    }
    fclose(f);
    *out_count = idx;
    return processes;
}

// Uses loaded average CPU usage along with computed average burst and I/O wait times
// to select the best scheduling algorithm via ANN inference.
const char* choose_scheduling_algorithm(Process *processes, int num_processes, float avg_cpu) {
    float avg_burst = get_avg_burst_time(processes, num_processes);
    float avg_io = get_avg_io_wait_time(processes, num_processes);
    return predict_best_algorithm(avg_cpu, avg_burst, avg_io);
}

// Organizes the processes based on the chosen scheduling algorithm.
void schedule_processes(Process *processes, int num_processes) {
    float avg_cpu = load_avg_cpu_usage("output/data.log");
    const char* algorithm = choose_scheduling_algorithm(processes, num_processes, avg_cpu);
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
    int num_processes = 0;
    Process *processes = load_processes_from_file("output/data.log", &num_processes);
    if (!processes || num_processes == 0) {
        fprintf(stderr, "No processes loaded from data.log. Falling back to simulated processes.\n");
        num_processes = get_process_count();
        processes = get_process_list(num_processes);
    }
    
    schedule_processes(processes, num_processes);
    free(processes);
    return 0;
}
