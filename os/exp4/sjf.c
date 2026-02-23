#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];
    int isCompleted[n];

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        isCompleted[i] = 0;
    }

    while (completed < n) {
        int idx = -1;
        int minBT = 100000;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && isCompleted[i] == 0) {
                if (bt[i] < minBT) {
                    minBT = bt[i];
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;  // CPU idle
        } else {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            avgWT += wt[idx];
            avgTAT += tat[idx];

            isCompleted[idx] = 1;
            completed++;
        }
    }
printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
printf("\nAverage Waiting Time = %.2f", avgWT / n);
printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);
return 0;
}
