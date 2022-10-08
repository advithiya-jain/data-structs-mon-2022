#include <stdio.h>

int isPrime(int n) {
    int i, result = 0;
    // Running loop from 2 to n/2. Since we dont care about 0 or 1 or any numbers after n/2. 
    // All numbers after n/2 wont be factors of n.
    for(i = 2; i < (n/2); i++) {
        result = (n % i == 0)? 1 : 0; //Storing 1 in result if n is divisible by i (not prime). Else 0.
    }
    return result; // returning the result (0 for prime, 1 for not prime)
}

int main(int argc, char** argv) {
    int n, flag;
    flag = 0;
    //take user input.
    do{
        printf("Enter a positive number: ");
        scanf("%d", &n);
        //Check if entered number is negative
        if(n < 0){
            printf("Wrong input!\n");
            flag = 1;
        }
        else {
            //Check if number is 0 or 1
            if(n == 1 || n == 0) {
                printf("Entered number is not prime.\n");
                flag = 0;
            }
            else {
                //Call prime function to check if its prime or not
                if(isPrime(n) == 0){
                    printf("Entered number is prime.\n");
                    flag = 0;
                }
                else
                    printf("Entered number is not prime.\n");
            }
        }
    }while(flag == 1);
}