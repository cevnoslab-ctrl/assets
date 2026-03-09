#include <stdio.h>
int main() {
    int n, fsize, i, j, k, fault = 0, flag, frames[10], pages[30], temp[10];
    int max, index;
    printf("Enter number of ref:");
    scanf("%d", &n);
    printf("Enter the ref string: ");
    for(i=0;i<n;i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter framesize : ");
    scanf("%d", &fsize);
    for(i=0;i<fsize;i++) 
        frames[i] = -1;
    for(i=0;i<n;i++) {
        flag = 0;
        for(j=0;j<fsize;j++) {
            if(frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            fault++;
            int empt = 0;
            for(j=0;j<fsize;j++) {
                if(frames[j] == -1) {
                    frames[j] = pages[i];
                    empt = 1;
                    break;
                }
            }
            if(!empt) {
                for(j=0;j<fsize;j++) {
                    temp[j] = -1;
                    for(k=i+1;k<n;k++) {
                        if(frames[j] == pages[k]) {
                            temp[j] = k;
                            break;
                        }
                    }
                }
                max = -1;
                index = 0;
                for(j=0;j<fsize;j++) {
                    if(temp[j] == -1) {
                        index = j;
                        break;
                    }
                    if(temp[j]> max) {
                        max = temp[j];
                        index = j;
                    }
                }
                frames[index] = pages[i];
            }
        }
    }
    printf("\nTotal Page Faults = %d", fault);
    printf("\nMiss Ratio = %.2f%%",((float)fault/n)*100);
    printf("\nHit Ration = %.2f%%", ((float)(n-fault)/n)*100);

    return 0;
}