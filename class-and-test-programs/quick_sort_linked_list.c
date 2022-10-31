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

/**
 * ! Helper function to quick sort a linked list for the partitions.
 * * This function takes in the last node of the linked list and places all nodes with values less than the
 * * pivot to the left of the pivot and all nodes with values greater than the pivot to the right of the pivot.
 * ! This function is called by quickSort() to sort the linked list.
 * @param head is the head node of the linked list.
 * @param last is the last node of the linked list.
 * @return the new pivot node.
 */
Node* partition(Node* head, Node* last) {
    // Initialise variables for: pivotNode, current Node and a temp variable to swap the values later
    Node* pivotNode = head;
    Node* currentNode = head;
    int t = 0; 
    // While loop that runs till currentNode is NULL and currentNode is not the last node
    while(currentNode && currentNode != last) {
        // If the value of the current node is less than the last node
        if(currentNode->value < last->value) {
            // Set the pivotNode to the head node
            pivotNode = head;
            // Swap the values of the head node and the current node
            t = head->value;
            head->value = currentNode->value;
            currentNode->value = t;

            // Set the head node to the next node
            head = head->next;
        }
        // Move the current node to the next node
        currentNode = currentNode->next;
    }
    // Swap the values of the head node and the last node after the while loop finishes
    t = head->value;
    head->value = last->value;
    last->value = t;
    // Return the new pivot node
    return pivotNode;
}

/**
 * ! Function to quick sort a given linked list
 * @param lower takes in the lower index to start with
 * @param higher takes in the higher index to end with
*/
void quickSortLinked(Node* head, Node* last){
    // If the head node is the last node currently then we return, the sorting is complete.
    if (head == last) return;
    // Setting the pivot node as the value recieved from the partition function.
    Node* pivot = partition(head, last);
    // If the pivot node is not NULL we recursively call the quickSort from the node after the pivot till the last node
    if (pivot && pivot->next) quickSortLinked(pivot->next, last);
    // If the head node is not the pivot node we recursively call the quickSort from the head node till the pivot node.
    if (pivot && head != pivot) quickSortLinked(head, pivot);
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
    // Finding the last node of the linked list
    Node* last = linked_list;
    while(last->next != NULL) {
        last = last->next;
    }
    //calling quickSort function to sort the linked list
    quickSortLinked(linked_list, last);
    //printing the sorted linked list
    printf("Your sorted linked list is: ");
    printLinked(&linked_list);
    // Freeing the linked list
    freeLinkedList(linked_list);
    return 0;
}