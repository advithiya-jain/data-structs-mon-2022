#include<stdlib.h>
#include<stdio.h>

//Creating a new struct called nodeType to create linked lists with nodes.
struct nodeType {
    int value;
    struct nodeType* next;
};

// making Node a nodeType struct for easier typing. basically a shortcut.
typedef struct nodeType Node;

//TODO: Create a function that allows me to add values to a linked list using user input to test this
//      program.
//The int val will be user input data.
void addValue(Node** head_addr, int val) {
    //Allocate a temp node to input values and address into a node.
    Node* temp_node = malloc(sizeof(Node));
    //Set value of the node to the argument val
    temp_node->value = val;
    //Set address of the next node to the head_addr.
    temp_node->next = (*head_addr);
    //Set the address of the head to the created node.
    (*head_addr) = temp_node;
}

//TODO: Create a function for the user to enter the length of the linked list and enter values into it.
Node* userLinkedList(Node* head, int n){
    //Initialise variables for: length of list, user input data, head node and temp_node of linked list.
    int val, i;
    head = NULL;
    //While loop that runs till the user input length of list
    i = 0;
    while(i < n){
        //take user input for the value.
        printf("Enter value of node %d: ", i+1);
        scanf("%d", &val);
        //call addValue function to add values into the list
        addValue(&head, val);
        //increment i by 1 to indicate that a node has been added
        i++;
    }
    return head;

}

//Function to check if a linked list is looped onto itself.
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

int main(int argc, char** argv) {
    //Assuming a linked list with data of type: nodeType, with name: linked_list, exists.
    Node *linked_list = NULL;
    int n;
    //Take user input for the length of the list
    printf("Enter length of linked list: ");
    scanf("%d", &n);
    //calling userLinkedList function to take user input for values in the linked list.
    linked_list = userLinkedList(linked_list, n);
    //Creating a loop in the list. Assuming the user has entered 3 as the size of the list.
    //TODO: give an option to create a loop in the list as long as length>1. 
    //      Here I am looping the list only if length==3.
    if(n == 3)
        linked_list->next->next->next = linked_list->next;
    //Calling isLooping function to check if list is looping.
    if(isLooping(linked_list) == 0) {
        printf("Congratulations! Your linked list does not eat itself! :D \n");
    }
    else {
        printf("Loop detected! Your linked list is eating itself! :`( \n");
    }
    return 0;
}