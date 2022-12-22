#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "rbtree.h"

/**
 * ! Helper function to create a new node
 * @param key is the key of the node
 * @param value is the value the key is mapped to
*/
Node* createNode(int key, int value) {
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
Node* bst_insert(Node *root, Node* node) {

	// performing normal BST insertion
	// code used and slightly modified from https://github.com/advithiya-jain/data-structs-mon-2022/blob/6b387289717897f7fc7e924de15820fbf6a98a8f/class-and-test-programs/binary_search_tree_basics.c 
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
 * @param root is the root of the tree
 * @param node is the node to be rotated
 * @return void
 */
void rotateLeft(Node** root, Node *node) {
	
	Node *rightChild = node->right; // set the right child of the passed node to the rightChild variable
	node->right = rightChild->left; // set the left child of the rightChild to the right child of the passed node
	// if the right child of the node is not null, set the parent of the right child of the node to the passwd node
	if (node->right) node->right->parent = node;
	// we then set the parent of the rightChild to the parent of the passed node
	rightChild->parent = node->parent;
	// if the parent of the passed node is null, we set the root to the rightChild
	if (!node->parent) *root = rightChild;
	// else, if the passed node is the left child of the parent, 
	// we set the left child of the parent to the rightChild
	else if (node == node->parent->left) node->parent->left = rightChild;
	// else, we set the right child of the parent to the rightChild
	else node->parent->right = rightChild;

	// Finally, we set the left child of the rightChild to the passed node
	rightChild->left = node;
	// and set the parent of the passed node to the rightChild, successfully rotating the node to the left
	node->parent = rightChild;


}

/**
 * ! Function to rotate a given node to the right
 * @param root is the root of the tree
 * @param node is the node to be rotated
 * @return void
 */
void rotateRight(Node** root, Node *node) {

	Node *leftChild = node->left; // set the left child of the passed node to the leftChild variable
	node->left = leftChild->right; // set the right child of the leftChild to the left child of the passed node
	// if the left child of the node is not null, set the parent of the left child of the node to the passwd node
	if (node->left) node->left->parent = node;
	// we then set the parent of the leftChild to the parent of the passed node
	leftChild->parent = node->parent;
	// if the parent of the passed node is null, we set the root to the leftChild
	if (!node->parent) *root = leftChild;
	// else, if the passed node is the left child of the parent,
	// we set the left child of the parent to the leftChild
	else if (node == node->parent->left) node->parent->left = leftChild;
	// else, we set the right child of the parent to the leftChild
	else node->parent->right = leftChild;

	// Finally, we set the right child of the leftChild to the passed node
	leftChild->right = node;
	// and set the parent of the passed node to the leftChild, successfully rotating the node to the right
	node->parent = leftChild;
}

/**
 * ! Function to fix the tree after insertion
 * @param root is an address to the root pointer of the tree
 * @param node is the node that was inserted
 * @return void
 */
void insertFix(Node **root, Node *node) {
	Node *parent = NULL;
	Node *grandparent = NULL;

	// loop that runs until the node is the root or the node is black or the parent of the node is black
	while ((node != (*root)) && (node->color != 0) && (node->parent->color == 1)) {

		// initialize the parent and grandparent nodes
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
}

/**
 * ! Function to insert a new node into the tree
 * @param root is an address to the root pointer of the tree
 * @param key is the key of the new node
 * @param value is the value of the new node
 * @return void
 */
void insert(Node **root, int key, int value) {
	// This uses the bst_insert function to insert the node into the tree
	// and then calls the insertFix function to fix the tree

	Node* temp = createNode(key, value); // since we need the new node that we are inserting for the fix,
										 // we create it within this function itself
	// insert the node into the tree
	(*root) = bst_insert((*root), temp);
	// and finally fix the tree
	insertFix(root, temp);
}

/**
 * ! Function to search for a given key in the tree
 * @param root is the root node of the tree
 * @param key is the key to search for
 * @return the node with the given key if found, NULL otherwise
*/
Node* search(Node** root, int key) {
	
	// performing normal BST search
	// code used from: https://github.com/advithiya-jain/data-structs-mon-2022/blob/6b387289717897f7fc7e924de15820fbf6a98a8f/class-and-test-programs/binary_search_tree_basics.c

	if(*root){
		if (key < (*root)->key) 	 return search(&((*root)->left), key);
		else if (key > (*root)->key) return search(&((*root)->right), key);
		else 					  	 return *root;
	}
	else return NULL;
}

/**
 * ! Function to update the value of a given key in the tree
 * @param root is the root node of the tree
 * @param key is the key to search for
 * @param value is the new value to update
 * @return true if the key was found and updated, false otherwise
*/
bool update(Node** root, int key, int value) {

	// This function takes the returned node from the search function and then updates the value.
	// If the node is not null, we update the value and return true.
	// If the node is null, we return false, as this means the key was not found in the tree.

	Node* node = search(root, key);
	if (node) {
		node->value = value;
		return true;
	}
	else return false;
}

void preorder(Node* root) {
	if(root->left) preorder(root->left);       
	if(root) printf("%d - %d - %d", root->key, root->value, root->color);
	if(root->right) preorder(root->right);
}

/**
 * ! Function to free the memory allocated to a tree
 * @param root is the address to the root pointer of the tree
 * @return void
*/
void freeTree(Node** root) {
	if (!(*root)) return;

	freeTree(&((*root)->left));
	freeTree(&((*root)->right));
	free((*root));
}