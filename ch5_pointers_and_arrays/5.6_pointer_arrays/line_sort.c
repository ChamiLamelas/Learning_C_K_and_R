#include "C:\Users\Chami\programming\c\kernigan_ritchie\ch5_pointers_and_arrays\5.5_character_pointers_and_functions\string.h"
#include "C:\Users\Chami\programming\c\kernigan_ritchie\ch5_pointers_and_arrays\5.4_address_arithmetic\memory_allocation.h"
#include <stdio.h> 

int readLines(char *lines[]);
void quickSort(char *arr[], int left, int right);
int partition(char *arr[], int left, int right);

#define MAX_LINES 1000 

int main() {
    char *lines[MAX_LINES];

    int numLines = readLines(lines);
    quickSort(lines, 0, numLines - 1);

    for (int i = 0; i < numLines; i++) {
        printf("%s\n", lines[i]);
    }

    return 0; 
}

int readLines(char *lines[]) {
    const int MAX_LINE_LENGTH = 100; 

    int numLines = 0; 
    lines[0] = alloc(MAX_LINE_LENGTH);
    int len = getline(lines[0], MAX_LINE_LENGTH);

    while (len != EOF && numLines < MAX_LINES - 1) {
        numLines++;
        lines[numLines] = alloc(MAX_LINE_LENGTH);
        len = getline(lines[numLines], MAX_LINE_LENGTH);
    }
    
    return numLines;
}

void quickSort(char *arr[], int left, int right) {
    if (left >= right) {
        return;
    }

    int x = partition(arr, left, right);
    quickSort(arr, left, x - 1);
    quickSort(arr, x + 1, right);
}

int partition(char *arr[], int left, int right) {
    char *x = arr[left];
    int i = left; 
    char *tmp = NULL;

    for (int j = left + 1; j <= right; j++) {
        if (strcmp(arr[j], x) <= 0) {
            i++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    tmp = arr[left];
    arr[left] = arr[i];
    arr[i] = tmp; 

    return i;
}