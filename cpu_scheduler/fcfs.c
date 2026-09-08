#include <stdio.h>

int main() {

    int n;
    int process[100];
    int arrival[100];
    int burst[100];
    int completion[100];
    int waiting[100];
    int turnaround[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Arrival Time and Burst Time:\n");

    for (int i = 0; i < n; i++) {

        process[i] = i + 1;

        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);

        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);
    }


    // Sort processes according to Arrival Time
    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arrival[j] > arrival[j + 1]) {

                // Swap Arrival Time
                int temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                // Swap Burst Time
                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                // Swap Process Number
                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }


    // FCFS Scheduling
    int time = 0;

    for (int i = 0; i < n; i++) {

        // CPU idle if process has not arrived
        if (time < arrival[i]) {
            time = arrival[i];
        }

        time = time + burst[i];

        completion[i] = time;

        turnaround[i] = completion[i] - arrival[i];

        waiting[i] = turnaround[i] - burst[i];
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
    float average_waiting = (float)total_waiting / n;
    float average_turnaround = (float)total_turnaround / n;

    printf("\nAverage Waiting Time = %.2f\n", average_waiting);
    printf("Average Turnaround Time = %.2f\n", average_turnaround);


    // Gantt Chart
    printf("\nGantt Chart:\n");

    printf(" ");

    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf("  P%d   |", process[i]);
    }

    printf("\n ");

    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    printf("\n%d", arrival[0]);

    for (int i = 0; i < n; i++) {
        printf("\t%d", completion[i]);
    }

    printf("\n");

    return 0;
}