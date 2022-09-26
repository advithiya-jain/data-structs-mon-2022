#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Initialising a 2d-array of the alphabet that will be used to check against the entered string.
char alph[26][2] = {{'A','a'}, {'B','b'}, {'C','c'}, {'D','d'}, {'E','e'}, {'F','f'}, {'G','g'}, 
{'H','h'}, {'I','i'}, {'J','j'}, {'K','k'}, {'L','l'}, {'M','m'}, {'N','n'}, {'O','o'}, {'P','p'}, 
{'Q','q'}, {'R','r'}, {'S','s'}, {'T','t'}, {'U','u'}, {'V','v'}, {'W','w'}, {'X','x'}, {'Y','y'}, {'Z','z'}};

// Program that takes the birth day and name of the user as input. 
// Then removes the charcaters in the name coinciding with the birthday. 1 = A/a, 2 = B/b, ... 26 = Z/z. 
// Beyond 26, the list overflows back onto A/a. so 27 = A/a, ... 31 = E/e.
int bday_rem(char name[], int bday) {
  // Storing length of the user's name. sizeof() gives the size of the array which is divided by the 
  // size of one element in the array, arr[0] is used for Simplicity.
  int len = strlen(name);
  // Stores the character that must be removed.
  char rem[2]={0,0};
  // Stores new name.
  char new_name[50];
  // Checking if the date overflows after 26.
  if(bday > 26) {
    bday = bday - 26;
  }
  switch(bday){
    case 1: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 2: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 3: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 4: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 5: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 6: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 7: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 8: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 9: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 10: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 11: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 12: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 13: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 14: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 15: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 16: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 17: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 18: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 19: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 20: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 21: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 22: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 23: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 24: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 25: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    case 26: rem[0] = alph[bday-1][0]; rem[1] = alph[bday-1][1];
    break;
    default: printf("Invalid bday entered. Exiting...\n"); return -1;
    break;
  }
  int i;
  int j = 0;
  // Loop to go through the entered name.
  for(i = 0; i < len; i = i + 1) {
    // Condition to check if the current letter is not the one coinciding with the birthday.
    if(name[i] != rem[0] && name[i] != rem[1]) {
      // Checking to see if the current character is not a 1. return input (Enter), 2. new line.
      // This is to preserve white-spaces in full names without adding these special characters.
      if(name[i] != '\n' && name[i] != '\r'){
        new_name[j] = name[i];
        j++;
      }
    } 
  }
  // Making sure the new_name string ends with a \0 so c knows when to stop printing. This prevents 
  // random data being printed to the end of the string.
  new_name[j] = '\0';
  // Print the new name.
  int new_len = strlen(new_name);
  if(new_len != len){
  printf("Your new name is: %s\n", new_name);
  }
  else{
    printf("Your name is still: %s\n", name);
  }
  return 0;
}

int main(){
  char name[50];
  int bday;
  printf("Enter your name: ");
  scanf("%[^\n]s", name);
  printf("Enter the day you were born on: ");
  scanf("%d", &bday);
  if(bday_rem(name, bday) == 0){
    return 0;
  }
  else{
    return -1;
  }
}