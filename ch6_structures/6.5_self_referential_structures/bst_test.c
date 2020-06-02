#include "trees.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>

struct bstNode *root;

const char *toString(const void *key);
size_t stralloc(const void *key);
void insert(const char *key);
void printNode(struct bstNode *node);
void print();
void insertTest();
struct bstNode *search(const char *key);
void searchTest();
void predecessorTest();
void successorTest();
void deleteTest();
struct bstNode *predecessor(const char *key);
struct bstNode *successor(const char *key);
void delete (const char *key);

int main()
{
    insertTest();
    searchTest();
    predecessorTest();
    successorTest();
    deleteTest();
    printf("Tests done.\n");
    return 0;
}

void insertTest()
{
    printf("Insert Test\n");
    insert("k");
    insert("e");
    insert("q");
    insert("b");
    insert("g");
    insert("n");
    insert("s");
    insert("a");
    insert("c");
    insert("f");
    insert("h");
    insert("m");
    insert("o");
    insert("r");
    insert("t");
    print();

    bstFree(root);
    root = NULL;

    insert("a");
    insert("b");
    insert("c");
    insert("d");
    insert("e");
    insert("f");
    print();

    bstFree(root);
    root = NULL;

    insert("f");
    insert("e");
    insert("d");
    insert("c");
    insert("b");
    insert("a");
    print();

    bstFree(root);
    root = NULL;
}

void searchTest()
{
    printf("Search test\n");
    printNode(search("a")); // NULL
    insert("k");
    printNode(search("a")); // k
    printNode(search("z")); // k
    printNode(search("k")); // k
    insert("e");
    insert("q");
    printNode(search("a")); // e
    printNode(search("g")); // e
    printNode(search("e")); // e
    printNode(search("p")); // q
    printNode(search("z")); // q
    printNode(search("q")); // q
    insert("b");
    insert("g");
    insert("n");
    insert("s");
    printNode(search("a")); // b
    printNode(search("c")); // b
    printNode(search("b")); // b
    printNode(search("f")); // g
    printNode(search("h")); // g
    printNode(search("g")); // g
    printNode(search("m")); // n
    printNode(search("o")); // n
    printNode(search("n")); // n
    printNode(search("r")); // s
    printNode(search("t")); // s
    printNode(search("s")); // s
    bstFree(root);
    root = NULL;
}

void predecessorTest()
{
    printf("Predecessor Test\n");
    printNode(predecessor("a")); // NULL
    insert("k");
    insert("e");
    insert("q");
    insert("b");
    insert("g");
    insert("n");
    insert("s");
    insert("a");
    insert("c");
    insert("f");
    insert("h");
    insert("m");
    insert("o");
    insert("r");
    insert("t");
    printNode(predecessor("z")); // t
    printNode(predecessor("t")); // s
    printNode(predecessor("p")); // o
    printNode(predecessor("o")); // n
    printNode(predecessor("l")); // k
    printNode(predecessor("h")); // g
    printNode(predecessor("d")); // c
    printNode(predecessor("c")); // b
    printNode(predecessor("a")); // NULL
    bstFree(root);
    root = NULL;
}

void successorTest()
{
    printf("Successor Test\n");
    printNode(successor("a")); // NULL
    insert("k");
    insert("e");
    insert("q");
    insert("b");
    insert("g");
    insert("n");
    insert("s");
    insert("a");
    insert("c");
    insert("f");
    insert("h");
    insert("m");
    insert("o");
    insert("r");
    insert("t");
    printNode(successor("t")); // NULL
    printNode(successor("s")); // t
    printNode(successor("p")); // q
    printNode(successor("m")); // n
    printNode(successor("l")); // m
    printNode(successor("g")); // h
    printNode(successor("d")); // e
    printNode(successor("a")); // b
    printNode(successor("A")); // a
    bstFree(root);
    root = NULL;
}

void deleteTest() {
    printf("Delete Test\n");
    delete("a");
    printNode(root); // NULL
    insert("a"); // root delete (leaf)
    delete("a"); 
    printNode(root); // NULL
    printNode(search("a")); // NULL
    insert("a");
    insert("b");
    delete("a"); // root delete (has left child)
    printNode(search("a")); // b
    insert("c");
    delete("b"); // root delete (has right child)
    printNode(search("b")); // c 
    insert("b");
    insert("d");
    delete("c"); // root delete (2 children)
    printNode(search("a")); // b
    print(); // b d

    bstFree(root);
    root = NULL;

    insert("k");
    insert("e");
    insert("q");
    insert("b");
    insert("g");
    insert("n");
    insert("s");
    insert("a");
    insert("c");
    insert("f");
    insert("h");
    insert("m");
    insert("o");
    insert("r");
    insert("t");

    // 2 child delete root, swap with 0 child successor 
    delete("k");
    printNode(root); // m 
    printNode(search("k")); // h
    print(); // a b c e f g h m n o q r s t

    // 2 child delete root, swap with 1 child successor 
    delete("m");
    printNode(root); // n 
    printNode(search("m")); // h
    print(); // a b c e f g h n o q r s t 

    // 0 child delete 3rd tree level 
    delete("o");
    printNode(root); // n
    printNode(search("o")); // q
    print(); // a b c e f g h n q r s t

    // right child delete 2nd tree level
    delete("q"); 
    printNode(root->right); // s
    printNode(search("q")); // r
    print(); // a b c e f g h n r s t

    // leaf deletion 
    delete("h");
    printNode(search("h")); // g
    print(); // a b c e f g n r s t

    // left child delete 3rd tree level 
    delete("g");
    printNode(search("g")); // f
    print(); // a b c e f n r s t

    bstFree(root);
    root = NULL;
}

void insert(const char *key)
{
    root = bstInsert(root, (const void *)key, (void (*)(void *, const void *))strcpy, stralloc, (int (*)(const void *, const void *))strcmp);
}

struct bstNode *search(const char *key)
{
    return bstSearch(root, (const void *)key, (int (*)(const void *, const void *))strcmp);
}

struct bstNode *predecessor(const char *key)
{
    return bstPredecessor(root, key, (int (*)(const void *, const void *))strcmp);
}

struct bstNode *successor(const char *key)
{
    return bstSuccessor(root, key, (int (*)(const void *, const void *))strcmp);
}

void delete (const char *key)
{
    root = bstDelete(root, key, (int (*)(const void *, const void *))strcmp);
}

void print()
{
    bstPrint(root, toString);
    printf("\n");
}

void printNode(struct bstNode *n)
{
    if (n == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%s\n", toString(n->key));
    }
}

const char *toString(const void *key)
{
    return (const char *)key;
}

size_t stralloc(const void *key)
{
    return strlen((const char *)key) + 1;
}