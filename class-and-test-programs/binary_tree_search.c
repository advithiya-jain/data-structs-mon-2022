#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node {
	int val;
    // These 2 data values are used to do binary search tree, which has left and right branches.
	struct node * left;  // smaller
	struct node * right; // larger
}node;

/**
 * ! Function to create a node for a binary search tree
*/
node* createNode(int val) {
	node* root = malloc(sizeof(node));
	root->val = val;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/**
 * ! Function to insert an integer value 'val' into a given binary search tree
*/
node* insert(node* root, int val) {

	if(root==NULL) return createNode(val);

	if (val < root->val) root->left = insert(root->left , val);
	else if (val > root->val) root->right = insert(root->right, val);

	return root;
}

/**
 * ! Function to print a binary tree 'horizontally' where the root starts from the left
 * @param dist is used to create distance between the elemetns being printed using spaces
*/
void printHorizontal(node* root, int dist)
{
 
    if (root == NULL) return; // if the current node is NULL then we just return.

    // Every time the function runs we add 5 to the 'dist' counter 
	// to increase the distance between the elements being printed
    dist += 10;

	// Recursing to the right branch, this reaches the last right branch and prints it
    printHorizontal(root->right, dist);

	// Actual printing happens here
    printf("\n");
    for (int i = 10; i < dist; i++) printf(" "); // Printing 'dist' number of spaces
    printf("%d\n", root->val); // then printing the value
 
    // Now we recurse to the left branch
    printHorizontal(root->left, dist);

}

// ! Function to print a tree using inorder traversal
void printInorder(node* root) {
	if(root->left) printInorder(root->left);       
	if(root) printf(" %d ", root->val);
	if(root->right) printInorder(root->right);
}

/**
 * ! Function to generate a binary search tree from a given array 'a' of size 'n'
*/
node* generateBST(node* root, int* a, int n) {
	root = insert(root, a[0]); // Inserting the first element of the array as the root

	//generating the tree by inserting the i'th element of the array
	for(int i = 1; i < n; i++){
		insert(root, a[i]);
	}
	// Finally return the generated tree.
	return root;
}

// ! Function to generate an array of given size 'n'
int* generateArray(int n) {
    // Creating a temporary array to use 
    int* temp = malloc(n * sizeof(int));
    if(temp) {
        for (int i = 0; i < n; i++)
        {
            temp[i] = rand()%100; // using rand()%1000 to limit the number of digits in each element to 3.
        }
    }
    return temp; // returning the generated temp array.
}

/**
 * ! Function to print an array
 * @param a here is a an integer array (or int pointer to the first index of array 'a')
*/ 
void printArray(int* a, int n) {

    for (int i = 0; i < n; i++)
    {
        printf(i?", %d":"%d", a[i]);
    }
    printf(". :D\n");
    
}

int main(int argc, char** argv){
	int* a; // Array to be genereated
    int n, flag = 0; // n = length of array. flag is a test variable for taking input
	node* root = NULL; // Initialising an empty tree

    srand(time(NULL)); // Initialising srand to use the current time in seconds as the seed.

	do { // Using a do while loop to keep asking for input in case of an invalid input
        printf("Enter size of the array: ");
        scanf("%d", &n);
        if(n < 1){ printf("Invalid input >:(\n"); flag = 1; }
    }while(flag == 1);

	a = generateArray(n);
    printf("\nYour randomly generated array is: ");
    printArray(a, n);

	// Generate tree from array
	root = generateBST(root, a, n);
	// Print the generated tree 
	printf("\nYour generated tree from the array is: \n");
	printHorizontal(root, 0); // giving an initial distance of 0 as the first element must print on the left
}