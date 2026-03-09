#include <stdio.h>
int main() {
    int refer[50], frame[50], fsize, i, j,flag =0, c =0, n, fault = 0, k, recent[50], temp, flag1 = 0;
    float miss, hit;
    printf("Enter the number of refer : ");
    scanf("%d",&n);
    printf("Enter the refer : ");
    for(i=0;i<n;i++) {
        scanf("%d", &refer[i]);
    }
    printf("Enter the frame size : ");
    scanf("%d",&fsize);
    for(i=0;i<fsize;i++) {
        fault++;
        frame[i] = refer[i];
        recent[i] = refer[i];
        c++;
    }
    recent[c] = 0;
    for(i=0;i<n;i++) {
        for(k=0;k<c;k++) {
            if(recent[k] == refer[i]) {
                flag1 = 1;
                break;
            }
        }
        if(flag1==1) {
            temp = recent[k];
            for(j=k;j<c;j++) 
                recent[j] = recent[j+1];
            recent[c-1] = temp;
        }
        else {
            recent[c] = refer[i];
            c++;
            recent[c] = 0;
        }
        flag1 = 0;
        for(j=0;j<fsize;j++) {
            if(frame[j] == refer[i])
                flag = 1;
        }
        if(flag!=1) {
            fault++;
            for(k=0;k<c;k++) {
                for(j=0;j<fsize;j++){
                    if(recent[k] == frame[j]) {
                        frame[j] = refer[i];
                        goto end;
                    }
                }
            }
        }
        end:
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