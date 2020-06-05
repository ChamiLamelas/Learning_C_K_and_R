#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

HashTable *t = NULL;

size_t strHash(const void *s);
size_t strSize(const void *s);
const char *strToString(const void *s);
void insertTest(void);
void searchTest(void);
void deleteTest(void);

int main()
{
    insertTest();
    searchTest();
    deleteTest();
    return 0;
}

void insertTest(void)
{
    t = tableCreate(strHash, (int (*)(const void *, const void *))strcmp, (void (*)(void *, const void *))strcpy, (void (*)(void *, const void *))strcpy, strSize, strSize, strToString, strToString, NULL, NULL);
    printf("size=%u\n", tableSize(t));
    printf("HASHES: [%u %u %u %u %u %u %u %u]\n", strHash("cosi10"), strHash("cosi11"), strHash("cosi12"), strHash("cosi112"), strHash("cosi127"), strHash("cosi110"), strHash("<A"), strHash("<B"));
    printf("HASHES (m = 13): [%u %u %u %u %u %u %u %u]\n", strHash("cosi10") % 13, strHash("cosi11") % 13, strHash("cosi12") % 13, strHash("cosi112") % 13, strHash("cosi127") % 13, strHash("cosi110") % 13, strHash("<A") % 13, strHash("<B") % 13);
    printf("HASHES (m = 26): [%u %u %u %u %u %u %u %u]\n", strHash("cosi10") % 26, strHash("cosi11") % 26, strHash("cosi12") % 26, strHash("cosi112") % 26, strHash("cosi127") % 26, strHash("cosi110") % 26, strHash("<A") % 26, strHash("<B") % 26);

    // testing overwrite of insert
    tableInsert(t, "cosi10", "java");
    tablePrint(t);
    printf("size=%u\n", tableSize(t));
    tableInsert(t, "cosi10", "python");
    tablePrint(t);
    printf("size=%u\n", tableSize(t));

    // testing insertion no collision (next chain in internal table)
    tableInsert(t, "cosi11", "java");
    tablePrint(t);
    printf("size=%u\n", tableSize(t));

    // testing insertion collision (chain created at index with cosi11) -- hash dep on cap
    tableInsert(t, "<A", "a");
    tablePrint(t);
    printf("size=%u\n", tableSize(t));

    // inserting till we have 10 elements (force rehash)
    // initial cap = 13, load_factor = 0.75, 10/13 ~ 0.77

    // collide to create another 2 element chain -- hash dep on cap
    tableInsert(t, "cosi12", "java");
    tableInsert(t, "<B", "b");
    tablePrint(t);
    printf("size=%u\n", tableSize(t));

    // collide 2x to create a 3 element chain -- hash indep of cap
    tableInsert(t, "cosi112", "python");
    tableInsert(t, "cosi121", "scheme");
    tableInsert(t, "cosi211", "c");
    tablePrint(t);
    printf("size=%u\n", tableSize(t));

    // insert 2 more elements that don't collide
    tableInsert(t, "cosi127", "SQL");
    tableInsert(t, "cosi101", "matlab"); // this will trigger a rehash
    tablePrint(t);
    printf("size=%u\n", tableSize(t));

    // test overwrite post rehash
    tableInsert(t, "cosi112", "Python3");
    tableInsert(t, "cosi121", "Lisp");
    tableInsert(t, "cosi211", "C++");
    tablePrint(t);
    printf("size=%u\n", tableSize(t));

    tableFree(t);
    printf("INSERT TEST DONE.\n");
}

void searchTest(void)
{
    t = tableCreate(strHash, (int (*)(const void *, const void *))strcmp, (void (*)(void *, const void *))strcpy, (void (*)(void *, const void *))strcpy, strSize, strSize, strToString, strToString, NULL, NULL);

    // search empty table
    printf("%p\n", tableSearch(t, "cosi10")); // NULL

    // insert + overwrite to check if search works
    tableInsert(t, "cosi10", "java");
    printf("%s\n", tableSearch(t, "cosi10")); // java
    tableInsert(t, "cosi10", "python");
    printf("%s\n", tableSearch(t, "cosi10")); // python

    // testing insertion then will search for collision and re-insert
    tableInsert(t, "cosi11", "java");
    printf("%s\n", tableSearch(t, "cosi11")); // java
    printf("%p\n", tableSearch(t, "<A"));     // NULL

    // testing insertion collision (chain created at index with cosi11) -- hash dep on cap
    tableInsert(t, "<A", "a");
    printf("%s\n", tableSearch(t, "<A")); // a

    // collide to create another 2 element chain -- hash dep on cap
    tableInsert(t, "cosi12", "java");
    tableInsert(t, "<B", "b");
    printf("%p\n", tableSearch(t, "cosi21")); // NULL

    // collide 2x to create a 3 element chain -- hash indep of cap
    tableInsert(t, "cosi112", "python");
    tableInsert(t, "cosi121", "scheme");
    tableInsert(t, "cosi211", "c");
    printf("%s\n", tableSearch(t, "cosi211")); // c
    printf("%s\n", tableSearch(t, "cosi121")); // scheme
    printf("%s\n", tableSearch(t, "cosi112")); // python

    // insert 2 more elements that don't collide
    tableInsert(t, "cosi127", "SQL");
    tableInsert(t, "cosi101", "matlab"); // this will trigger a rehash

    // test overwrite post rehash
    tableInsert(t, "cosi112", "Python3");
    tableInsert(t, "cosi121", "Lisp");
    tableInsert(t, "cosi211", "C++");

    printf("%s\n", tableSearch(t, "cosi10"));  // python
    printf("%s\n", tableSearch(t, "cosi11"));  // java
    printf("%s\n", tableSearch(t, "cosi12"));  // java
    printf("%s\n", tableSearch(t, "cosi112")); // Python3
    printf("%s\n", tableSearch(t, "cosi121")); // Lisp
    printf("%s\n", tableSearch(t, "cosi211")); // C++
    printf("%s\n", tableSearch(t, "cosi127")); // SQL
    printf("%s\n", tableSearch(t, "cosi101")); // matlab
    printf("%s\n", tableSearch(t, "<A"));      // a
    printf("%s\n", tableSearch(t, "<B"));      // b

    printf("%p\n", tableSearch(t, "cosi01")); // NULL
    printf("%p\n", tableSearch(t, "cosi21")); // NULL

    tableFree(t);

    printf("SEARCH TEST DONE.\n");
}

void deleteTest(void)
{
    t = tableCreate(strHash, (int (*)(const void *, const void *))strcmp, (void (*)(void *, const void *))strcpy, (void (*)(void *, const void *))strcpy, strSize, strSize, strToString, strToString, NULL, NULL);
    printf("%d ", tableDelete(t, "cosi10")); // 0
    printf("%u\n", tableSize(t));            // 0

    tableInsert(t, "cosi10", "java");
    printf("%d ", tableDelete(t, "cosi10"));  // 1
    printf("%u\n", tableSize(t));             // 0
    printf("%p\n", tableSearch(t, "cosi10")); // NULL

    tableInsert(t, "cosi10", "java");
    tableInsert(t, "cosi11", "java");
    printf("%d ", tableDelete(t, "<A")); // 0
    printf("%u\n", tableSize(t));        // 2
    printf("%s\n", tableSearch(t, "cosi10")); // java
    printf("%s\n", tableSearch(t, "cosi11")); // java

    tableInsert(t, "<A", "a");
    // delete end of chain (<A)
    printf("%d ", tableDelete(t, "<A"));  // 1
    printf("%u ", tableSize(t));          // 2
    printf("%d\n", tableDelete(t, "<A")); // 0
    printf("%s\n", tableSearch(t, "cosi11")); // java
    printf("%p\n", tableSearch(t, "<A")); // NULL

    tableInsert(t, "cosi12", "java");
    tableInsert(t, "<B", "b");
    // delete top of chain (cosi12b)
    printf("%d ", tableDelete(t, "cosi12"));  // 1
    printf("%u ", tableSize(t));              // 3
    printf("%d\n", tableDelete(t, "cosi12")); // 0
    printf("%s\n", tableSearch(t, "<B")); // b
    printf("%p\n", tableSearch(t, "cosi12")); // NULL

    tableInsert(t, "cosi112", "python");
    tableInsert(t, "cosi121", "scheme");
    tableInsert(t, "cosi211", "c");
    // delete middle of list
    printf("%d ", tableDelete(t, "cosi121"));  // 1
    printf("%u ", tableSize(t));               // 5
    printf("%d\n", tableDelete(t, "cosi121")); // 0
    printf("%s\n", tableSearch(t, "cosi112")); // python
    printf("%s\n", tableSearch(t, "cosi211")); // c
    printf("%p\n", tableSearch(t, "csoi121")); // NULL

    // delete top 2x
    printf("%d ", tableDelete(t, "cosi112"));  // 1
    printf("%d ", tableDelete(t, "cosi211"));  // 1
    printf("%u ", tableSize(t));               // 3
    printf("%d ", tableDelete(t, "cosi112")); // 0
    printf("%d\n", tableDelete(t, "cosi211")); // 0
    printf("%p\n", tableSearch(t, "cosi112")); // NULL
    printf("%p\n", tableSearch(t, "cosi211")); // NULL
    printf("%p\n", tableSearch(t, "csoi121")); // NULL
    
    tableFree(t);

    printf("DELETE TEST DONE.\n");
}

size_t strHash(const void *s)
{
    size_t h = 0;
    const char *cs = (const char *)s;
    while (*cs != '\0')
    {
        h += *cs - '\0';
        cs++;
    }
    return h;
}

size_t strSize(const void *s)
{
    return strlen((const char *)s) + 1;
}

const char *strToString(const void *s)
{
    return (const char *)s;
}