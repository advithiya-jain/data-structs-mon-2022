#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/**
 * ! struct for the Red-Black Tree node
 * * enclosed in a typedef for easier referencing
 */
typedef struct node
{
	int key;			 // key of the node
	int color;			 // colour of the node. 1 for red and 0 for black
	long int value;		 // value the key is mapped to
	struct node *left;	 // left child of the node
	struct node *right;	 // right child of the node
	struct node *parent; // parent of the node
} Node;

/**
 * ! Defining all the functions to be used for the Red-Black Tree
 */
Node *createNode(int key, long int value);			   // creates a new node
Node *bst_insert(Node* root, Node* node); // inserts a new node into the tree using normal BST insertion
void insertFix(Node** root, Node *node);			   // fixes the tree after insertion
void insert(Node** root, int key, long int value);	   // inserts a new node into the tree and fixes the tree
													   // ( Wrapper that uses the above two functions)
void rotateLeft(Node** root, Node *node);			   // rotates the tree to the left
void rotateRight(Node** root, Node *node);			   // rotates the tree to the right
Node* search(Node* root, int key);					   // searches for a node in the tree
bool update(Node* root, int key, long int value);	   // updates the value of a node in the tree

/**
 * ! Helper function to create a new node
*/
Node* createNode(int key, long int value) {
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->key = key;
	temp->value = value;
	temp->color = 1;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	return temp;
}

/**
 * ! Function to insert a new node into the tree using normal BST insertion
 * @param root is the root of the tree
 * @param key is the key of the node to be inserted
 * @param value is the value the key is mapped to
 * @return the root of the tree
 */
Node *bst_insert(Node *root, Node* node) {
	if (!root) return node;
	
	if (node->key < root->key) {
		root->left = bst_insert(root->left, node);
		root->left->parent = root;
	}

	else if (node->key > root->key) {
		root->right = bst_insert(root->right, node);
		root->right->parent = root;
	}

	return root;
}

/**
 * ! Function to rotate a given node to the left
 */
void rotateLeft(Node** root, Node *node) {
	Node *right = node->right;
	node->right = right->left;

	if (node->right) node->right->parent = node;

	right->parent = node->parent;

	if (!node->parent) *root = right;

	else if (node == node->parent->left) node->parent->left = right;

	else node->parent->right = right;

	right->left = node;
	node->parent = right;

}

/**
 * ! Function to rotate a given node to the right
 */
void rotateRight(Node** root, Node *node) {
	Node *left = node->left;
	node->left = left->right;

	if (node->left) node->left->parent = node;

	left->parent = node->parent;

	if (!node->parent) *root = left;

	else if (node == node->parent->left) node->parent->left = left;

	else node->parent->right = left;

	left->right = node;
	node->parent = left;
}

/**
 * ! Function to fix the tree after insertion
 */
void insertFix(Node **root, Node *node) {
	Node *parent = NULL;
	Node *grandparent = NULL;

	while ((node != (*root)) && (node->color != 0) && (node->parent->color == 1)) {

		parent = node->parent;
		grandparent = node->parent->parent;

		// Situation where the parent node is the left child of the grandparent node
		if (parent == grandparent->left) {
			// We set the uncle node to the right child of the grandparent node
			// as the uncle is the "sibling" of the parent node
			Node *uncle = grandparent->right;

			// Situation where the uncle node is red
			if (uncle && uncle->color == 1) {
				// We set the parent and uncle nodes to black and the grandparent node to red
				grandparent->color = 1;
				parent->color = 0;
				uncle->color = 0;
				// finally we set the node to the grandparent node for the loop to repeat the process from the that node
				node = grandparent;
			}

			// Situation where the uncle node is black
			else {
				// If the node is the right child of the parent node when the uncle is black, 
				// we have to rotate the tree to the left at the parent node to maintain the tree balance.
				if (node == parent->right) {
					rotateLeft(root, parent);
					// After rotation we set the node to the parent node
					node = parent;
					// and the parent node to the grandparent node 
					parent = node->parent;
				}

				// Situation where the node is the left child of the parent node when the uncle is black, 
				// we rotate the tree to the right at the grandparent node as the uncle is black
				rotateRight(root, grandparent);

				// then swap the colors of the parent and grandparent nodes after rotation
				int temp = parent->color;
				parent->color = grandparent->color;
				grandparent->color = temp;
				node = parent;
			}
		}

		// Situation where the parent node is the right child of the grandparent node
		else {
			// here we set the uncle node to the left child of the grandparent node, as per the "sibling" rule
			Node *uncle = grandparent->left;

			// Situation where the uncle node is red
			if ((uncle) && (uncle->color == 1)) {
				// We set the parent and uncle nodes to black and the grandparent node to red
				grandparent->color = 1;
				parent->color = 0;
				uncle->color = 0;
				// finally we set the node to the grandparent node for the loop to repeat the process from the that node
				node = grandparent;
			}

			// Situation where the uncle node is black
			else {
				// same as the previous situation where the uncle node is black, except we rotate the tree to the right
				if (node == parent->left) {
					rotateRight(root, parent);
					node = parent;
					parent = node->parent;
				}

				// If the node is the right child of the parent node, 
				// then we rotate the tree to the left at the grandparent node
				rotateLeft(root, grandparent);

				// then swap the colors of the parent and grandparent nodes after rotation
				int temp = parent->color;
				parent->color = grandparent->color;
				grandparent->color = temp;
				node = parent;
			}
		}
	}

	// We set the root node to black to maintain the rules of a red-black tree (root is always black)
	(*root)->color = 0;

	// finally we return the root node
}

/**
 * ! Function to insert a new node into the tree
 */
void insert(Node **root, int key, long int value) {
	Node* temp = createNode(key, value);
	(*root) = bst_insert((*root), temp);
	insertFix(root, temp);
}

/**
 * ! Function to search for a given key in the tree
*/
Node* search(Node* root, int key) {
	
	if(root){
		if (key < root->key) 	  return search(root->left, key);
		else if (key > root->key) return search(root->right, key);
		else 					  return root;
	}
	else return NULL;
}

/**
 * ! Function to update the value of a given key in the tree
*/
bool update(Node* root, int key, long int value) {
	Node* node = search(root, key);
	if (node) {
		node->value = value;
		return true;
	}
	else return false;
}

void inorder(struct node* node) {
	if (!node) return;
	inorder(node->left);
	printf("%d - %ld - %d\n", node->key, node->value, node->color);
	inorder(node->right);
}

void preorder(struct node* node) {
	if (!node) return;
	printf("%d - %ld - %d\n", node->key, node->value, node->color);
	preorder(node->left);
	preorder(node->right);
}

int main(int argc, char** argv) {
	Node* root = NULL;
	int key;
	long int value;
	srand(time(NULL));
	int a[] = {7, 3, 18, 10, 22, 8, 11, 26};

	for(int i = 0; i < 8; i++) {
		key = a[i];
		value = rand() % 100;
		printf("\n Inserting %d - %ld\n", key, value);
		insert(&root, key, value);
	}
	printf("\n");
	preorder(root);
	printf("\n");
	Node* temp = search(root, 10);
	printf("\n");
	if(temp) printf("%d - %ld - %d\n", temp->key, temp->value, temp->color);
	else printf("Not found\n");
	printf("\n");
	if (update(root, 10, 100)) printf("Updated value of 10 to 100\n");
	else printf("Not found\n");
	printf("\n");
	temp = search(root, 10);
	if(temp) printf("%d - %ld - %d\n", temp->key, temp->value, temp->color);
	else printf("Not found\n");

}