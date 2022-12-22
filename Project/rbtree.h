#ifndef RBTREE_H
#define RBTREE_H

/**
 * ! struct for the Red-Black Tree node
 * * enclosed in a typedef for easier referencing
 */
typedef struct node
{
	int key;			 // key of the node
	int color;			 // colour of the node. 1 for red and 0 for black
	int value;		 // value the key is mapped to
	struct node *left;	 // left child of the node
	struct node *right;	 // right child of the node
	struct node *parent; // parent of the node
} Node;

/**
 * ! Defining all the functions to be used for the Red-Black Tree
 */
Node* createNode(int key, int value);			   // creates a new node
Node* bst_insert(Node* root, Node* node);              // inserts a new node into the tree using normal BST insertion
void insertFix(Node** root, Node *node);			   // fixes the tree after insertion
void insert(Node** root, int key, int value);	   // inserts a new node into the tree and fixes the tree
													   // ( Wrapper that uses the above two functions)
void rotateLeft(Node** root, Node *node);			   // rotates the tree to the left
void rotateRight(Node** root, Node *node);			   // rotates the tree to the right
Node* search(Node** root, int key);					   // searches for a node in the tree
bool update(Node** root, int key, int value);	   // updates the value of a node in the tree
void freeTree(Node** root);							   // frees a tree
void preorder(struct node* node);                      // prints the tree in preorder traversal

#endif