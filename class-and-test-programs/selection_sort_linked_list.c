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

//Function to free a Linked list
void freeLinkedList(Node* head){
    Node* prevNode;
    while(head) {
        prevNode = head;
        head = head->next;
        free(prevNode);
    }
}

//Fucntion to add values to the end of a linked list (append). val is user input.
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
    //Initialise variables for: length of list, user input value, head node and temp_node of linked list.
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

//TODO: Make a function selectSortLinked(Node** head) that selection sorts a given linked list.
void selectSortLinked(Node** head) {
    // Using a temporary node and a temp variable
    Node* temp = *head;
    int t = 0;
    //Runs till the end of the list
    while(temp != NULL) {
        //Initialising the values for the minimum value & the nextNode i.e. j+1 in a normal selection sort
        Node* min_val = temp;
        Node* nextNode = temp->next;
        //Runs from the nextNode till the end of the list, 
        while(nextNode != NULL) {
            //Checking if the minimum value is greater than the current(nextNode's) value
            if(min_val->value > nextNode->value) {
                //Updating the minimum value if it is true
                min_val = nextNode;
            }
            //Updating the value of the current(nextNode)
            nextNode = nextNode->next;
        }

        //Swapping values after the inner loop has run.
        t = temp->value;
        temp->value = min_val->value;
        min_val->value = t;
        //Updating the temp node to point to the next node (move forward in the list to sort)
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
    printf("Your created linked list is: ");
    printLinked(&linked_list);
    //Sorting the list
    selectSortLinked(&linked_list);
    //printing the sorted list
    printf("Congratulations! Your sorted list is: ");
    printLinked(&linked_list);
    freeLinkedList(linked_list);
    return 0;
}