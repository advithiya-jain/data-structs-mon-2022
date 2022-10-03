#include<stdlib.h>

struct nodeType {
    int value;
    struct nodeType* next;
};

// making Node a nodeType struct for easier typing. basically a shortcut.
typedef struct nodeType Node;

int isLooping(Node* linked_list) {
    //Assuming a linked list has been provided of type nodeType with the variable name: linked_list.
    //Creating temporary counters to traverse the list.
    Node *single_counter = linked_list;
    Node *double_counter = linked_list;
    //While loop that runs only if single_counter, double_counter and double_counter->next are not NULL.
    //i.e. the counters have to be in a non-NULL node and the double_counter must point to a node that
    //doesn't have the head address of NULL (which is the last node).
    while(single_counter && double_counter && double_counter->next) {
        //Moving 1 node ahead with the single_counter
        single_counter = single_counter->next;
        //Moving 2 nodes ahead with the double counter
        double_counter = double_counter->next->next;
        //Checking if single_counter and double_counter ever point to the same node
        if(single_counter == double_counter) {
            //Return 1 if there is a loop detected, i.e. single and double counters point to the same node
            return 1;
        }
    }
    //If while loop terminates and nothing is returned, no loop is found since the 2 counters 
    //never pointed to the same node. So I return 0 to indicate no loop was found.
    return 0;
}

//TODO: Create a function that allows me to add values to a linked list using user input to test this
//      program.
int main(int argc, char** argv) {
    //Assuming a linked list of type nodeType with name linked_list exists.
    Node *linked_list;
    //Creating a loop in the list
    linked_list->next->next->next->next = linked_list->next->next
    //Calling isLooping function to check if list is looping.
    if(isLooping(linked_list) == 0) {
        printf("Congratulations! Your linked list does not eat itself! :D");
    }
    else {
        printf("Loop detected! Your linked list is eating itself! :`( ");
    }
    return 0;
}