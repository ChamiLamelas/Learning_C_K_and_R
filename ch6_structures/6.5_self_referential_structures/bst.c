/*  
    Contains implementation of a BST operations for generic data (inc. comparison, copying, allocation, printing).
    This is an expansion of the limited word counting BST described in section 6.5 of the text.

    File format :
        1.  Necessary headers
        2.  Private (static) helper function declarations 
        3.  Public header function definitions 
        4.  Private (static) helper function definitions 

    For runtime calculations of the declarad operations, they are done with respect to the number of nodes (n)
    in the BST. Operations regarding node data such as copying, size, comparison, and string conversion are
    considered to be O(1).

    Author: Chami Lamelas
    6/2/2020
*/

#include "trees.h"  // needed for BST operation declarations, BST node structure
#include <stddef.h> // needed for size_t
#include <stdlib.h> // needed for malloc(), free()
#include <stdio.h>  // needed for printf()

// ***************************** PRIVATE HELPER FUNCTIONS DEFINITIONS ***************************************

/*
    Creates a new node containing a copy of the data referenced by a provided key. 

    Parameters: 
        key (const void *) : pointer to key to add 
        copy (void (*) (void *, const void *)) : pointer to a function that copies a value referenced by a const source 
            pointer (2nd param) to be referenced by a destination pointer (1st param)
        size (size_t (*) (const void *)) : pointer to a function that retrieves the allocation size (in bytes) of the 
            data referenced by a given const void pointer. 

    Output: 
        Assuming that copy and size have been implemented properly such that a new bstNode can be created 
        dynamically with the appropriate size and data, returns a pointer to a BST node containing a deep copy
        of key. 

        Otherwise, behavior is undefined. 

    For example usage, see documentation of bstInsert() in trees.h 

    Runtime: O(1) 
*/
static struct bstNode *createNewNode(const void *key, void (*copy)(void *, const void *), size_t (*size)(const void *));

/*
    Deletes a node from a BST that has 2 children. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of the BST to delete from 
        curr (struct bstNode *) : pointer to node to be deleted 
        prev (struct bstNode *) : pointer to curr's parent or NULL if curr is the root
        comp (int (*) (const void *, const void *)) : pointer to the comparison function to be used in the
            search / construction of the BST. 

    Output: 
        A pointer to the BST with curr removed from the tree is returned. For this particular implementation
        of deletion, the deleted node is swapped with its successor. An alternative implementation could 
        choose the predecessor. 

    Runtime: O(n) unbalanced, O(log(n)) balanced    n = # nodes in BST 
*/
static struct bstNode *deleteNodeWith2Children(struct bstNode *root, struct bstNode *curr, struct bstNode *prev, int (*comp)(const void *, const void *));

/*
    Deletes a node from a BST that has only 1 child. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of the BST to delete from 
        curr (struct bstNode *) : pointer to node to be deleted 
        prev (struct bstNode *) : pointer to curr's parent or NULL if curr is the root
        comp (int (*) (const void *, const void *)) : pointer to the comparison function to be used in the
            search / construction of the BST. 

    Output: 
        A pointer to the BST with curr removed from the tree is returned.

    Runtime: O(1)
*/
static struct bstNode *deleteNodeWith1Child(struct bstNode *root, struct bstNode *curr, struct bstNode *prev, int (*comp)(const void *, const void *));

/*
    Deletes a node from a BST that has only no children. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of the BST to delete from 
        curr (struct bstNode *) : pointer to node to be deleted 
        prev (struct bstNode *) : pointer to curr's parent or NULL if curr is the root
        comp (int (*) (const void *, const void *)) : pointer to the comparison function to be used in the
            search / construction of the BST. 

    Output: 
        A pointer to the BST with curr removed from the tree is returned.

    Runtime: O(1)
*/
static struct bstNode *deleteLeaf(struct bstNode *root, struct bstNode *curr, struct bstNode *prev, int (*comp)(const void *, const void *));

/*
    Frees the storage held by a provided bstNode and marks it as freed. 

    Parameters: 
        node (struct bstNode *) : pointer to bstNode to be freed 

    Output: 
        Frees the storage previously allocated to the provided bstNode pointer. The pointer's referenced data is
        marked as freed by having them set to NULL. 

        NOTES: 
            1. This does not mean the provided pointer is now NULL. This must be done (and recommended) in the 
            calling function. 
            2.  Marking the children of the referenced bstNode as NULL can lead to dangling pointers if the referenced
            data is not freed previously. 
            3.  However, the key data is freed which is allocated dynamically in bstInsert().

    Runtime: O(1)   - memory de-allocation is independent
*/
static void freeBstNode(struct bstNode *node);

// ***************************** HEADER FUNCTIONS DEFINITIONS *******************************************

struct bstNode *bstSearch(struct bstNode *root, const void *key, int (*comp)(const void *, const void *))
{
    // tracks last previously visited node
    struct bstNode *prev = NULL;
    while (root != NULL)
    {
        prev = root;
        // key less than node being visited, compare it with left child
        if ((*comp)(key, root->key) < 0)
        {
            root = root->left;
        }
        // key greater than node being visited, compare it with right child
        else if ((*comp)(key, root->key) > 0)
        {
            root = root->right;
        }
        // key equals visited node's key, return visited node
        else
        {
            return root;
        }
    }

    // key not found, return last previously visited node instead
    return prev;
}

struct bstNode *bstMinimum(struct bstNode *root)
{
    // BST empty, return that there's no min
    if (root == NULL)
    {
        return NULL;
    }
    // keep going left until node with no left child hit
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

struct bstNode *bstMaximum(struct bstNode *root)
{
    // BST empty, return that there's no max
    if (root == NULL)
    {
        return NULL;
    }
    // keep going right until node with no right child hit
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

struct bstNode *bstPredecessor(struct bstNode *root, const void *key, int (*comp)(const void *, const void *))
{
    if (root == NULL)
    {
        return NULL;
    }

    // lowest smaller parent
    struct bstNode *lsp = NULL;
    // tracks last previously visited node
    struct bstNode *prev = NULL;

    // loop until key found or determined not in tree
    while (root != NULL && (*comp)(root->key, key) != 0)
    {
        prev = root;
        // if visited node less than key, track it as a smaller parent and go right
        if ((*comp)(root->key, key) < 0)
        {
            lsp = root;
            root = root->right;
        }
        // visited node greater than key, go left
        else
        {
            root = root->left;
        }
    }

    // if key not found, then find predecessor of last previously visited
    if (root == NULL)
    {
        root = prev;
    }

    // if key exists in tree, then it may have a left subtree. its predecessor will be the max of that subtree
    // all elements in its left subtree will be between its lowest smaller parent and it
    if (root->left != NULL)
    {
        return bstMaximum(root->left);
    }
    // otherwise, if key exists or not, return lowest smallest parent
    else
    {
        return lsp;
    }
}

struct bstNode *bstSuccessor(struct bstNode *root, const void *key, int (*comp)(const void *, const void *))
{
    if (root == NULL)
    {
        return NULL;
    }

    // last previously visited node
    struct bstNode *prev = NULL;
    // lowest greater parent
    struct bstNode *lgp = NULL;

    // loop until key found or determined not in tree
    while (root != NULL && (*comp)(root->key, key) != 0)
    {
        prev = root;
        // if visited node greater than key, track it as greater parent and go left
        if ((*comp)(root->key, key) > 0)
        {
            lgp = root;
            root = root->left;
        }
        // visited less than key, go right
        else
        {
            root = root->right;
        }
    }

    // if key not found, then find successor of last previously visited
    if (root == NULL)
    {
        root = prev;
    }

    // if key exists in tree, then it may have a right subtree. its successor will be the min of that subtree
    // all elements in its right subtree will be between its lowest greater parent and it
    if (root->right != NULL)
    {
        return bstMinimum(root->right);
    }
    // otherwise, if key exists or not, return lowest greatest parent
    else
    {
        return lgp;
    }
}

struct bstNode *bstInsert(struct bstNode *root, const void *key, void (*copy)(void *, const void *), size_t (*size)(const void *), int (*comp)(const void *, const void *))
{
    // search for insertion point into tree
    struct bstNode *res = bstSearch(root, key, comp);

    // if search led to key, return root unchanged
    if (root != NULL && (*comp)(res->key, key) == 0)
    {
        return root;
    }

    // key not in BST, create node with a copy using helper
    struct bstNode *newNode = createNewNode(key, copy, size);

    // if BST empty, return created node
    if (root == NULL)
    {
        return newNode;
    }
    // if key less than insertion point, insert it as left child
    else if ((*comp)(key, res->key) < 0)
    {
        res->left = newNode;
    }
    // else, key greater, insert it as right child
    else
    {
        res->right = newNode;
    }

    // return new root
    return root;
}

struct bstNode *bstDelete(struct bstNode *root, const void *key, int (*comp)(const void *, const void *))
{
    // if tree empty
    if (root == NULL)
    {
        return NULL;
    }

    // similar logic to bstSearch, but both prev and curr needed for deletion, hence it is rewritten
    struct bstNode *prev = NULL;
    struct bstNode *curr = root;
    while (curr != NULL && (*comp)(curr->key, key) != 0)
    {
        prev = curr;
        if ((*comp)(key, curr->key) < 0)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    // key not found, return untouched root
    if (curr == NULL)
    {
        return root;
    }

    // will hold new root
    struct bstNode *out = NULL;

    // key has 2 children, delete using helper
    if (curr->left != NULL && curr->right != NULL)
    {
        out = deleteNodeWith2Children(root, curr, prev, comp);
    }
    // key has 1 child, delete using helper
    else if (curr->left != NULL || curr->right != NULL)
    {
        out = deleteNodeWith1Child(root, curr, prev, comp);
    }
    // key is a leaf, delete using helper
    else
    {
        out = deleteLeaf(root, curr, prev, comp);
    }

    // free the deleted node and return new root
    freeBstNode(curr);
    return out;
}

void bstFree(struct bstNode *root)
{
    // nothing to deallocate in this case
    if (root == NULL)
    {
        return;
    }
    // use postorder traversal to perform memory deallocation, free subtrees first then root
    bstFree(root->left);
    bstFree(root->right);
    freeBstNode(root);
}

void bstPrint(struct bstNode *root, const char *(*toString)(const void *))
{
    // nothing to print in this case
    if (root == NULL)
    {
        return;
    }
    // print left subtree first
    bstPrint(root->left, toString);
    // print this node using toString function
    printf("%s\n", (*toString)(root->key));
    // print right subtree after
    bstPrint(root->right, toString);
}

// ***************************** PRIVATE HELPER FUNCTIONS DECLARATIONS ***************************************

static struct bstNode *createNewNode(const void *key, void (*copy)(void *, const void *), size_t (*size)(const void *))
{
    // allocate space for the struct (note malloc() returns void * hence the cast)
    // sizeof() is used on the type bstNode
    struct bstNode *n = (struct bstNode *)malloc(sizeof(struct bstNode));

    // allocate space for a copy of the key using the size
    n->key = malloc((*size)(key));

    // copy the key into the structure's field
    (*copy)(n->key, key);

    // set children to NULL before returning created node, these are default initialized to garbage
    n->left = NULL;
    n->right = NULL;
    return n;
}

static void freeBstNode(struct bstNode *node)
{
    // mark children as NULL (note this could lead to orphaned data if children were not freed)
    node->left = NULL;
    node->right = NULL;
    // free data referenced by key pointer and mark it NULL as well
    free(node->key);
    node->key = NULL;
    // free storage allocated to pointer parameter
    free((void *)node);
}

static struct bstNode *deleteNodeWith2Children(struct bstNode *root, struct bstNode *curr, struct bstNode *prev, int (*comp)(const void *, const void *))
{
    // track last node visited prior to the successor
    struct bstNode *sPrev = NULL;
    // track the successor, which will be the minimum of the right subtree (as curr is known to have 2 children)
    struct bstNode *successor = curr->right;

    // find successor as minimum
    while (successor->left != NULL)
    {
        sPrev = successor;
        successor = successor->left;
    }

    // successor must be switched with curr, this checks if successor has a parent that needs to be updated
    if (sPrev != NULL)
    {
        // successor may have a right child, it needs to be attached to successor's parent as its left child
        sPrev->left = successor->right;
        // if successor has a parent, then the successor is at least 1 level after curr->right (i.e. curr->
        // right now must be attached as successor's RST).
        successor->right = curr->right;
        // if successor has no parent, then the successor is curr->right, and its right does not need to
        // be updated
    }

    // attach successor's left to curr's left to complete switch (Note: successor's left will be NULL before this)
    successor->left = curr->left;

    // this means root is being deleted, therefore, successor is now the root
    if (prev == NULL)
    {
        return successor;
    }
    else
    {
        // if deleted node is a left child, update its parent's left child to be the successor
        if ((*comp)(curr->key, prev->key) < 0)
        {
            prev->left = successor;
        }
        // if deleted node is a right child, update it's parent's right child to be the successor
        else
        {
            prev->right = successor;
        }

        // return existing root
        return root;
    }
}

static struct bstNode *deleteNodeWith1Child(struct bstNode *root, struct bstNode *curr, struct bstNode *prev, int (*comp)(const void *, const void *))
{
    // determine whether curr has a left or right child
    struct bstNode *child = NULL;
    if (curr->left != NULL)
    {
        child = curr->left;
    }
    else
    {
        child = curr->right;
    }

    // this means root is being deleted, therefore child is the new root
    if (prev == NULL)
    {
        return child;
    }
    else
    {
        // if deleted node is a left child, update its parent's left child to be curr's child
        if ((*comp)(curr->key, prev->key) < 0)
        {
            prev->left = child;
        }
        // if deleted node is a right child, update its parent's right child to be curr's child
        else
        {
            prev->right = child;
        }

        // return existing root
        return root;
    }
}

static struct bstNode *deleteLeaf(struct bstNode *root, struct bstNode *curr, struct bstNode *prev, int (*comp)(const void *, const void *))
{
    // this means root is being deleted, and if root is a leaf, that means this was a 1 node tree that is now empty
    if (prev == NULL)
    {
        return NULL;
    }
    else
    {
        // if deleted node is a left child, update its parent's left child to be NULL
        if ((*comp)(curr->key, prev->key) < 0)
        {
            prev->left = NULL;
        }
        // if deleted node is a right child, update its parent's right child to be NULL
        else
        {
            prev->right = NULL;
        }

        // return existing root
        return root;
    }
}
