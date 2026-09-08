#include <stdio.h>

void printGantt(int order[], int start[], int end[], int count) {

    printf("\nGantt Chart:\n");

    printf(" ");

    for (int i = 0; i < count; i++) {
        printf("--------");
    }

    printf("\n|");

    for (int i = 0; i < count; i++) {
        printf("  P%d   |", order[i] + 1);
    }

    printf("\n ");

    for (int i = 0; i < count; i++) {
        printf("--------");
    }

    printf("\n%d", start[0]);

    for (int i = 0; i < count; i++) {
        printf("\t%d", end[i]);
    }

    printf("\n");
}


void fcfs() {

    int n;
    int process[100], arrival[100], burst[100];
    int completion[100], waiting[100], turnaround[100];

    int order[100], start[100], end[100];

    printf("\n--- FCFS Scheduling ---\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {

        process[i] = i + 1;

        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);

        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);
    }

    // Sort by Arrival Time
    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arrival[j] > arrival[j + 1]) {

                int temp;

                temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }

    int time = 0;

    for (int i = 0; i < n; i++) {

        if (time < arrival[i]) {
            time = arrival[i];
        }

        order[i] = process[i] - 1;
        start[i] = time;

        time += burst[i];

        end[i] = time;

        completion[i] = time;

        turnaround[i] = completion[i] - arrival[i];

        waiting[i] = turnaround[i] - burst[i];
    }

    int totalWT = 0;
    int totalTAT = 0;

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i],
               arrival[i],
               burst[i],
               completion[i],
               waiting[i],
               turnaround[i]);

        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    printf("\nAverage Waiting Time = %.2f\n",
           (float)totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           (float)totalTAT / n);

    printGantt(order, start, end, n);
}


void sjf() {

    int n;

    int process[100];
    int arrival[100];
    int burst[100];

    int completion[100];
    int waiting[100];
    int turnaround[100];
    int completed[100];

    int order[100];
    int start[100];
    int end[100];

    printf("\n--- SJF Scheduling ---\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {

        process[i] = i + 1;
        completed[i] = 0;

        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);

        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);
    }

    int time = 0;
    int count = 0;

    while (count < n) {

        int shortest = -1;

        for (int i = 0; i < n; i++) {

            if (completed[i] == 0 &&
                arrival[i] <= time) {

                if (shortest == -1 ||
                    burst[i] < burst[shortest]) {

                    shortest = i;
                }
            }
        }

        if (shortest == -1) {

            time++;

        } else {

            order[count] = shortest;
            start[count] = time;

            time += burst[shortest];

            end[count] = time;

            completion[shortest] = time;

            turnaround[shortest] =
                completion[shortest] - arrival[shortest];

            waiting[shortest] =
                turnaround[shortest] - burst[shortest];

            completed[shortest] = 1;

            count++;
        }
    }

    int totalWT = 0;
    int totalTAT = 0;

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i],
               arrival[i],
               burst[i],
               completion[i],
               waiting[i],
               turnaround[i]);

        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    printf("\nAverage Waiting Time = %.2f\n",
           (float)totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           (float)totalTAT / n);

    printGantt(order, start, end, n);
}


void priorityScheduling() {

    int n;

    int process[100];
    int arrival[100];
    int burst[100];
    int priority[100];

    int completion[100];
    int waiting[100];
    int turnaround[100];
    int completed[100];

    int order[100];
    int start[100];
    int end[100];

    printf("\n--- Priority Scheduling ---\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

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

    while (count < n) {

        int highest = -1;

        for (int i = 0; i < n; i++) {

            if (completed[i] == 0 &&
                arrival[i] <= time) {

                if (highest == -1 ||
                    priority[i] < priority[highest]) {

                    highest = i;
                }
            }
        }

        if (highest == -1) {

            time++;

        } else {

            order[count] = highest;
            start[count] = time;

            time += burst[highest];

            end[count] = time;

            completion[highest] = time;

            turnaround[highest] =
                completion[highest] - arrival[highest];

            waiting[highest] =
                turnaround[highest] - burst[highest];

            completed[highest] = 1;

            count++;
        }
    }

    int totalWT = 0;
    int totalTAT = 0;

    printf("\nProcess\tAT\tBT\tPriority\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               process[i],
               arrival[i],
               burst[i],
               priority[i],
               completion[i],
               waiting[i],
               turnaround[i]);

        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    printf("\nAverage Waiting Time = %.2f\n",
           (float)totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           (float)totalTAT / n);

    printGantt(order, start, end, n);
}


void roundRobin() {

    int n, quantum;

    int process[100];
    int arrival[100];
    int burst[100];
    int remaining[100];

    int completion[100];
    int waiting[100];
    int turnaround[100];
    int completed[100];

    int order[1000];
    int start[1000];
    int end[1000];

    printf("\n--- Round Robin Scheduling ---\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    for (int i = 0; i < n; i++) {

        process[i] = i + 1;
        completed[i] = 0;

        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);

        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);

        remaining[i] = burst[i];
    }

    int queue[1000];
    int front = 0;
    int rear = 0;

    int time = 0;
    int completedCount = 0;
    int ganttCount = 0;

    while (completedCount < n) {

        // Add arrived processes
        for (int i = 0; i < n; i++) {

            if (arrival[i] <= time &&
                completed[i] == 0) {

                int already = 0;

                for (int j = front; j < rear; j++) {

                    if (queue[j] == i) {
                        already = 1;
                        break;
                    }
                }

                if (!already) {
                    queue[rear++] = i;
                }
            }
        }

        if (front == rear) {

            time++;
            continue;
        }

        int current = queue[front++];

        order[ganttCount] = current;
        start[ganttCount] = time;

        int executeTime;

        if (remaining[current] > quantum) {
            executeTime = quantum;
        } else {
            executeTime = remaining[current];
        }

        time += executeTime;

        remaining[current] -= executeTime;

        end[ganttCount] = time;

        ganttCount++;

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {

            if (arrival[i] <= time &&
                completed[i] == 0 &&
                i != current) {

                int already = 0;

                for (int j = front; j < rear; j++) {

                    if (queue[j] == i) {
                        already = 1;
                        break;
                    }
                }

                if (!already) {
                    queue[rear++] = i;
                }
            }
        }

        if (remaining[current] == 0) {

            completed[current] = 1;

            completion[current] = time;

            turnaround[current] =
                completion[current] - arrival[current];

            waiting[current] =
                turnaround[current] - burst[current];

            completedCount++;

        } else {

            queue[rear++] = current;
        }
    }

    int totalWT = 0;
    int totalTAT = 0;

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i],
               arrival[i],
               burst[i],
               completion[i],
               waiting[i],
               turnaround[i]);

        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    printf("\nAverage Waiting Time = %.2f\n",
           (float)totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           (float)totalTAT / n);

    printGantt(order, start, end, ganttCount);
}


int main() {

    int choice;

    while (1) {

        printf("\n================================\n");
        printf("       AIOS CPU SCHEDULER\n");
        printf("================================\n");

        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. Priority Scheduling\n");
        printf("4. Round Robin\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                fcfs();
                break;

            case 2:
                sjf();
                break;

            case 3:
                priorityScheduling();
                break;

            case 4:
                roundRobin();
                break;

            case 5:
                printf("\nExiting AIOS CPU Scheduler...\n");
                return 0;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}