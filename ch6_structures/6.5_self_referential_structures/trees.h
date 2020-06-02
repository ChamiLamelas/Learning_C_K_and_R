/*
    Contains declarations of a BST operations for generic data (inc. comparison, copying, allocation, printing).
    This is an expansion of the limited word counting BST described in section 6.5 of the text.

    For runtime calculations of the declarad operations, they are done with respect to the number of nodes (n)
    in the BST. Operations regarding node data such as copying, size, comparison, and string conversion are
    considered to be O(1).

    Author: Chami Lamelas
    6/2/2020
*/

#ifndef TREES_H
#define TREES_H

#include <stddef.h> // needed for size_t

/*
    Structure of a binary search tree (BST) node.

    Fields: 
        left (struct bstNode *) : pointer to left child (which is a bstNode)
        right (struct bstNode *) : pointer to right child (which is a bstNode)
        key (void *) : pointer to the data key of any type
*/
struct bstNode
{
    struct bstNode *left;
    struct bstNode *right;
    void *key;
};

/*
    Searches the BST rooted at a provided node for a provided key. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of the BST to search
        key (const void *) : pointer to the search key (not modified)
        comp (int (*) (const void *, const void *)) : pointer to the comparison function to be used in the
            search / construction of the BST. 
    Output: 
        Assuming that root points to a valid BST and that key is compatible with the comparison function comp: 

            1. If the key is in the BST rooted at root, then a pointer to the bstNode containing key is returned. 
            2. If the key is not in the BST rooted at root, then a pointer to the last bstNode in the search for
                key is returned. 

    Usage: 
        Output may be NULL in case #2. 
        To see if the BST contains key, one can check if returned pointer references node containing the searched
            key or not. 

    Runtime: O(n) unbalanced, O(log(n)) balanced    n = # nodes in BST 
*/
struct bstNode *bstSearch(struct bstNode *root, const void *key, int (*comp)(const void *, const void *));

/*
    Retrieves the minimum value in a BST. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of a BST 

    Output: 
        A pointer to the bstNode with the minimum value in the BST rooted at root. 
        This will be NULL if root is NULL. 

    Runtime: O(n) unbalanced, O(log(n)) balanced    n = # nodes in BST 
*/
struct bstNode *bstMinimum(struct bstNode *root);

/*
    Retrieves the maximum value in a BST. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of a BST 

    Output: 
        A pointer to the bstNode with the maximum value in the BST rooted at root. 
        This will be NULL if root is NULL. 

    Runtime: O(n) unbalanced, O(log(n)) balanced    n = # nodes in BST 
*/
struct bstNode *bstMaximum(struct bstNode *root);

/*
    Retrieves the largest value smaller than a provided value in a given BST. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of the BST to search
        key (const void *) : pointer to the key for which the predecessor is being searched (not modified)
        comp (int (*) (const void *, const void *)) : pointer to the comparison function to be used in the
            search / construction of the BST. 

    Output: 
        Assuming that root points to a valid BST and that key is compatible with the comparison function comp: 

            1. If the key has a predecessor in the BST, then a pointer to the bstNode containing the predecessor 
                is returned. Even if the key is not in the BST. 
            2. If the key has no predecessor in the BST, then NULL is returned. This is true even if the key is in
                the BST. 

    Runtime: O(n) unbalanced, O(log(n)) balanced    n = # nodes in BST 
*/
struct bstNode *bstPredecessor(struct bstNode *root, const void *key, int (*comp)(const void *, const void *));

/*
    Retrieves the smallest value larger than a provided value in a given BST. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of the BST to search
        key (const void *) : pointer to the key for which the successor is being searched (not modified)
        comp (int (*) (const void *, const void *)) : pointer to the comparison function to be used in the
            search / construction of the BST. 

    Output: 
        Assuming that root points to a valid BST and that key is compatible with the comparison function comp: 

            1. If the key has a successor in the BST, then a pointer to the bstNode containing the successor 
                is returned. Even if the key is not in the BST. 
            2. If the key has no successor in the BST, then NULL is returned. This is true even if the key is in
                the BST. 

    Runtime: O(n) unbalanced, O(log(n)) balanced    n = # nodes in BST 
*/
struct bstNode *bstSuccessor(struct bstNode *root, const void *key, int (*comp)(const void *, const void *));

/*
    Inserts a copy of the provided key into a BST. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of the BST to insert into 
        key (const void *) : pointer to the key to be inserted. A copy of the referenced data will be inserted into the BST. 
        copy (void (*) (void *, const void *)) : pointer to a function that copies a value referenced by a const source 
            pointer (2nd param) to be referenced by a destination pointer (1st param)
        size (size_t (*) (const void *)) : pointer to a function that retrieves the allocation size (in bytes) of the 
            data referenced by a given const void pointer. 
        comp (int (*) (const void *, const void *)): pointer to the comparison function to be used in the
            search / construction of the BST. 

    Output: 
        Assuming that: 
            1.  root points to a valid BST. 
            2.  key is compatible with the comparison function comp
            3.  size correctly determines the allocation size in bytes of the data referenced by key 
            4.  copy makes a deep copy of the data referenced by key

        If the key does not occur in the BST, then a pointer to the root of the BST with the inserted data is returned.
        Otherwise, a pointer to the original root is returned. 

    Example Usage: 
        Suppose you are operating on a BST storing strings with an existing root 'root'. 
        A key (as with the other operations) must be cast to (const void *) 
            -   from (const char *) in this case. 
        strcpy may be used for copying, but it must be cast to (void (*) (void *, const void *)) 
            -   from (void (*) (char *, const char *)) in this case.
        A function that utilizes strlen + 1 with the appropriate function type (size_t (*) (const void *)) may
            be used. The addition of 1 is needed for the terminating null character. 
        strcmp may be used for comparison, but it must be cast to (int (*) (const void *, const void *)) as 
            with the other operations. 
            -   from (int (*) (const char *, const char *)) in this case.

    Runtime: O(n) unbalanced, O(log(n)) balanced    n = # nodes in BST 

        NOTE: memory allocation is assumed to be independent
*/
struct bstNode *bstInsert(struct bstNode *root, const void *key, void (*copy)(void *, const void *), size_t (*size)(const void *), int (*comp)(const void *, const void *));

/*
    Deletes the node from a BST containing a provided key. 

    Parameters: 
        root (struct bstNode *) : pointer to the root of the BST to delete from
        key (const void *) : pointer to the key for which the successor is being searched (not modified)
        comp (int (*) (const void *, const void *)) : pointer to the comparison function to be used in the
            search / construction of the BST. 

    Output: 
        Assuming that root points to a valid BST and that key is compatible with the comparison function comp: 

            1.  If the provided key exists in the BST, then the root of the tree with the node containing key
                removed.
            2.  If the provided key does not exist in the BST, then the original root is returned. 

    Runtime: O(n) unbalanced, O(log(n)) balanced    n = # nodes in BST
*/
struct bstNode *bstDelete(struct bstNode *root, const void *key, int (*comp)(const void *, const void *));

/*
    Frees all the storage allocated to the nodes of a provided BST.

    Parameters: 
        root (struct bstNode *) : a pointer to the root of the BST to free 

    Output: 
        All nodes in the tree have their left, right, and key pointers set to NULL and are freed. 
        This means that all nodes in the tree besides the root are set to NULL.
        The root pointer points to a struct where the left, right, and key are NULL. 
        It is recommended that the root is set to NULL after a function is used in the calling function to
            prevent undefined behavior.

    Runtime: O(n)   n - # nodes in BST
*/
void bstFree(struct bstNode *root);

/*
    Prints the keys in the BST in the order in which they are stored. This is done using the comparison function
    used in search, insertion, and deletion. 

    Parameters: 
        root (struct bstNode *) : a pointer to the root of the BST to print
        toString (const char * (*) (const void *)) : pointer to a function that converts the data referenced by
            a generic pointer into a character string. 

    Output: 
        Assuming the supplied toString function applies to the stored data, an inorder of traversal of the tree 
            is printed.

    Runtime: O(n)   n - # nodes in BST
*/
void bstPrint(struct bstNode *root, const char *(*toString)(const void *));

#endif