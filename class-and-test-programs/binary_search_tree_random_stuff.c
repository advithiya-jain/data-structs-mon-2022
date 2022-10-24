#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

/*************************************************** FOR BSTs *****************************************************/

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
	root->val = val; // storing the value at the current node
	root->left = NULL; // setting the left and right branches to NULL
	root->right = NULL;
	return root; // returning the newly created node.
}

/**
 * ! Function to search a BST for the value 's'
*/
node* searchBST(node* root, int s){
	if(root) {
		if (s < root->val)      return searchBST(root->left, s);
		else if (s > root->val) return searchBST(root->right, s);
		else                    return root;
	}
	else return NULL;
}

/**
 * ! Function to insert an integer value 'val' into a given binary search tree
*/
node* insertBST(node* root, int val) {

	if(root==NULL) return createNode(val);

	if (val < root->val) root->left = insertBST(root->left , val);
	else if (val > root->val) root->right = insertBST(root->right, val);

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

void quickSort(int* a, int low, int high);

/**
 * ! Function to generate a balanced BST using a sorted array for input elements
 * * Recursively adds elements to the tree by: 
 * * 1. first using the mid element as the root and then
 * * 2. recursively doing the same thing for the left half and right half of the array
 * Since the array is in sorted order, this will give us a balanced BST
 * ? Surprised at how well this works. Maybe I should try some other stuff like this and generate trees with different structures.
*/
node* generateBSTSorted(int* a, int low, int high) {
	if (low > high) return NULL;

	int mid = (low+high) / 2;

	node* root = createNode(a[mid]);
	root->left = generateBSTSorted(a, low, mid-1);
	root->right = generateBSTSorted(a, mid+1, high);

	return root;
}

/**
 * ! Function to generate a balanced BST given a non sorted array 'a' of length 'n'
*/
node* generateBST(int* a, int n) {
	int* sorted = a;
	quickSort(sorted, 0, n-1);
	
	return generateBSTSorted(sorted, 0, n-1);
}

/**
 * ! Function to find the 'successor' value of a node in a BST
 * @param root struct node* type - The node whose successor is to be found
 * @return int - Returns an int, which is the successor value of the node passed
*/
int nodeSuc(node* root) {

	// Since we are looking for the successor of the root,
	// we have to move to the right branch which will have values larger than the current node
	root = root->right;
	// Now we loop untill we reach the 1 node before the end of the left branch
	// and keep traversing the left branch till then
	while (root->left) root = root->left;
	// After the loop has ended we have reached the value that is the successor of the current node value
	return root->val; // So we just return the value at the current node.

}

/**
 * ! Fucntion to find the 'predecessor' value of a node in a BST
 * @param root struct node* type - The node whose predecessor is to be found
 * @return int - Returns an int, which is the predecessor value of the node passed
*/
int nodePre(node* root){

	// Since we are looking for the predecessor of the root,
	// we have to move to the left branch which will have values smaller than the current node
	root = root->left;
	// Now we loop untill we reach the 1 node before the end of the right branch
	// and keep traversing the right branch till then
	while (root->right) root = root->right;
	// After the loop has ended we have reached the value that is the predecessor of the current node value
	return root->val; // So we just return the value at the current node.

}

/**
 * ! Function to delete a specific element from a binary search tree.
 * * Recursive function that will also restructure the tree if the element deleted has children (or if it is the root).
 * @param root is the node address of the root element of the tree
 * @param se is the search element to be deleted
 * @return struct node* - Returns a node address type with the search element deleted from it
*/
node* deleteTreeNode(node* root, int se) {
	// If the root is NULL i.e. and empty tree we just return it back as there is nothing to be deleted.
	if (root == NULL) return root;
	// If the search element is smaller than the current value, we start deletion from the left branch
	if (se < root->val) root->left = deleteTreeNode(root->left, se);
	// If the search element is greater, than we start deletion again from the right branch
	else if (se > root->val) root->right = deleteTreeNode(root->right, se);
	// Otherwise the search element is the same as the root of the tree
	else {
		// We first check if the root has any children, if no then we just set it to NULL
		if (root->left == NULL && root->right == NULL) root = NULL;
		// else if we have a right branch then we recursively replace the current node with the successor value
		else if (root->right) { 
			root->val = nodeSuc(root);
			root->right = deleteTreeNode(root->right, root->val);
		}
		// otherwise we have a left branch only so we recursively replace the current node with the predecessor value
		else {
			root->val = nodePre(root);
			root->left = deleteTreeNode(root->left, root->val);
		}
	}
	// Now we return the modified tree (this will be used by recursive calls as well so we return the whole node)
	return root;

}

// ! Function to free memory allocated to a BST.
void freeTree(node* root){
	free(root);
}

/************************************************** END FOR BSTs ****************************************************/

/************************************************** FOR ARRAYS ****************************************************/

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

// ! Helper function for quick sort to swap values from two given int addresses
void swap (int* a, int* b){
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

/**
 * ! Helper function to quick sort an array for the partitions
 * @param lower takes in the lower index to start with
 * @param higher takes in the higher index to end with
 * * This function basically returns a 'wall' which partitions the entered array
 * */ 
int quickPartition(int* a, int lower, int higher) {
    int pivot = a[higher]; // Setting the pivot to the higher index
    int ind_of_small = lower-1; // setting the index of the smaller index to the one before the lower index

    for(int i = lower; i < higher; i++) { // loop runs from lower to higher
        if(a[i] < pivot) { // If the element at index i is lesser than that of the pivot,
            ind_of_small++;// We increment ind_of_small, so as to make it point to the next value (as it is being swapped)
            swap(&a[ind_of_small], &a[i]); // And swap the index of the smaller value with that of i.
        }
    }
    // After exiting the loop, we swap the value at the index after the one at the smallest value and
    // the higher index value
    swap(&a[ind_of_small+1], &a[higher]);
    // Returning the next pivot index, which will be the one after the smaller value index
    return (ind_of_small+1);
}

/**
 * ! Recursive function to quick sort an array
 * @param low takes the beginning index of the array (when being called for the first time)
 * @param high takes the last index of the array (when being called for the first time)
 * * Since this is a recursive function, @param low and @param high can also be inferred as the lower index
 * * to start with and the higher index to end with (respectively)
 * ! It's void since it takes in a pointer(values will be modified while the pointer remains the same)
*/
void quickSort(int* a, int low, int high) {
    // Only recurses if the low index is before the high question
    if (low < high) {
        int p = quickPartition(a, low, high); // Partitioning the array and storing the wall in p

        // This sorts the 'left' half of the array, since we're starting from the low index till the wall
        quickSort(a, low, p - 1); 
        // This sorts the 'right' half, since we're starting after the wall till the high index.
        quickSort(a, p + 1, high);
    }
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
/************************************************** END FOR ARRAYS ****************************************************/

int main(int argc, char** argv){
	int* a; // Array to be genereated
    int s, n, flag = 0; // n = length of array. flag is a test variable for taking input
	node* root = NULL; // Initialising an empty tree

    srand(time(NULL)); // Initialising srand to use the current time in seconds as the seed.

	do { // Using a do while loop to keep asking for input in case of an invalid input
        printf("Enter size of the array: ");
        scanf("%d", &n);
        if(n < 1){ printf("Invalid input >:(\n"); flag = 1; }
		/**
		 * ! Uncomment this block to use search the BST for a user input search element
		else {
			
			printf("Enter an element to be searched in the array: ");
			scanf("%d", &s);
		}
		*/
    }while(flag == 1);

	a = generateArray(n);

	// Generate tree from array
	//root = generateBSTSortedOld(root, a, n);
	root = generateBST(a, n);

	/**
	 * ! To search for an element.
	 * ! Uncomment this out and comment out lines 264-269 to use

	node* test; // Initialising a test node to be used to check if the BST contains the search element.
	if(test = searchBST(root, s)) printf("\nCongratulations! The element %d exists in the array! :D\n", s);
	else						  printf("\nBummer. The element %d does not exist in the array :C\n", s);
	*/

    printf("\nYour randomly generated array is: ");
    printArray(a, n);

	// Print the generated tree 
	printf("\nYour generated tree from the array is: \n");
	printHorizontal(root, 0); // giving an initial distance of 0 as the first element must print on the left

	printf("Enter an element to be deleted from the array: ");
	scanf("%d", &s);

	root = deleteTreeNode(root, s);
	printf("\nYour new tree is: \n");
	printHorizontal(root, 0);

	free(a); // freeing memory allocated to the array.
	freeTree(root); // freeing memory allocated to the tree.
}