#include <stdio.h>

int main() {

    int n;

    int process[100];
    int arrival[100];
    int burst[100];
    int priority[100];

    int completion[100];
    int waiting[100];
    int turnaround[100];
    int completed[100];

    // Gantt Chart information
    int order[100];
    int start_time[100];
    int end_time[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Arrival Time, Burst Time and Priority:\n");

    for (int i = 0; i < n; i++) {

        process[i] = i + 1;
        completed[i] = 0;

        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);

        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);

        printf("P%d Priority: ", i + 1);
        scanf("%d", &priority[i]);
    }

    int time = 0;
    int count = 0;

    // Priority Scheduling
    while (count < n) {

        int highest = -1;

        // Find highest priority available process
        for (int i = 0; i < n; i++) {

            if (completed[i] == 0 &&
                arrival[i] <= time) {

                // Smaller number = higher priority
                if (highest == -1 ||
                    priority[i] < priority[highest]) {

                    highest = i;
                }
            }
        }

        // No process has arrived
        if (highest == -1) {

            time++;

        } else {

            // Save start time
            start_time[count] = time;

            // Execute process
            time = time + burst[highest];

            // Save end time
            end_time[count] = time;

            // Save execution order
            order[count] = highest;

            completion[highest] = time;

            turnaround[highest] =
                completion[highest] - arrival[highest];

            waiting[highest] =
                turnaround[highest] - burst[highest];

            completed[highest] = 1;

            count++;
        }
    }

    // Display result
    printf("\nProcess\tAT\tBT\tPriority\tCT\tWT\tTAT\n");

    int total_waiting = 0;
    int total_turnaround = 0;

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               process[i],
               arrival[i],
               burst[i],
               priority[i],
               completion[i],
               waiting[i],
               turnaround[i]);

        total_waiting += waiting[i];
        total_turnaround += turnaround[i];
    }

    printf("\nAverage Waiting Time = %.2f\n",
           (float)total_waiting / n);

    printf("Average Turnaround Time = %.2f\n",
           (float)total_turnaround / n);


    // Gantt Chart
    printf("\nGantt Chart:\n");

    printf(" ");

    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf("  P%d   |", process[order[i]]);
    }

    printf("\n ");

    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    printf("\n%d", start_time[0]);

    for (int i = 0; i < n; i++) {
        printf("\t%d", end_time[i]);
    }

    printf("\n");

    return 0;
}