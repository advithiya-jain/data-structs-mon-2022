#include<stdio.h>
#include<stdlib.h>

int main(){
    int inp_time, hours, mins, flag;

    flag = 0;

    do{

        printf("Enter time in 24-hr format: ");
        scanf("%d", &inp_time);

        hours = inp_time / 100;
        mins = inp_time % 100;

        if((hours < 0 || hours > 23) || (mins < 0 || mins > 59)){
            printf("Invalid time entered.\n");
            flag = 1;
        }
        else {
            if(hours > 12 && hours < 24) {
                hours = hours-12;
                printf("%d:%d PM\n", hours, mins);
            }
            else {
                printf("%d:%d AM\n", hours, mins);
            }
            flag = 0;
        }

    } while (flag == 1);

    return 0;
}