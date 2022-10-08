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
    //Set address of the next node to NULL to indicate it is the last node.
    temp_node->next = NULL;
    //If the current head address is null (i.e the last node) set it to the newly created node
    if(*head_addr == NULL){
        *head_addr = temp_node;
    }
    //Else we find the previous node and make it point to the newly created node
    else {
        Node *prevNode = *head_addr;
        // loop runs till the 2nd last node (as the lost node will be NULL)
        while(prevNode->next != NULL) {
            prevNode = prevNode->next;
        }
        //making the prevoius node point to the newly created node.
        prevNode->next = temp_node;
    }
}

// Function that takes in user input for linked list values and creates a linked list.
void userLinkedList(Node** head, int n){
    //Initialise variables for: length of list, user input data, head node and temp_node of linked list.
    int val, i;
    //head = NULL;
    //While loop that runs till the user input length of list
    i = 0;
    while(i < n){
        //take user input for the value.
        printf("Enter value of node %d: ", i+1);
        scanf("%d", &val);
        //call addValue function to add values into the list
        addValue(head, val);
        //printf("%d\n", head->value);
        //increment i by 1 to indicate that a node has been added
        i++;
    }
}

// Function to print all values of a given linked list
void printLinked(Node** head) {
    Node *temp = (*head);
    while(temp != NULL){
        printf("%d,", temp->value);
        temp = temp->next;
    }
}

int main(int argc, char** argv) {
    Node *linked_list = NULL;
    int n, flag = 0;
    // Do while loop to keep asking for input if the list size entered is invalid
    do{
        //Take user input for the length of the list
        printf("Enter length of linked list: ");
        scanf("%d", &n);
        if(n <= 0){
            printf("Invalid list size >:(\n");
            flag = 1; // set flag to 1 so the loop repeats.
        }
        else {
            flag = 0;
        }
    }while(flag == 1);
    //calling userLinkedList function to take user input for values in the linked list.
    userLinkedList(&linked_list, n);
    //printing the created linked llist
    printf("Congratulations! Your created linked list is: ");
    printLinked(&linked_list);
    // Print statement for aesthetics
    printf("\b. :D \n");
    free(linked_list);
    return 0;
}