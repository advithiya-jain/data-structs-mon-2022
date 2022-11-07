#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

/**
 * ! struct for an AVL tree node
 * 
*/
typedef struct TreeNode {

    int val; // value stored in the node
    struct TreeNode* left; // left child of node (if any)
    struct TreeNode* right; // right child of node (if any)
    struct TreeNode* parent; // parent of node (if any)

    int height; // height difference between left and right child is at most one in an ABL tree
    // height of a node is 1 + the height of the taller child
    // height always needs to be changed during insertion and deletion, dependent on the child(ren).

}tNode;

