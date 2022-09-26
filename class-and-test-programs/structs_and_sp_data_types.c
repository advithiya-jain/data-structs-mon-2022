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
            n = n*2;
            a = (int *) realloc(a, n * sizeof(int));
        }
        scanf("%d", &val);
    }
    // Print Data
    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n\nDone!\n");

    return 0;
}