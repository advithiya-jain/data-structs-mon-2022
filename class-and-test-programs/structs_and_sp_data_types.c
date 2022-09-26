#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv) {
    int *a;
    int n = 10;
    int i;

    a = malloc(n * sizeof(int));

    for(i = 0; i < n; i++) {
        a[i] = i;
        printf("%d\n", a[i]);
    }

    return 0;
}