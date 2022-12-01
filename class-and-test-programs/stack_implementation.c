#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>


/*************************************************** FOR STACKS *****************************************************/
typedef struct node {
    int val;
    struct node* next;
}node;

// ! Function to check if a stack is empty
bool isEmpty(node* top) {
    return (top == NULL);
}

/**
 * ! Function to add values to the stack
 * *Stacks work in accordance with the LIFO (Last in First Out) rule.
 * *so we essentially 'push' nodes onto the top as this is what will be accessed first.
 * @param top type struct node* - The top of the stack to be pushed to.
 * @param val type int - the value to be pushed
 * @return bool - to indicate success or failure of adding a vallue to the stack 
*/
bool push(node** top, int val) {
    // Using a temporary node to add the value into the stach
    node* temp = malloc(sizeof(node));
    if(temp == NULL) return false;
    // Now assign the given value to this node
    temp->val = val;
    /** Now we have to make the temp the new top, so we:
     * 1. Make it point to the current top and then,
     * 2. Set the temp node as the new top
    */
   temp->next = (*top);
   (*top) = temp;
   return true;
} 

/**
 * ! Funtion to remove and access the top value of the stack.
 * * We remove and return (pop) the top value of the stack to maintain the LIFO rule.
 * * If the stack is empty the functioin returns an INT
 * @param top type struct node* - The top of the stack to be accessed
 * @return long long int - To return the value that was removed (using long long int to check for errors 
 * it returns a INT64_MIN value if the stack is empty).
*/
long long int pop(node** top) {
    if(isEmpty((*top))) return INT64_MIN; // Return the minimum long long int value if the stack is empty.
    // else the stack isn't empty so we pop the first value.
    
    // since the value in the stack is an int we have to type case it to a long long int to store the result
    long long int result = (long long int)((*top)->val);
    // making a temp node to store the top (this is used to free the top node after popping it)
    node* temp = (*top);
    (*top) = (*top)->next; // now we point the top to the next node as we are 'popping' the top.
    free(temp); // freeing the old top by freeing temp, succesfully popping it.
    return result; // returning the value of the old top.
}

/**
 * ! Function to print the values of the stack
*/
void printStack(node* top) {
    if (isEmpty(top)) printf("\nThe stack is currently empty.\n");
    else {
        printf("\n");
        while(top) {
            printf("%d->", top->val);
            top = top->next;
        }
        printf("NULL\n");
    }
}

// ! Function to free all memory allocated to a given stack
void freeStack(node* top){
    node* prevNode;
    while(top) {
        prevNode = top;
        top = top->next;
        free(prevNode);
    }
}

int main(int argc, char** argv) {
    node* stack = NULL;
    long long int t;
    int opt = 0;

    printf("Welcome to this (mostly useless) stack editing program.\nUsing the Menu of options, you can perform all stack functions on a created stack.\n");
    while(opt != 5){

        printf("\nMenu\n1: Push\n2: Pop\n3: Display stack\n4: Empty stack\n5: Exit\n(enter one of these numbers to perform the corresponding action): ");
        scanf("%d", &opt);
        switch(opt){
            case 1: printf("Enter an int value to be pushed onto the stack: ");
                    scanf("%lld", &t);
                    push(&stack, t);
                    break;

            case 2: if((t = pop(&stack)) != INT64_MIN) printf("\nThe top value of '%lld' has been popped. :D\n", t);
                    else printf("\nThe stack is empty! :C\n");
                    break;

            case 3: printStack(stack);
                    break;

            case 4: // If the stack is not empty, we free it.
                    if(!(isEmpty(stack))) {
                        // Emptying the stack using the pop function in a while loop
                        while((t = pop(&stack)) != INT64_MIN);
                        printf("\nThe stack has been emptied.\n");
                    }
                    // Else the stack is already empty.
                    else printf("\nThe stack is already empty.\n");
                    break;
                    
            case 5: break;
            
            default: printf("\nInvalid option entered! >:C\n");
                    break;
        }
    }
    
    printf("\nThank you for using this (mostly useless for you) stack editor program! :D\n");

    freeStack(stack);
}