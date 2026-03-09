#include <stdio.h>
int main() {
    int refer[50], frame[50], fsize, i, j,flag =0, c =0, n, fault = 0;
    float miss, hit;
    printf("Enter the number of refer : ");
    scanf("%d",&n);
    printf("Enter the refer : ");
    for(i=0;i<n;i++) {
        scanf("%d", &refer[i]);
    }
    printf("Enter the frame size : ");
    scanf("%d",&fsize);
    for(i=0;i<fsize;i++)
        frame[i] = -1;
    for(i=0;i<n;i++) {
        for(j=0;j<fsize;j++) {
            if(frame[j] == refer[i])
                flag = 1;
        }
        if(flag!=1) {
            fault++;
            frame[c] = refer[i];
            c++;
        }
        if(c==fsize)
            c = 0;
        flag = 0;
    }
    printf("Total number of faults = %d\n", fault);
    miss = ((float)fault/n)*100;
    hit = ((float)(n-fault)/n)*100;
    printf("Total number of references = %d\n", n);
    printf("Miss ratio = %.2f%% \n", miss);
    printf("Hit Ratio = %.2f%% \n",hit);

    return 0;
}