#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Function to check whether the entered string contains only integers.
int isNum(char str[]) {
    int i = 0;
    int len = strlen(str);

    // Avoiding working on whitespaces and other special space characters like \n, \r, etc.
    while (len > 0 && isspace(str[len - 1])) {
        len--;
    }
    // If the length of the string is greater then 0 after checking for space characters then enter.
    if(len > 0){
        // Loop that runs through the input string and checks if each character is a digit or not.
        for (i = 0; i < len; ++i) {
            // isdigit() returns true if the character is a digit,
            // so a ! is added in front to check if it is not one.
            // 0 (false) is returned if any of the characters is not a digit.
            if (!isdigit(str[i])) {
               return 0;
            }
        }
        // return 1 (true), only if the loop terminates successfully.
        return 1;
    }
    // else return 0 which is essentially false.
    else{
        return 0;
    }

}

int main(){
    int inp_time, hours, mins, flag;
    // String to hold user input time (assuming they will no enter more than 10 chars)
    char inp[11];
    // flag variable used to terminate do while loop.
    flag = 0;

    do{
        // Ask for input first.
        printf("Enter time in 24-hr format in 4 numbers (ex: 0315 for 3:15, 2245 for 22:45): ");
        scanf("%s", inp);
        // Calling isNum() to check if the entered string only contains numbers.
        // Also checking if the string entered is less than 4 chars or greater than 4 chars.
        if(isNum(inp) == 0 || strlen(inp) < 4 || strlen(inp) > 4) {
            printf("Invalid time entered.\n");
            flag = 1; // setting flag to 1 so the loop continues at the while condition.
        }

        else {
            // converting input string to integer
            inp_time = atoi(inp);
            // Getting the first 2 digits of the 24 hour time, which are the hours.
            hours = inp_time / 100;
            // Getting the last 2 digits of the 24 hour time, which are the mins.
            mins = inp_time % 100;
            // Basic checking for invalid hours and mins entered.
            if((hours < 0 || hours > 23) || (mins < 0 || mins > 59)){
                printf("Invalid time entered.\n");
                flag = 1; // Setting flag to 1 so loop will continue.
            }
            // If all checks above are passed move here.
            else {
                // Logic to convert hours after 12, back to 1, 2, 3, ...
                if(hours > 12 && hours < 24) {
                    hours = hours-12;
                    // Printing the time in 12 hr format. This is done here to make the AM/PM result
                    // easier to print.
                    // If the mins are greater than 9 i.e. double digit we print it as it is
                    if(mins > 9) printf("%d:%d PM\n", hours, mins);
                    // else it is single digit so we add a 0 in front
                    else         printf("%d:0%d PM\n", hours, mins);
                }
                else {
                    // No conversion needed if hours is < 12 and > 0.
                    if(mins > 9) printf("%d:%d AM\n", hours, mins); // Same logic as line 73
                    else         printf("%d:0%d AM\n", hours, mins);
                }
                flag = 0; // Setting flag to 0 so that the loop will exit.

            }

        }

    } while (flag == 1);

    return 0;
}