#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H

// Structure representing a process.
typedef struct {
    int pid;
    int burst_time;
    int io_wait_time;
    float cpu_usage;
} Process;

// Function prototypes for process management.
int get_process_count();
Process* get_process_list(int num_processes);
void schedule_fcfs(Process *processes, int num_processes);
void schedule_sjn(Process *processes, int num_processes);
void schedule_rr(Process *processes, int num_processes);

#endif // PROCESS_MANAGEMENT_H
