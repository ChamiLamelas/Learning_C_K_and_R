#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

struct entry
{
    void *key;
    void *val;
    struct entry *next;
};

struct HashTable
{
    struct entry **table;
    size_t size;
    size_t capacity;
    size_t (*hash)(const void *);
    int (*keyCmp)(const void *, const void *);
    void (*keyCpy)(void *, const void *);
    void (*valCpy)(void *, const void *);
    size_t (*keySize)(const void *);
    size_t (*valSize)(const void *);
    const char *(*keyToString) (const void *);
    const char *(*valToString) (const void *);
};

struct HashTable *tableCreate(size_t (*hash)(const void *), int (*keyCmp)(const void *, const void *), void (*keyCpy)(void *, const void *), void (*valCpy)(void *, const void *), size_t (*keySize)(const void *), size_t (*valSize)(const void *), const char *(*keyToString) (const void *), const char *(*valToString) (const void *));

void tableInsert(struct HashTable *t, const void *key, const void *value);

void *tableSearch(struct HashTable *t, const void *key);

int tableDelete(struct HashTable *t, const void *key);

void tableFree(struct HashTable *t);

void tablePrint(struct HashTable *t);

#endif