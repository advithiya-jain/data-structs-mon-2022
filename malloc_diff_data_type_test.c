#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int *a;
    char *b;
    int i;
    a = malloc(1000 * sizeof(int));
   // printf("%d\n", *(a+1001)); 
   // can also be written as a[999] or a[0] 
   printf("All vaules of a:\n\n");
   for (i = 0; i < 1000; i++){
        a[i] = i;
        printf("%d\n", a[i]);
   }
    b = (char*)a;
    i = 0;
   printf("\nAll vaules of a accessed through b (character pointer):\n\n");
    while(i<3997){
        printf("%d\n", *(b+i));
        i+=4;
    }
    free(a);
}