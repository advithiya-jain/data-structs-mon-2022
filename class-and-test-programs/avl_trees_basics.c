#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

/**
 * ! struct for an AVL tree node
*/
typedef struct TreeNode {

    int val; // value stored in the node
    struct TreeNode* left; // left child of node (if any)
    struct TreeNode* right; // right child of node (if any)

    int height; // height difference between left and right child is at most one in an ABL tree
    // height of a node is 1 + the height of the taller child
    // height always needs to be changed during insertion and deletion, dependent on the child(ren).

}tNode;

/**
 * ! Helper Function to find the max of two integers (to find the greater of two heights)
 * @param x - the first integer value
 * @param y - the second integer value
*/
int max(int x, int y) { return (x > y)? x : y; }

/**
 * ! Helper Function to find the height of a tree/subtree
 * @param root - the root of the tree/subtree
*/
int getHeight(tNode* root) {
    return (root == NULL)? 0 : root->height;
}

/**
 * ! Function to create a new node in an AVL tree
 * @param val is value to be stored in the node
*/
tNode* createNode(int val){
    tNode* node = (tNode*)malloc(sizeof(tNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    node->height = 1;

    return (node);
}

/**
 * ! Function to get the height_diffof a tree/subtree
 * @param root - is the root of the tree/subtree
*/
int treeBalance(tNode* root) {
    return (root == NULL)? 0 : getHeight(root->left) - getHeight(root->right);
}

/**
 * ! Function to rotate a node in an AVL tree to the left
 * @param root type tNode* - the parent of the node that is to be rotated
*/
tNode* rotateLeft(tNode* root) {
    tNode* cnode = root->right; // the right child node of the root to be rotated, the root of the subtree
    tNode* temp = cnode->left; // temp value to store the left child of the right child of the root to be rotated

    // if the root of the sub-tree to be rotated is NULL, it does not exist so we just return NULL.
    //if (cnode == NULL) return NULL;

    // the left child of the sub-tree root is now the parent node
    cnode->left = root;
    // the right child of the original tree root is now the left child of the new root(cnode)
    root->right = temp;

    // now we have to update the heights of the nodes,
    // the height of a parent node is now the greater (heights) of its children + 1
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    cnode->height = max(getHeight(cnode->left), getHeight(cnode->right)) + 1;

    return cnode; // we return the new root of the tree/subtree (the right child of the original root).
}

/**
 * ! Function to rotate a node in an AVL tree to the right
 * @param root type tNode* - the parent of the node that is to be rotated
*/
tNode* rotateRight(tNode* root) {
    tNode* cnode = root->left; // the left child node of the root to be rotated, the root of the subtree
    tNode* temp = cnode->right; // temp value to store the right child of the left child of the root to be rotated

    // if the root of the sub-tree to be rotated is NULL, it does not exist so we just return NULL.
    //if (cnode == NULL) return NULL;

    // the left child of the sub-tree root is now the parent node
    cnode->right = root;
    // the left child of the original tree root is now the right child of the new root(cnode)
    root->left = temp;

    // now we have to update the heights of the nodes,
    // the height of a parent node is now the greater (heights) of its children + 1
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    cnode->height = max(getHeight(cnode->left), getHeight(cnode->right)) + 1;

    return cnode; // we return the new root of the tree/subtree (the left child of the original root).
}

/**
 * ! Function to rotate the child of a node in an AVL tree to the left and then rotate the node to the right
 * @param root is the root of the tree/subtree to be balanced
*/
tNode* rotateLeftRight(tNode* root) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
}

/**
 * ! Function to rotate the child of a node in an AVL tree to the right and then rotate the node to the left
 * @param root is the root of the tree/subtree to be balanced
*/
tNode* rotateRightLeft(tNode* root) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
}

/**
 * ! Function to insert a node into an AVL tree
 * @param root is the root of the tree/subtree to be inserted into
 * @param val is the value to be inserted into the tree
*/
tNode* insertAVL(tNode* root, int value)
{
    /**
     * ! First we normally insert a value as we would in a BST
    */
    // if the root is NULL, we create a new node and return it
    if (root == NULL) return(createNode(value));
    // if the value is less than the root, we insert it in the left subtree
    if (value < root->val) root->left  = insertAVL(root->left, value);
    // if the value is greater than the root, we insert it in the right subtree
    else if (value > root->val) root->right = insertAVL(root->right, value);
    // if the value is equal to the root, we do not insert it
    else return root;

    /**
     * ! Now we do the checks for the AVL tree condition and balance the tree if necessary
    */
    
    // If the value entered was not equal to the value at the root, i.e nothing was inserted, 
    // we have to update the height of the root node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Now we check for height differences to see if the tree is balanced and rotate if necessary
    int height_diff = treeBalance(root);

    // If the height difference is less than -1 and the value is greater than the right child's value, 
    // then this is an indicator of a double right heavy tree/subtree.
    // So we have to rotate the tree to the left to balance it.
    if (height_diff< -1 && value > root->right->val) return rotateLeft(root);

    // If the height difference is greater than 1 and the value is greater than the right child's value,
    // then this is an indicator of a double left heavy tree/subtree.
    // So we have to rotate the tree to the right to balance it.
    if (height_diff > 1 && value < root->left->val) return rotateRight(root);
    
    // Now, if the height difference is greater than 1 and the value is less than the left child's value,
    // then this is an indicator of a left then right heavy tree/subtree.
    // So we have to rotate the left child to the right and the root to the left to balance it.
    if (height_diff > 1 && value > root->left->val) return rotateLeftRight(root);

    // If the height difference is less than -1 and the value is greater than the right child's value,
    // then this is an indicator of a right then left heavy tree/subtree.
    // So we have to rotate the right child to the left and the root to the right to balance it.
    if (height_diff< -1 && value < root->right->val) return rotateRightLeft(root);

    // finally, we return the root of the tree/subtree after any balances have been made
    return root;

}

/**
 * ! Function to print a binary tree 'horizontally' where the root starts from the left
 * @param dist is used to create distance between the elemetns being printed using spaces
*/
void printHorizontal(tNode* root, int dist)
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

int main(int argc, char** aargv) {
    tNode* root = NULL;
    int n, val, flag = 0;

    printf("Welcome to this AVL tree editing program!\nJust enter length of the tree then the values you want to insert into the tree and the program will do the rest :D\n\n");

    do {
        printf("Enter the number of nodes you want in your AVL tree: ");
        scanf("%d", &n);

        if (n < 1) {
            printf("Invalid number of nodes! >:C");
            flag = 1;
        }
        else {
            flag = 0;
            for(int i = 0; i < n; i++) {
                printf("Enter value %d: ", i+1);
                scanf("%d", &val);
                root = insertAVL(root, val);
            }
        }
    } while (flag == 1);

    printf("\n\nThe AVL tree you created is:\n");

    printHorizontal(root, 0);
    
    return 0;
}