#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isNum(char str[]) {
    int i = 0;
    int len = strlen(str);
    while (len > 0 && isspace(str[len - 1])) {
        len--;
    }

    if(len > 0){
        for (i = 0; i < len; ++i) {
            if (!isdigit(str[i])) {
               return 0;
            }
        }
        return 1;
    }
    else{
        return 0;
    }

}

int main(){
    int inp_time, hours, mins, flag;
    char inp[11];

    flag = 0;

    do{

        printf("Enter time in 24-hr format: ");
        scanf("%s", inp);

        if(isNum(inp) == 0 || strlen(inp) < 4 || strlen(inp) > 4) {
            printf("Invalid time entered.\n");
            flag = 1;
        }

        else {

            inp_time = atoi(inp);

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

        }

    } while (flag == 1);

    return 0;
}