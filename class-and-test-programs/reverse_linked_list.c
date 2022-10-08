#include<stdlib.h>
#include<stdio.h>

//Creating a new struct called nodeType to create linked lists with nodes.
struct nodeType {
    int value;
    struct nodeType* next;
};

// making Node a nodeType struct for easier typing. basically a shortcut.
typedef struct nodeType Node;

// Function to print all values of a given linked list
void printLinked(Node** head) {
    Node *temp = (*head);
    int i = 0;
    while(temp != NULL){
        printf(i?", %d":"%d", temp->value);
        temp = temp->next;
        i++;
    }
    printf(". :D\n");
}

// Function to add values to the end of the linked list (append)
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

/*
TODO: Create a function that takes a linked list as an input, reverses it and returns a reversed list.
preliminary Algorithm: 
    initialise 3 nodes: the current node, the node before that, and the node after.
    # Run a loop till the current loop is NULL
    while (current node != NULL):
        # make the next node point to the node after current
        nextNode = currentNode->nextNode
        # make the next value of current node point to the previous node (reverse its pointer)
        currentNode->next = previousNode
        # Make the previous node the current node to move 1 place ahead in the list
        previousNode = currentNode
        # Make the current Node the next Node for the same reason as above.
        currentNode = nextNode
    # outside the while loop, make the head of the list point to the previous node (as the list is now reversed)
    head = previousNode
*/
Node* reverseLinkedList(Node **head_addr) {
    // initialising nodeType variables
    Node* prevNode = NULL;
    Node* nextNode = NULL;
    Node* currentNode = *head_addr;

    while(currentNode != NULL) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    (*head_addr) = prevNode;
    return (*head_addr);
}

int main(int argc, char** argv){
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
    //Printing original Linked List
    printf("Your original linked list is: ");
    printLinked(&linked_list);
    //Creating new empty list to store the value of the reversed linked list.
    Node *rev_list = NULL;
    //calling reverseLinkedList to reverse the inputted linked list.
    rev_list = reverseLinkedList(&linked_list);
    //printing reversed linked list
    printf("Your reversed linked list is: ");
    printLinked(&rev_list);
    free(rev_list);
}