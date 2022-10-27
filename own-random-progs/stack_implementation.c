#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>


/*************************************************** FOR STACKS *****************************************************/
typedef struct node {
    int val;
    struct node* next;
}node;

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
    if((*top)== NULL) return INT64_MIN; // Return the minimum long long int value if the stack is empty.
    // else the stack isn't empty so we pop the first value.
    
    // since the value in the stack is an int we have to type case it to a long long int to store the result
    long long int result = (long long int)((*top)->val);
    // making a temp node to store the top (this is used to free the top node after popping it)
    node* temp = (*top);
    (*top) = (*top)->next; // now we point the top to the next node as we are 'popping' the top.
    free(temp); // freeing the old top by freeing temp, succesfully popping it.
    return result; // returning the value of the old top.
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
    push(&stack, 5);
    push(&stack, 7);
    push(&stack, 3);
    push(&stack, 9);

    if((t = pop(&stack)) != INT64_MIN) {printf("%lld\n", t);}
    if((t = pop(&stack)) != INT64_MIN) {printf("%lld\n", t);}
    if((t = pop(&stack)) != INT64_MIN) {printf("%lld\n", t);}
    if((t = pop(&stack)) != INT64_MIN) {printf("%lld\n", t);}
    if((t = pop(&stack)) != INT64_MIN) {printf("%lld\n", t);}
    if((t = pop(&stack)) != INT64_MIN) {printf("%lld\n", t);}

    freeStack(stack);
    
}