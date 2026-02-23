#include <stdio.h>

int main() {
    int bt[20], p[20], wt[20], tat[20], pr[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;

    printf("Enter the total number of process:");
    scanf("%d", &n);

    printf("Enter the Burst time and priority:\n");
    for (i = 0; i < n; i++) {
        printf("\n p[%d]\n", i + 1);
        printf("Burst time :");
        scanf("%d", &bt[i]);
        printf("Priority :");
        scanf("%d", &pr[i]);
        p[i] = i + 1;
    }

    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (pr[j] < pr[pos])
                pos = j;
        }

        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j];
        total += wt[i];
    }

    avg_wt = (float)total / n;
    total = 0;

    printf("\n Process\t Burst time\t priority\t Waiting Time\t Turn around Time");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
        printf("\n p[%d]\t\t %d\t\t %d\t\t %d\t\t %d", p[i], bt[i], pr[i], wt[i], tat[i]);
    }

    avg_tat = (float)total / n;
    printf("\n\n Average waiting Time = %.2f", avg_wt);
    printf("\n Average turnatound time = %.2f\n", avg_tat);

    return 0;
}
