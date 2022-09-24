#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int *a;
    char *b;
    int i;
    //Using 100 instead of 1000 because character pointer arrays cap out at 512 indeces. (Could use 127 too)
    a = malloc(100 * sizeof(int));
   // can also be written as a[999] or a[0] 
   printf("All vaules of a:\n\n");
   for (i = 0; i < 100; i++){
        a[i] = i;
        printf("%d\n", a[i]);
   }
    b = (char*)a;
    i = 0;
   printf("\nAll vaules of a accessed through b (character pointer):\n\n");
   // 397 is 99*4 since we have to move 4 locations (characters use 1 byte while integers use 4)
    while(i<397){
        printf("%d\n", *(b+i));
        i=i+4; // incrementing i by 4 (same reason as above).
    }
    //getting a weird output where it goes from 0 to 127 then -128, -127, -126... back to 0
    //this cycle continues till the 999th index - this is if the integer pointer array has 100 indeces.
    free(a);
}