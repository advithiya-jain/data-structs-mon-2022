#include <stdio.h>
#include <stdlib.h>

void stressTest(){
  float x;
  int ctr = 1;
  for(x = 0.0; x < 0.1; x = x + 0.01) {
    printf("%f\n", x);
    printf("%d\n", ctr);
    ctr = ctr + 1;
  }
}

void normalLoop(){
  float y;
  int ctr = 1;
  for(y = 0; y < 10; y = y + 1) {
    printf("%f\n", y);
    printf("%d\n", ctr);
    ctr = ctr + 1;
  }
}

int main(int argc, char** argv) {
  //printf("Option 1: Normal loop that runs 10 times.\nOption 2: Stress test C using decimal values for the loop variable.\n");
  //int option;
  //printf("Enter option: ");
  int arg = atoi (argv[1]);
  if (argc > 2) {
    printf("Only 1 number must be passed as an argument. 1 for the normal loop and 2 for the stress test.");
    return -1;
  }
  if (arg == 2) {
    stressTest();
  }
  else if (arg == 1){
    normalLoop();
  }
  else{
    printf("Invalid argument. Allowed Arguments are:\n1 for the normal loop and 2 for the stress test.\n");
  }
  return 0;
}
