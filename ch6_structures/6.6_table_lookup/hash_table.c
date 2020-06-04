#include "hash_table.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define LOAD_FACTOR 0.75
#define INITIAL_CAPACITY 13

static void rehash(struct HashTable *t);
void allocInternalTable(struct HashTable *t);
static struct entry *createEntry(struct HashTable *t, const void *key, const void *value);
static void freeEntry(struct entry *e);

struct HashTable *tableCreate(size_t (*hash)(const void *), int (*keyCmp)(const void *, const void *), void (*keyCpy)(void *, const void *), void (*valCpy)(void *, const void *), size_t (*keySize)(const void *), size_t (*valSize)(const void *), const char *(*keyToString)(const void *), const char *(*valToString)(const void *))
{
    struct HashTable *t = (struct HashTable *)malloc(sizeof(struct HashTable));
    t->capacity = INITIAL_CAPACITY;
    t->size = 0;
    allocInternalTable(t);
    t->hash = hash;
    t->keyCmp = keyCmp;
    t->keyCpy = keyCpy;
    t->valCpy = valCpy;
    t->keySize = keySize;
    t->valSize = valSize;
    t->keyToString = keyToString;
    t->valToString = valToString;
    return t;
}

void tableInsert(struct HashTable *t, const void *key, const void *value)
{
    if (((double)t->size) / t->capacity >= LOAD_FACTOR)
    {
        rehash(t);
    }

    size_t pos = (*t->hash)(key) % t->capacity;
    struct entry *curr = t->table[pos];
    struct entry *prev = NULL;

    while (curr != NULL)
    {
        if ((*t->keyCmp)(curr->key, key) == 0)
        {
            free(curr->val);
            curr->val = malloc((*t->valSize)(value));
            (*t->valCpy)(curr->val, value);
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    prev->next = createEntry(t, key, value);
    t->size++;
    return 1; 
}

void *tableSearch(struct HashTable *t, const void *key)
{
    size_t pos = t->hash(key) % t->capacity;
    struct entry *curr = t->table[pos];
    while (curr != NULL)
    {
        if ((*t->keyCmp)(curr->key, key) == 0)
        {
            return curr->val;
        }
        curr = curr->next;
    }
    return NULL;
}

int tableDelete(struct HashTable *t, const void *key)
{
    size_t pos = t->hash(key) % t->capacity;
    if (t->table[pos] == NULL)
    {
        return 0;
    }
    else if ((*t->keyCmp)(key, t->table[pos]->key) == 0)
    {
        struct entry *next = t->table[pos]->next;
        freeEntry(t->table[pos]);
        t->table[pos] = next;
        t->size--;
        return 1;
    }
    else
    {
        struct entry *prev = t->table[pos];
        struct entry *curr = t->table[pos]->next;
        while (curr != NULL) {
            if ((*t->keyCmp)(key, curr->key) == 0) {
                prev->next = curr->next;
                freeEntry(curr);
                t->size--;
                return 1;
            }
            prev = curr;
            curr = curr->next;
        }

        return 0;
    }
}

void tableFree(struct HashTable *t)
{
    struct entry *tmp = NULL;
    for (int i = 0; i < t->capacity; i++)
    {
        while (t->table[i] != NULL)
        {
            tmp = t->table[i]->next;
            freeEntry(t->table[i]);
            t->table[i] = tmp;
        }
    }

    free((void *)t->table);
    t->table = NULL;
    t->size = 0;
    t->capacity = 0;
}

void tablePrint(struct HashTable *t)
{
    struct entry *curr = NULL;
    for (int i = 0; i < t->capacity; i++)
    {
        curr = t->table[i];
        while (curr != NULL)
        {
            printf("[\nKey: %s\nValue: %s\n]\n", t->keyToString(curr->key), t->valToString(curr->val));
            curr = curr->next;
        }
    }
}

static void rehash(struct HashTable *t)
{
    struct entry **tableCpy = t->table;
    t->capacity *= 2;
    allocInternalTable(t);
    struct entry *tmp = NULL;
    struct entry *curr = NULL;
    struct entry *add = NULL;
    size_t pos = -1;
    for (int i = 0; i < t->capacity / 2; i++)
    {
        while (tableCpy[i] != NULL)
        {
            tmp = tableCpy[i]->next;
            pos = t->hash(tableCpy[i]->key) % t->capacity;

            // adding into t->table, allocate new entry to add and put at top of chain
            add = (struct entry *)malloc(sizeof(struct entry));
            add->key = tableCpy[i]->key;
            add->val = tableCpy[i]->val;
            add->next = t->table[pos];
            t->table[pos] = add;

            // freeing memory of entry from copied table
            free((void *)tableCpy[i]);
            tableCpy[i]->key = NULL;
            tableCpy[i]->val = NULL;
            tableCpy[i]->next = NULL;

            // move to next element in chain
            tableCpy[i] = tmp;
        }
    }

    free((void *)tableCpy);
    tableCpy = NULL;
}

void allocInternalTable(struct HashTable *t)
{
    t->table = (struct entry **)malloc(t->capacity * sizeof(struct entry *));
    for (int i = 0; i < t->capacity; i++)
    {
        t->table[i] = NULL;
    }
}

static struct entry *createEntry(struct HashTable *t, const void *key, const void *value)
{
    struct entry *e = (struct entry *)malloc(sizeof(struct entry));
    e->key = malloc((*t->keySize)(key));
    (*t->keyCpy)(e->key, key);
    e->val = malloc((*t->valSize)(value));
    (*t->valCpy)(e->val, value);
    e->next = NULL;
    return e;
}

static void freeEntry(struct entry *e)
{
    free(e->key);
    e->key = NULL;
    free(e->val);
    e->val = NULL;
    e->next = NULL;
    free((void *)e);
}