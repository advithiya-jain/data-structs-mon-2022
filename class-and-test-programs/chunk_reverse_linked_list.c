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

//Fucntion to add values to the end of a linked list (append).
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

/*TODO: Chunk reverse a linked list where the chunk size 'k' is input by the user.
        Ex: input: 1->2->3->4->5->6->7->8->9->10->11->NULL, k = 3
           output: 3->2->1->6->5->4->9->8->7->11->10->NULL

        Algorithm:
                    # Initialise nodes to be used
                    Node* prevNode, nextNode = NULL
                    Node* currentNode = head;
                    # Initialise counter variable to 0 
                    # (used to check how many nodes have been reversed according to chunk size)
                    ctr = 0
                    while(currentNode != NULL AND ctr<k):
                            # reversal logic, see: reverse_linked_list.c
                            nextNode = currentNode->next;
                            currentNode->next = prevNode;
                            prevNode = currentNode;
                            currentNode = nextNode;
                            #increment counter by one to indicate a reversal
                            ctr++;
                    
                    # Outside while loop. next points to the element at address k+1 
                    # so we set the new head->next to a recursive call to this function, passing
                    # nextNode as the head this time.
                    if(nextNode != NULL):
                        head->next = chunkreverse(nextNode, k)
                    # after recursive calls, the previous node now points to the start of list 
                    # (see: reverse_linked_list.c) so we return the previous Node
                    return prevNode
                    
*/
Node* chunkReverseLinkedList(Node *head_addr, int k) {
    // initialising nodeType variables
    Node* prevNode = NULL;
    Node* nextNode = NULL;
    Node* currentNode = head_addr;
    int ctr = 0;

    while(currentNode != NULL && ctr < k) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
        ctr++;
    }
    
    if(nextNode != NULL)
        head_addr->next = chunkReverseLinkedList(nextNode, k);
    
    return prevNode;
}


int main(int argc, char** argv) {
    //Initialise variables to be used
    Node *linked_list = NULL;
    int n, k, flag = 0;
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
            printf("Enter chuck size: ");
            scanf("%d", &k);
            if(k < 0){
                printf("Invalid chunk size >:(\n");
                flag = 1; // set flag to 1 so the loop repeats.
            }
            else {
                flag = 0;
            }
        }
    }while(flag == 1);
    //calling userLinkedList function to take user input for values in the linked list.
    userLinkedList(&linked_list, n);
    //printing the created linked llist
    printf("Your created linked list is: ");
    printLinked(&linked_list);
    // Printing prompt before printing the reversed linked list
    printf("Congratulations! Your chunk reversed list is: ");
    //Checking if k = 0, if so just printing the linked list as it is.
    if(k == 0){
        printLinked(&linked_list);
    }
    else {
        //chunk reversing the list using the chunkReverseLinkedList() function
        linked_list = chunkReverseLinkedList(linked_list, k);
        // Printing the chunk reversed linked list.
        printLinked(&linked_list);
    }
    // freeing space used up by the linked list.
    freeLinkedList(linked_list);
    return 0;
}