/*
    This file contains an implementation of generic quick sort for a pointer array of any type and for a provided comparison function. 
    
    Furthermore, it contains a set of functions that could be used to implement the command flags discussed in the text. 

        1.  strNumCmp : compares two strings treating them as numbers (can be used to implement example on p. 120-1 in text)
        2.  strReverseCmp : compares two strings in the opposite way as strcmp from string.h (can be used to implement flag in exercise 5-14)
        3.  strIgnoreCaseCmp : compares two strings ignoring the case (can be used to implement flag in exercise 5.15)
        4.  strDirOrderCmp : compares two strings in "directory order" from the text (can be used to implement flag in exercise 5.16)
        5.  numCmp : compares values referenced by 2 integer pointers (can be used to compare numbers in integer sorting algorithms)
    
    NOTE: int (*)(void *, void *) is a TYPE. 
    
    That is, it is a pointer to a function that returns int and takes arguments void *, void *

    Similarly, int (*)(const char *, const char *) is a TYPE. 

    That is, it is a pointer to a function that returns int and takes arguments const char *, const char *
*/

#include <stdio.h>
#include "C:\Users\Chami\programming\c\kernigan_ritchie\ch5_pointers_and_arrays\5.4_address_arithmetic\memory_allocation.h"
#include "C:\Users\Chami\programming\c\kernigan_ritchie\ch5_pointers_and_arrays\5.5_character_pointers_and_functions\string.h"

#define MAX_LINES 1000

void quickSort(void *arr[], int left, int right, int (*compareTo)(void *, void *));
int partition(void *arr[], int left, int right, int (*compareTo)(void *, void *));
void swap(void *arr[], int i, int j);

int strNumCmp(const char *s, const char *t);
int strReverseCmp(const char *s, const char *t);
int strIgnoreCaseCmp(const char *s, const char *t);
int strDirOrderCmp(const char *s, const char *t);
int isDirChar(int c);
int numCmp(int *p, int *q);

int readLines(char *lines[]);

int main()
{
    // positive, negative, 0, negative, negative, positive
    printf("%d %d %d %d %d %d\n", strNumCmp("123", "12"), strNumCmp("12", "123"), strNumCmp("123", "123"), strNumCmp("-123", "123"), strNumCmp("-123", "-12"), strNumCmp("-12", "-123"));

    // negative, positive, 0, positive, negative, positive
    printf("%d %d %d %d %d %d\n", strReverseCmp("123", "12"), strReverseCmp("12", "123"), strReverseCmp("123", "123"), strReverseCmp("-123", "123"), strReverseCmp("-123", "-12"), strReverseCmp("-12", "-123"));

    // 0 0 0 0 positive, negative, 0, negative, positive, negative
    printf("%d %d %d %d %d %d %d %d %d %d\n", strIgnoreCaseCmp("a", "A"), strIgnoreCaseCmp("", ""), strIgnoreCaseCmp("ABC", "ABc"), strIgnoreCaseCmp("abc", "ABC"), strIgnoreCaseCmp("123", "12"), strIgnoreCaseCmp("12", "123"), strIgnoreCaseCmp("123", "123"), strIgnoreCaseCmp("-123", "123"), strIgnoreCaseCmp("-123", "-12"), strIgnoreCaseCmp("-12", "-123"));

    // 0
    printf("%d ", strDirOrderCmp("!a@1# $", "a1 "));

    // 0
    printf("%d ", strDirOrderCmp("a1 ", "!a@1# $"));

    // negative
    printf("%d ", strDirOrderCmp("a1 ", "!b@1# $"));

    // positive
    printf("%d ", strDirOrderCmp("b1 ", "!a@1# $"));

    // positive
    printf("%d ", strDirOrderCmp("b1 ", "!B@1# $"));

    // negative
    printf("%d ", strDirOrderCmp("B1 ", "!b@1# $"));

    // 0
    printf("%d ", strDirOrderCmp(" ", "!@# $"));

    // 0
    printf("%d ", strDirOrderCmp("abc", "abc"));

    printf("\n");

    int a = 1;
    int *aPtr = &a;
    int b = 2;
    int *bPtr = &b;
    int c = 2;
    int *cPtr = &c;

    // negative, positive, 0
    printf("%d %d %d\n", numCmp(aPtr, bPtr), numCmp(bPtr, aPtr), numCmp(bPtr, cPtr));

    // re-writing regular sort (no args)

    char *lines[MAX_LINES];

    int numLines = readLines(lines);

    // 2 casts are done in this call to quickSort() - compilation errors will occur otherwise
    // The first is that lines is cast from char** to void**
    // The second is that strcmp is cast from int (*)(const char *, const char *) to int (*)(void *, void *)
    quickSort((void **)lines, 0, numLines - 1, (int (*)(void *, void *))strcmp);

    for (int i = 0; i < numLines; i++)
    {
        printf("%s\n", lines[i]);
    }

    return 0;
}

int readLines(char *lines[])
{
    const int MAX_LINE_LENGTH = 100;

    int numLines = 0;
    lines[0] = alloc(MAX_LINE_LENGTH);
    int len = getline(lines[0], MAX_LINE_LENGTH);

    while (len != EOF && numLines < MAX_LINES - 1)
    {
        numLines++;
        lines[numLines] = alloc(MAX_LINE_LENGTH);
        len = getline(lines[numLines], MAX_LINE_LENGTH);
    }

    return numLines;
}

void quickSort(void *arr[], int left, int right, int (*compareTo)(void *, void *))
{
    if (left >= right)
    {
        return;
    }

    int x = partition(arr, left, right, compareTo);
    quickSort(arr, left, x - 1, compareTo);
    quickSort(arr, x + 1, right, compareTo);
}

int partition(void *arr[], int left, int right, int (*compareTo)(void *, void *))
{
    void *x = arr[left];
    int i = left;

    for (int j = left + 1; j <= right; j++)
    {
        if ((*compareTo)(arr[j], x) <= 0)
        {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, left, i);
    return i;
}

void swap(void *arr[], int i, int j)
{
    void *tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int strNumCmp(const char *s, const char *t)
{
    int sInt = stringToInt(s);
    int tInt = stringToInt(t);

    if (sInt == 0 && strcmp(s, "0") != 0)
    {
        return 0;
    }

    if (tInt == 0 && strcmp(t, "0") != 0)
    {
        return 0;
    }

    return sInt - tInt;
}

int strReverseCmp(const char *s, const char *t)
{
    return -1 * strcmp(s, t);
}

int strIgnoreCaseCmp(const char *s, const char *t)
{
    while (toLower(*s) == toLower(*t) && *s != '\0' && *t != '\0')
    {
        s++;
        t++;
    }

    return *s - *t;
}

int strDirOrderCmp(const char *s, const char *t)
{
    while (*s != '\0' && *t != '\0')
    {
        while (*s != '\0' && !isDirChar(*s))
        {
            s++;
        }
        while (*t != '\0' && !isDirChar(*t))
        {
            t++;
        }

        if (*s != *t)
        {
            return *s - *t;
        }

        s++;
        t++;
    }

    return 0;
}

int isDirChar(int c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ';
}

int numCmp(int *p, int *q)
{
    return *p - *q;
}