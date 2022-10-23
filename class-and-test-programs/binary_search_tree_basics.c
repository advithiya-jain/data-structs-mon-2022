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
node* createTreeNode(int val) {
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

	if(root==NULL) return createTreeNode(val);

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

/**
 * ! Function to generate a binary search tree from a given array 'a' of size 'n'
*/
node* generateBSTFromArray(node* root, int* a, int n) {

	root = insertBST(root, a[0]); // Inserting the first element of the array as the root

	// generating the tree by inserting the i'th element of the array
	// except for the first element as that has already been inserted
	for(int i = 1; i < n; i++){
		insertBST(root, a[i]);
	}
	// Finally return the generated tree.
	return root;
}

// ! Function to free memory allocated to a BST.
void freeTree(node* root){
	free(root);
}

/************************************************** END FOR BSTs ****************************************************/

int main(int argc, char** argv){
	int a[] = {4, 2, 1, 3, 8, 6, 13}; // Array to be used to generate BST
	int n = 7;
	int se;
	node* root = NULL; // Initialising an empty tree

	// Generate tree from array
	//root = generateBSTSortedOld(root, a, n);
	root = generateBSTFromArray(root, a, n);

	printf("Enter an element to be searched in the array: ");
	scanf("%d", &se);
	node* test; // Initialising a test node to be used to check if the BST contains the search element.
	if(test = searchBST(root, se)) printf("\nCongratulations! The element %d exists in the array! :D\n", se);
	else						  printf("\nBummer. The element %d does not exist in the array :C\n", se);

	// Print the generated tree 
	printf("\nYour generated tree from the array is: \n");
	printHorizontal(root, 0); // giving an initial distance of 0 as the first element must print on the left

	// Print tree inorder
	printf("\n Your tree using inorder traversal is: ");
	printInorder(root);
	printf(":D\n");

	freeTree(root); // freeing memory allocated to the tree.
}