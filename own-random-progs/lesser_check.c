#include<stdio.h>

int main() {
    int i, j;
    printf("Enter value of i: ");
    scanf("%d", &i);
    printf("Enter value of j: ");
    scanf("%d", &j);
    
    int le = 0;
    //le = ((i+j)*(i+j))-((i-j)*(i-j)); does not work
    le = (j+i)-(j-i); // neither does this. fml.
    le = le/2;
    printf("%d\n", le);
}