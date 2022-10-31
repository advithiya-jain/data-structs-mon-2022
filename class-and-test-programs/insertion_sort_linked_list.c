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
    printf(". :D \n");
}

//Function to free a Linked list
void freeLinkedList(Node* head){
    Node* prevNode;
    while(head) {
        prevNode = head;
        head = head->next;
        free(prevNode);
    }
}

/**
 * ! Function to add/append values to a linked list
 * @param head is a pointer to the head of the linked list
 * @param value is the value to be added to the linked list
 * */ 
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

/**
 * ! Function to insertion sort a given linked list
 * @param head is a pointer to the head node of the linked list
*/
void insertionSortLinked(Node** head) {
    Node* sortedHead = malloc(sizeof(Node)); // A head for the sorted part of the linked list
    Node* nextNode; // Node that stores the next node to be compared
    Node* temp; // temp node that starts at the sorted head and is incremented through the loop
    // loop runs till the head is NULL
    while((*head)){
        // Setting the nextNode to the node after the head
        nextNode = (*head)->next;
        // setting the temp node to the sortedHead (this has to be done every time the loop is run since we always need the starting node of the sorted list)
        temp = sortedHead;
        // loop that runs till the node after temp exists and if the value at that node is less than that of the head
        while(temp->next && temp->next->value < (*head)->value) { 
            temp = temp->next; // Incrementing/moving forward one node till the above condition is true
        } 
        // Now we set the the node after the head node to the node after the tempNode 
        // (this happens after the second while loop to make sure only the correct value is being inserted)
        (*head)->next = temp->next;
        // Set the node after the temp node to the head node
        temp->next = (*head); 
        // set the head to be the nextNode (move forward in the list)
        (*head) = nextNode; 
    }
    // after the main loop is finished, the array is sorted so we set the given head to the sortedHead.
    (*head) = sortedHead;
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
    //calling insertionSortLinked function to sort the linked list
    insertionSortLinked(&linked_list);
    //printing the sorted linked list
    printf("Your sorted linked list is: ");
    printLinked(&linked_list);
    // Freeing the linked list
    freeLinkedList(linked_list);
    return 0;
}