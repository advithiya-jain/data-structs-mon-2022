#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

/*************************************************** FOR QUEUES *****************************************************/
struct node {
    int val;
    struct node* next;
};
// Defining a node struct to be used for queues.
typedef struct node node;

typedef struct queue{
    node* head;
    node* tail;
} queue; // Defining and typedef a struct queue. A queue has a head and a tail which are of both type struct node

/**
 * ! Function to initialise an empty queue
 * we set head and tail to NULL, as currently the queue is empty. This makes it easier to create new queues.
*/
queue* initQueue(queue* q){
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/**
 * ! Function to add items to the queue
 * @param val is the int to be added to the queue
 * @param q is the queue to be enqueued.
*/
void enqueue(queue* q, int val) {
    node* temp = malloc(sizeof(node)); // Allocating space for a new node in the queue
    temp->val = val; // setting the value of this new node as val
    temp->next = NULL; // The next node should be null as this is going to be the new 'tail'

    // If there is a pre existing tail, we have to make it point to this new tail.
    if (q->tail) { q->tail->next = temp; }
    // Now we update the tail to be this new node, as we are adding it to the end of the queue.
    q->tail = temp;
    //Now we need to check if we enqueued to an empty list
    // if it is then we have to set the head to point to this node as well. As there is only 1 node in the queue.
    if(q->head == NULL) {q->head = temp;} 
}

/**
 * ! Function to remove items from the queue
 * @param q is the passed q we have to dequeue.
 * * There is no @param val here since we are removing a node and returning the value at that node (return type int).
 * ? Need to figure out a way to store negative integers and still throw an error if the queue is empty
*/
int dequeue(queue* q){
    int val; // Used to store the value that has been dequeued.
    // If the queue is empty i.e. head is null then we return -1 to indicate a failure in dequeueing.
    if(q->head == NULL) {return -1;}
    
    val = q->head->val; // Storing the value at the head in val to be returned later.
    //Now we have to dequeue the queue and 'remove' the head.
    q->head = q->head->next; // making head point to the next value as the current one has been removed.
    // If this is now an empty queue after dequeueing then we have to reset the head and tail to NULL;
    if(q->head == NULL) {q->tail = NULL;}

    return val; //returning the value from the node that was dequeued.
}

/**
 * ! Function to check if a queue is empty
 * @return bool type, true if the queue is empty, else false
*/
bool isEmpty(queue* q){
    if(q->head == NULL && q->tail == NULL) {return true;}
    else {return false;}
}

/************************************************** END OF QUEUE ****************************************************/

// ! Function to generate an array of given size 'n'
int* generateArray(int n) {
    // Creating a temporary array to use 
    int* temp = malloc(n * sizeof(int));
    if(temp) {
        for (int i = 0; i < n; i++)
        {
            temp[i] = rand()%1000; // using rand()%1000 to limit the number of digits in each element to 3.
        }
    }
    return temp; // returning the generated temp array.
}

/**
 * ! Function to generate a queue from an array 'a' of size 'n'
 * @return queue*, to return  the genereated queue
*/
queue* queueFromArray(int* a, int n){
    queue* q = malloc(sizeof(queue));
    q = initQueue(q);
    if(n > 0){
        // Starting i from first index of array until the last index
        for (int i = 0; i < n; i++)
        {
            enqueue(q, a[i]);
        }
    }
    return q;
}

/**
 * ! Function to generate a queue from an array 'a' of size 'n' in reverse
 * @return queue*, to return  the genereated queue
*/
queue* queueFromArrayReverse(int* a, int n){
    queue* q = malloc(sizeof(queue));
    q = initQueue(q);
    if(n > 0){
        // Starting i from the last index (n-1) and going to the first index.
        for (int i = n-1; i >= 0; i--)
        {
            enqueue(q, a[i]);
        }
    }
    return q;
}

/**
 * ! Function to print an array
 * @param a here is a an integer array (or int pointer to the first index of array 'a')
*/ 
void printArray(int* a, int n) {

    for (int i = 0; i < n; i++)
    {
        printf(i?" [%d]":"[%d]", a[i]);
    }
    printf(" :D\n");
    
}

/**
 * ! Function to print a queue
 * @param q is the queue that is to be printed (we have to dequeue to print)
*/
void printQueue(queue* q) {
    int val;
    queue* temp = q;
    while(temp->head){
        val = dequeue(temp);
        printf(isEmpty(q)?"%d":"%d<-", val);
    }
    //printf("\b");
    printf(" :DD\n");
}

int main(int argc, char** argv) {
    int n, flag = 0;

    srand(time(NULL));

    do {
        printf("Enter size of array: ");
        scanf("%d", &n);
        
        if(n < 1) {flag = 1; printf("Invalid Input >:C\n");}

    }while(flag == 1);
    // generating an array with random 
    int *a = generateArray(n);
    // Printing the array to show the values
    printf("\nYour generated array is: ");
    printArray(a, n);
    // generating the queue to be tested
    queue* q = queueFromArray(a, n);
    // dequeueing values by printing to test
    printf("\nYour generated (dequeued) queue is: ");
    printQueue(q);
    // generating a reversed version of the array into a queue
    q = queueFromArrayReverse(a, n);
    // printing the reversed queue
    printf("\nYour (array) reversed version of the (dequeued) queue is: ");
    printQueue(q);

    free(q);
    return 0;
}