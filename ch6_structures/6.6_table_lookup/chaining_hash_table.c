/*  
    Contains implementation of a hash table operations for generic data (inc. comparison, copying, allocation, printing).
    This is an expansion of the limited lookup table described in section 6.6 of the text.

    File format :
        1.  Necessary headers
        2.  Constants
        3.  Structure definitions
        4.  Private (static) helper function declarations 
        5.  Public header function definitions 
        6.  Private (static) helper function definitions 

     For runtime calculations of the declarad operations, they are done with respect to the number of entries in
    the table (n) and the capacity of the table (m). 
    
    Operations regarding entry node data such as copying, size, comparison, and string conversion are
    considered to be O(1).

    Author: Chami Lamelas
    6/2/2020
*/

// ***************************** NECESSARY HEADERS ***************************************

#include "hash_table.h" // needed for hash table operations
#include <stdlib.h>     // needed for malloc(), free()
#include <stddef.h>     // needed for size_t
#include <stdio.h>      // needed for printf()

// ***************************** CONSTANTS ***********************************************

#define LOAD_FACTOR 0.75    // ratio of table that must be full to trigger rehash
#define INITIAL_CAPACITY 13 // initial size of internal array

// ***************************** STRUCTURE DEFINITIONS ***********************************

/*
    Structure for an entry in a chained hash table that uses singly linked lists for collision resolution.

    Fields: 
        key (void *) : pointer to key data 
        val (void *) : pointer to value data
        next (struct EntryNode *) : pointer to next EntryNode in SLL 
*/
struct EntryNode
{
    void *key;
    void *val;
    struct EntryNode *next;
};

/*
    Structure that represents a chained hash table. 

    Fields: 
        table (struct EntryNode **) : pointer to array of (struct EntryNode *) SLL heads. 
        size (size_t) : number of entries in the table 
        capacity (size_t) : length of 'table' 
        hash (size_t (*) (const void *)) : hash function to be used on entry keys in the table. 
        keyCmp (int (*) (const void *, const void *)) : comparison function to be used on entry keys. 
        keyCpy (void (*) (void *, const void *)) : copies key data into a void * pointer (destination) 
            from a const void * (source)
        valCpy (void (*) (void *, const void *)) : copies value data into a void * pointer (destination)
            from a const void * (source)
        keySize (size_t (*) (const void *)) : calculates the key allocation size (in bytes) for data referenced
            from a const void * (key pointer)
        valSize (size_t (*) (const void *)) : calculates the value allocation size (in bytes) for data referenced
            from a const void * (value pointer)
        keyToString (const char * (*) (const void *)) : pointer to a function that converts the data referenced 
            by a const void * (key pointer) into a character string. 
        valToString (const char * (*) (const void *)) : pointer to a function that converts the data referenced 
            by a const void * (value pointer) into a character string. 
        keyFree (void (*) (void *)) : frees the memory allocated to a given key pointer (or NULL to signify
            use of standard library free())
        valFree (void (*) (void *)) : frees the memory allocated to a given value pointer (or NULL to signify
            use of standard library free())
*/
struct ChainedHashTable
{
    struct EntryNode **table;
    size_t size;
    size_t capacity;
    size_t (*hash)(const void *);
    int (*keyCmp)(const void *, const void *);
    void (*keyCpy)(void *, const void *);
    void (*valCpy)(void *, const void *);
    size_t (*keySize)(const void *);
    size_t (*valSize)(const void *);
    const char *(*keyToString)(const void *);
    const char *(*valToString)(const void *);
    void (*keyFree)(void *);
    void (*valFree)(void *);
};

// ***************************** PRIVATE HELPER FUNCTION DECLARATIONS ***********************************

/*
    Helper function that rehashes a provided HashTable. The internal array's capacity is doubled. The original
    array is deallocated.

    Parameters: 
        t (HashTable *t) : pointer to table to rehash

    Output: 
        The internal array of t is doubled in size and the elements from the original array are hashed into
        the larger array. 

    Runtime: O(n + m)
*/
static void rehash(HashTable *t);

/*
    Allocates the internal array for a provided HashTable based on its set capacity. 

    Parameters: 
        t (HashTable *t) : pointer to table to allocate an internal array

    Output: 
        The internal array of t is allocated according to its capacity and has its elements initialized to NULL.

    Runtime: O(m)
*/
static void allocInternalTable(HashTable *t);

/*
    Creates an entry from a provided key, value pair to be stored in a HashTable.

    Parameters: 
        t (HashTable *) : pointer to table for which the entry will be created
        key (const void *) : pointer to key data to store in entry
        value (const void *) : pointer to value data to store in entry

    Output: 
        A pointer to the created EntryNode with the key, value pair that's been provided. The EntryNode
        is created from copies of the data referenced by the key and value pointers. This is done using the
        copy and size functions provided by t. If the parameter pointers do not correspond to the functions
        of t, the behavior is undefined. 

    Runtime: O(1)     -- recall: copy and size functions are considered to be constant with respect to n and m.
*/
static struct EntryNode *createEntry(HashTable *t, const void *key, const void *value);

/*
    Frees the memory referenced by a provided EntryNode pointer. 

    Parameters: 
        t (HashTable *) : pointer to a HashTable from which the EntryNode will be freed 
        e (struct EntryNode *) : pointer to an EntryNode to be freed

    Output: 
        The memory allocated to e is freed. The following steps are taken before this:
            Memory allocated to e->key is freed using t->keyFree or free() if t->keyFree = NULL 
            e->key is set to NULL before e's memory is freed
            Memory allocated to e->val is freed using t->valFree or free() if t->valFree = NULL 
            e->val is set to NULL before e's memory is freed
            e->next is set to NULL before e's memory is freed
                NOTE: this can cause memory to be orphaned if e->next is not backed up or been previously freed.

    Runtime: O(1) -- it is assumed that de-allocation functions are constant with respect to m and n
*/
static void freeEntry(HashTable *t, struct EntryNode *e);

// ***************************** PUBLIC HEADER FUNCTION DECLARATIONS ***********************************

HashTable *tableCreate(size_t (*hash)(const void *), int (*keyCmp)(const void *, const void *), void (*keyCpy)(void *, const void *), void (*valCpy)(void *, const void *), size_t (*keySize)(const void *), size_t (*valSize)(const void *), const char *(*keyToString)(const void *), const char *(*valToString)(const void *), void (*keyFree)(void *), void (*valFree)(void *))
{
    // dynamically allocate space to store members of HashTable
    HashTable *t = (HashTable *)malloc(sizeof(HashTable));
    t->capacity = INITIAL_CAPACITY;
    t->size = 0;
    // allocate internal array using initialized capacity
    allocInternalTable(t);
    // initialize members with parameter function pointers
    t->hash = hash;
    t->keyCmp = keyCmp;
    t->keyCpy = keyCpy;
    t->valCpy = valCpy;
    t->keySize = keySize;
    t->valSize = valSize;
    t->keyToString = keyToString;
    t->valToString = valToString;
    t->keyFree = keyFree;
    t->valFree = valFree;
    return t;
}

void tableInsert(HashTable *t, const void *key, const void *value)
{
    // if another insertion will cause n/m to surpass load factor, rehash
    if ((t->size + 1) / ((double)t->capacity) >= LOAD_FACTOR)
    {
        rehash(t);
    }

    // use hash function to get table index
    size_t pos = (*t->hash)(key) % t->capacity;
    // track current node being visited
    struct EntryNode *curr = t->table[pos];
    // track node previous to it (needed for insertion)
    struct EntryNode *prev = NULL;

    // loop over nodes in entry node chain
    while (curr != NULL)
    {
        // if node found with provided key, overwrite node's value with provided value
        if ((*t->keyCmp)(curr->key, key) == 0)
        {
            // free memory allocated to old val
            if (t->valFree == NULL)
            { // use free() if no valFree provided
                free(curr->val);
            }
            else
            { // otherwise, use valFree
                (*t->valFree)(curr->val);
            }
            // allocate space for new value and copy value into node
            curr->val = malloc((*t->valSize)(value));
            (*t->valCpy)(curr->val, value);
            return;
        }

        // otherwise, keep looping
        prev = curr;
        curr = curr->next;
    }

    // if table is empty at this spot, create head of chain
    if (t->table[pos] == NULL)
    {
        t->table[pos] = createEntry(t, key, value);
    }
    // otherwise, prev is known to be non-NULL, add after it
    else
    {
        prev->next = createEntry(t, key, value);
    }
    t->size++; // increase # entries in table
}

void *tableSearch(const HashTable *t, const void *key)
{
    // use hash function to get table index
    size_t pos = t->hash(key) % t->capacity;
    // node that will iterate over chain to search for key
    struct EntryNode *curr = t->table[pos];
    // loop over chain until key found
    while (curr != NULL)
    {
        // if key found, return associated value
        if ((*t->keyCmp)(curr->key, key) == 0)
        {
            return curr->val;
        }
        curr = curr->next;
    }
    return NULL;
}

int tableDelete(HashTable *t, const void *key)
{
    // use hash function to get table index
    size_t pos = t->hash(key) % t->capacity;

    // if table spot is empty, return 0 (nothing to delete)
    if (t->table[pos] == NULL)
    {
        return 0;
    }
    // if chain head is element to delete
    else if ((*t->keyCmp)(key, t->table[pos]->key) == 0)
    {
        // make a copy of pointer to next node in chain so it is not orphaned in freeEntry() call
        struct EntryNode *next = t->table[pos]->next;
        // free memory allocated to key, value, and entry
        freeEntry(t, t->table[pos]);
        // update head of chain
        t->table[pos] = next;
        t->size--;
        return 1;
    }
    // otherwise, element to delete must be after head if it exists
    else
    {
        // previous pointer needed for deletion
        struct EntryNode *prev = t->table[pos];
        // pointer used to search for entry with provided key
        struct EntryNode *curr = t->table[pos]->next;

        // loop over chain
        while (curr != NULL)
        {
            // if entry with matching key found
            if ((*t->keyCmp)(key, curr->key) == 0)
            {
                // unlink entry node from chain (must be done before memory is freed)
                prev->next = curr->next;
                // free key, value, and entry memory that was allocated to it
                freeEntry(t, curr);
                t->size--;
                return 1;
            }
            prev = curr;
            curr = curr->next;
        }

        // end of chain reached without finding key
        return 0;
    }
}

size_t tableSize(const HashTable *t)
{
    return t->size;
}

void tableFree(HashTable *t)
{
    // will be used for looping over chains
    struct EntryNode *tmp = NULL;
    // for each chain
    for (size_t i = 0; i < t->capacity; i++)
    {
        // delete and free head for each chain until head is NULL
        while (t->table[i] != NULL)
        {
            // store head's next node before it's freed
            tmp = t->table[i]->next;
            // free the head and its key, value data
            freeEntry(t, t->table[i]);
            // update head
            t->table[i] = tmp;
        }
    }

    // all chains destroyed, can free the table and set it to NULL
    free((void *)t->table);
    t->table = NULL;
    // set size, capacity to 0
    t->size = 0;
    t->capacity = 0;
    // set function pointers to NULL
    t->keyCmp = NULL;
    t->keyCpy = NULL;
    t->keyFree = NULL;
    t->keySize = NULL;
    t->keyToString = NULL;
    t->valCpy = NULL;
    t->valFree = NULL;
    t->valSize = NULL;
    t->valToString = NULL;
    // free memory allocated to table
    free((void *)t);
}

void tablePrint(const HashTable *t)
{
    printf("\n");
    // will iterate over chains in table
    struct EntryNode *curr = NULL;
    // for each chain
    for (size_t i = 0; i < t->capacity; i++)
    {
        // curr will iterate over chain and print each entry's data using table's toString() functions
        curr = t->table[i];
        while (curr != NULL)
        {
            printf("[\nKey: %s\nValue: %s\n]\n", (*t->keyToString)(curr->key), (*t->valToString)(curr->val));
            curr = curr->next;
        }
    }
    printf("\n");
}

// ***************************** PRIVATE HELPER FUNCTION DEFINITIONS ***********************************

static void rehash(HashTable *t)
{
    // create another pointer to point at original table
    struct EntryNode **tableCpy = t->table;
    // double new table's capacity and allocate an array of this size
    t->capacity *= 2;
    allocInternalTable(t);
    // pointer to iterate over original table
    struct EntryNode *tmp = NULL;
    // pointer used in copying original data over
    struct EntryNode *add = NULL;
    // table index value
    size_t pos;

    // loop over original table (half the new capacity)
    // note that t->capacity will always be even at this point
    for (size_t i = 0; i < t->capacity / 2; i++)
    {
        // until current chain is empty
        while (tableCpy[i] != NULL)
        {
            // save pointer to next entry before this entry is freed
            tmp = tableCpy[i]->next;
            // get table index of entry to copy over
            pos = t->hash(tableCpy[i]->key) % t->capacity;

            // adding into t->table, allocate new entry to add and put at top of chain
            add = (struct EntryNode *)malloc(sizeof(struct EntryNode));
            // don't need to copy over data of key, val just copy pointers to that data
            // shallow copy is fine because we want the data from pre-rehash to remain the same
            // will remove the old pointers in the freeing process below
            add->key = tableCpy[i]->key;
            add->val = tableCpy[i]->val;
            // for O(1) addition time, add at head of current chain
            add->next = t->table[pos];
            t->table[pos] = add;

            // freeing memory of EntryNode from copied table
            tableCpy[i]->key = NULL;
            tableCpy[i]->val = NULL;
            tableCpy[i]->next = NULL;
            free((void *)tableCpy[i]);

            // move to next element in chain
            tableCpy[i] = tmp;
        }
    }

    // now that all the elements of original table are null, can free original memory
    free((void *)tableCpy);
    tableCpy = NULL;
}

void allocInternalTable(HashTable *t)
{
    // allocate array of chains based on current capacity
    t->table = (struct EntryNode **)calloc(t->capacity, sizeof(struct EntryNode *));
    // set all chains to  be empty (NULL) or they will be garbage
    for (size_t i = 0; i < t->capacity; i++)
    {
        t->table[i] = NULL;
    }
}

static struct EntryNode *createEntry(HashTable *t, const void *key, const void *value)
{
    // allocate memory for the entry 
    struct EntryNode *e = (struct EntryNode *)malloc(sizeof(struct EntryNode));
    // allocate space for the key and copy data into key pointer 
    e->key = malloc((*t->keySize)(key));
    (*t->keyCpy)(e->key, key);
    // allocate space for the val and copy data into val
    e->val = malloc((*t->valSize)(value));
    (*t->valCpy)(e->val, value);
    // set next to NULL so it is not garbage 
    e->next = NULL;
    return e;
}

static void freeEntry(HashTable *t, struct EntryNode *e)
{
    // if no free function has been provided for keys, use library free
    if (t->keyFree == NULL)
    {
        free(e->key);
    }
    // otherwise, use provided function 
    else
    {
        (*t->keyFree)(e->key);
    }
    // memory freed, now set pointer to NULL 
    e->key = NULL;
    // if no free function has been provided for values, use library free
    if (t->valFree == NULL)
    {
        free(e->val);
    }
    // otherwise, use provided function 
    else
    {
        (*t->valFree)(e->val);
    }
    // memory freed, now set pointer to NULL
    e->val = NULL;
    // set next to NULL before memory is freed 
    // NOTE: this leaves susceptibility for orphaned memory if client code isn't correct
    e->next = NULL;
    // free memory used by entry 
    free((void *)e);
}