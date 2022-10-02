#include<stdlib.h>

struct nodeType {
    int value;
    struct nodeType* next;
};

// making Node a nodeType struct for easier typing. basically a shortcut.
typedef struct nodeType Node;

//Assuming the linked list already has data and blocks.
int main() {
    //Assuming a linked list has been provided of type nodeType with the variable name: linked_list
    Node *single_counter = linked_list;
    Node *double_counter = linked_list;
    //While loop that runs only if single_counter, double_counter and double_counter->next are not NULL.
    while(single_counter && double_counter && double_counter->next) {
        //Moving 1 block ahead with the single_counter
        single_counter = single_counter->next;
        //Moving 2 blocks ahead with the double counter
        double_counter = double_counter->next->next;
        //Checking if single_counter and double_counter ever point to the same block
        if(single_counter == double_counter) {
            printf("Loop detected! Your linked list is eating itself :`( ");
            return 0;
        }
    }
    //If while loop terminates and nothing is return, no loop is found since the 2 counters 
    //never pointed to the same block.
    printf("Congratulations! Your linked list does not eat itself!");
    return 0;
}