#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv) {
    int *a;
    int i, n, val;
    n = 3;
    a = (int *) malloc(n * sizeof(int));

    // Enter Data
    scanf("%d", &val);
    i = 0;
    while(val > 0) {
        // do stuff
        a[i] = val;
        i++;
        if(i >= n) {
            // doubling size of array
            n = n*2;
            // reallocating a to double the size of earlier (size is stored in 'n')
            a = (int *) realloc(a, n * sizeof(int)); 
        }
        scanf("%d", &val);
    }
    // this to make sure the number of locations do not exceed the entered +ve numbers. This is to prevent
    // extra data being printed and allocated to a. 
    n = i;
    a = realloc(a, n * sizeof(int));

    // Print Data
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n\nDone!\n");

    return 0;
}