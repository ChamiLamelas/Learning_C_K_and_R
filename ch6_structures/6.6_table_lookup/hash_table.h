/*
    Contains declarations of hash table operations for generic data (inc. comparison, copying, allocation, printing).
    This is an expansion of the limited look up table described in section 6.6 of the text.

    For runtime calculations of the declarad operations, they are done with respect to the number of entries in
    the table (n) and the capacity of the table (m). 
    
    Operations regarding entry node data such as copying, size, comparison, and string conversion are
    considered to be O(1).

    NOTE: Throughout the use of this data structure, if key type is not consistent with the input functions
    provided in tableCreate(), the behavior is undefined.

    Author: Chami Lamelas
    6/2/2020
*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

/*
    Type definition of the HashTable. It will be implemented via a structure that uses linked list chaining. 
*/
typedef struct ChainedHashTable HashTable;

/*
    Creates a HashTable for client use. 

    Parameters: 
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
        keyFree (void (*) (void *)) : frees the memory allocated to a given key pointer
        valFree (void (*) (void *)) : frees the memory allocated to a given value pointer
    
    Output: 
        A pointer to a HashTable that has been created with the provided function parameters. The created
        HashTable will be initialized to an implementation-defined initial capacity.

        If keyFree or valFree is left as NULL, then the library function free() will be used on key and value
        pointers instead. Note, the library version of free() on its own will not work to deallocate the data 
        referenced by key, value pointers if it contains dynamically allocated members. Therefore, keyFree and 
        valFree should be designed to deallocate dynamically allocated members of key and value data. 

    Runtime: O(m)
*/
HashTable *tableCreate(size_t (*hash)(const void *), int (*keyCmp)(const void *, const void *), void (*keyCpy)(void *, const void *), void (*valCpy)(void *, const void *), size_t (*keySize)(const void *), size_t (*valSize)(const void *), const char *(*keyToString) (const void *), const char *(*valToString) (const void *), void (*keyFree)(void *), void (*valFree)(void *));

/*
    Inserts a new (key, value) entry into a provided HashTable. If the key already exists, then its previously
    associated value is overwritten with the newly provided value.

    Parameters: 
        t (HashTable *) : pointer to the HashTable to update 
        key (const void *) : pointer to generic key data (const => not modified, copied before insertion)
        value (const void *) : pointer to generic value data (const => not modified, copied before insertion)

    Output: 
        If key does not exist in the table referenced by t, then a new entry of key, value is inserted. The 
            insertion makes a copy of the key, value pair using the key, value copy functions provided in 
            tableCreate(). 

        If key exists, then the value previously associated with t is overwritten with value. That is, a copy
            of the value is made using the key copy function provided in the tableCreate().

    Runtime: 
        O(n + m) : If the table becomes full, it will be resized. This will only occur when the ratio of the
        table's number of entries to the table's capacity surprasses the load factor (implementation-defined). 

        O(n) : If all of the previously inserted entries hash to the same table index. This would occur in the
        case of an extremely poorly designed hash function. Note that this could be improved to O(log(n)) 
        using a balanced BST in place of an SLL. 

        O(k) : Let k = the average chain length in the table. This should be relatively small if the hash
        function has been designed properly. This is the runtime in most cases provided a good hash function.
        If k is considered as the average number of entries per chain, then performance could be improved to
        O(log(k)) if a balcned BST was used in place of an SLL. 
*/
void tableInsert(HashTable *t, const void *key, const void *value);

/*
    Searches a provided HashTable for the value associated with a provided key.

    Parameters: 
        t (const HashTable *) : pointer to the HashTable to search (const, won't be modified in the search).
        key (const void *) : pointer to generic key data to search for 

    Output: 
        If there exists a key, value entry in the table referenced by t that has the provided key, then the
        value associated with it is returned. If there is no entry with the provided key, then NULL is 
        returned. 

    Runtime: 
        O(n) : If all of the previously inserted entries hash to the same table index. This would occur in the
        case of an extremely poorly designed hash function. Note that this could be improved to O(log(n)) 
        using a balanced BST in place of an SLL. 

        O(k) : Let k = the average chain length in the table. This should be relatively small if the hash
        function has been designed properly. This is the runtime in most cases provided a good hash function.
        If k is considered as the average number of entries per chain, then performance could be improved to
        O(log(k)) if a balcned BST was used in place of an SLL. 
*/
void *tableSearch(const HashTable *t, const void *key);

/*
    Deletes a provided key from a provided HashTable.

    Parameters: 
        t (HashTable *) : pointer to the HashTable to delete from
        key (const void *) : pointer to generic key data to delete

    Output: 
        If there exists a key, value entry in the table referenced by t that has the provided key, then the
        entry containing the key is deleted from the table and is de-allocated. This is done using the free
        functions provided in tableCreate() or the library free function if none were provided. In the
        case of a deletion being done successfully, 1 is returned.

        If no such entry exists, then 0 is returned.

    Runtime: 
        O(n) : If all of the previously inserted entries hash to the same table index. This would occur in the
        case of an extremely poorly designed hash function. Note that this could be improved to O(log(n)) 
        using a balanced BST in place of an SLL. 

        O(k) : Let k = the average chain length in the table. This should be relatively small if the hash
        function has been designed properly. This is the runtime in most cases provided a good hash function.
        If k is considered as the average number of entries per chain, then performance could be improved to
        O(log(k)) if a balcned BST was used in place of an SLL. 
*/
int tableDelete(HashTable *t, const void *key);

/*
    Retrieves the number of entries currently contained in a provided HashTable. 

    Parameters: 
        t (const HashTable *) : a pointer to a HashTable (not modified).

    Output: 
        The number of entries in the HashTable referenced by t. 

    Runtime: O(1)
*/
size_t tableSize(const HashTable *t);

/*
    De-allocates the memory allocated to a provided HashTable.

    Parameters: 
        t (HashTable *) : pointer to a HashTable to free 

    Output: 
        The memory previously allocated to t is freed. Note that this will properly set all internally de-allocated
        memory to NULL, but not t. Therefore, the calling function should do this to avoid undefined behavior. 

    Runtime: O(m + n)
*/
void tableFree(HashTable *t);

/*
    Prints the entries stored in a provided HashTable to stdout.

    Parameters: 
        t (const HashTable *) : pointer to HashTable to print

    Output: 
        The entries of the table are printed in an implementation-defined manner using the toString functions
        provided in tableCreate(). 

    Runtime: O(n + m)
*/
void tablePrint(const HashTable *t);

#endif