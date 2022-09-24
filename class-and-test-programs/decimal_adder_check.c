#include <stdio.h>

int main(){
  float sum = 0;
  sum = (0.00001) + 2.000051;
  // Tried with the smallest numbers I could.
  // Still couldnt get the error to show up for me. 
  // Changes can be seen in the commit history.
  printf("%f\n", sum);
  return 0;
}
