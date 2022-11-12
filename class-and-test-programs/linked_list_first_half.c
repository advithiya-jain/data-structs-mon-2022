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
void printLinked(Node** head, Node** tail) {
    Node *temp = (*head);
    int i = 0;
    while(temp != (*tail)){
        printf(i?"->%d":"%d", temp->value);
        temp = temp->next;
        i++;
    }
    printf(".\n");
}

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
Node* firstHlaf(Node* linked_list) {
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
    }
    return single_counter;
}

int main(int argc, char** argv) {
    //Assuming a linked list with data of type: nodeType, with name: linked_list, exists.
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
    linked_list = userLinkedList(linked_list, n);
    //calling firstHalf function to get the node of the end of the first half of the list.
    Node* end_of_first_half = firstHlaf(linked_list);
    printf("\nThe first of the linked list is: ");
    printLinked(&linked_list, &end_of_first_half);
    free(linked_list);
    return 0;
}