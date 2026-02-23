#include <stdio.h>

int main() {
    int n, quantum, i, temp, count = 0, timer = 0;
    int bt[10], rt[10], wt[10], tat[10];
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    while (count < n) {
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                if (rt[i] > quantum) {
                    timer += quantum;
                    rt[i] -= quantum;
                } else {
                    timer += rt[i];
                    wt[i] = timer - bt[i];
                    rt[i] = 0;
                    count++;
                    tat[i] = timer;
                }
            }
        }
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P[%d]\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage waiting time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
