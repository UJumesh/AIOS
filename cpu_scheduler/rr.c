#include <stdio.h>

int main() {

    int n, quantum;

    int process[100];
    int arrival[100];
    int burst[100];
    int remaining[100];

    int completion[100];
    int waiting[100];
    int turnaround[100];

    int completed[100];

    // Gantt Chart
    int gantt_process[1000];
    int gantt_start[1000];
    int gantt_end[1000];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    printf("\nEnter Arrival Time and Burst Time:\n");

    for (int i = 0; i < n; i++) {

        process[i] = i + 1;
        completed[i] = 0;

        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);

        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);

        remaining[i] = burst[i];
    }

    int time = 0;
    int completed_count = 0;
    int gantt_count = 0;

    /*
       Ready Queue
    */
    int queue[1000];
    int front = 0;
    int rear = 0;

    /*
       Add processes that have already arrived
    */
    for (int i = 0; i < n; i++) {

        if (arrival[i] <= time) {
            queue[rear++] = i;
        }
    }

    while (completed_count < n) {

        /*
           If queue is empty,
           move time forward until a process arrives
        */
        if (front == rear) {

            time++;

            for (int i = 0; i < n; i++) {

                if (completed[i] == 0 &&
                    arrival[i] <= time) {

                    int already_in_queue = 0;

                    for (int j = front; j < rear; j++) {
                        if (queue[j] == i) {
                            already_in_queue = 1;
                            break;
                        }
                    }

                    if (!already_in_queue) {
                        queue[rear++] = i;
                    }
                }
            }

            continue;
        }

        // Take first process from queue
        int current = queue[front++];

        // Store Gantt start time
        gantt_process[gantt_count] = current;
        gantt_start[gantt_count] = time;

        // Execute for quantum or remaining time
        int execution_time;

        if (remaining[current] > quantum) {
            execution_time = quantum;
        } else {
            execution_time = remaining[current];
        }

        time = time + execution_time;

        remaining[current] =
            remaining[current] - execution_time;

        // Store Gantt end time
        gantt_end[gantt_count] = time;
        gantt_count++;


        /*
           Add newly arrived processes
           to ready queue
        */
        for (int i = 0; i < n; i++) {

            if (completed[i] == 0 &&
                arrival[i] <= time &&
                i != current) {

                int already_in_queue = 0;

                for (int j = front; j < rear; j++) {

                    if (queue[j] == i) {
                        already_in_queue = 1;
                        break;
                    }
                }

                if (!already_in_queue) {
                    queue[rear++] = i;
                }
            }
        }


        // Process completed
        if (remaining[current] == 0) {

            completed[current] = 1;

            completion[current] = time;

            turnaround[current] =
                completion[current] - arrival[current];

            waiting[current] =
                turnaround[current] - burst[current];

            completed_count++;

        } else {

            // Process not completed
            // Put it back at queue end
            queue[rear++] = current;
        }
    }


    // Display result
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    int total_waiting = 0;
    int total_turnaround = 0;

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i],
               arrival[i],
               burst[i],
               completion[i],
               waiting[i],
               turnaround[i]);

        total_waiting += waiting[i];
        total_turnaround += turnaround[i];
    }


    // Average
    printf("\nAverage Waiting Time = %.2f\n",
           (float)total_waiting / n);

    printf("Average Turnaround Time = %.2f\n",
           (float)total_turnaround / n);


    // Gantt Chart
    printf("\nGantt Chart:\n");

    printf(" ");

    for (int i = 0; i < gantt_count; i++) {
        printf("--------");
    }

    printf("\n|");

    for (int i = 0; i < gantt_count; i++) {
        printf("  P%d   |",
               process[gantt_process[i]]);
    }

    printf("\n ");

    for (int i = 0; i < gantt_count; i++) {
        printf("--------");
    }

    printf("\n%d", gantt_start[0]);

    for (int i = 0; i < gantt_count; i++) {
        printf("\t%d", gantt_end[i]);
    }

    printf("\n");

    return 0;
}