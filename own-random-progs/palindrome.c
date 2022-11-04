#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int isPalindrome(char* str, int len) {
    for(int i = 0; i < len/2; i++) {
        if(str[i] != str[len-i-1]) return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    char str[50];
    printf("Enter a string: ");
    scanf("%s", str);
    int len = strlen(str);
    if(isPalindrome(str, len)) printf("The string is a palindrome! :D\n");
    else printf("The string is not a palindrome! :C\n");

}