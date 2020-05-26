#include <stdio.h> 

void shellSort(int arr[], int n); 
void print(const int arr[], int n);

int main() {
    int A[] = {1, 2, 3, 4};
    int B[] = {4, 3, 2, 1};
    int C[] = {};
    int D[] = {1};
    int E[] = {2, 1};

    shellSort(A, 4);
    shellSort(B, 4);
    shellSort(C, 0);
    shellSort(D, 1);
    shellSort(E, 2);

    print(A, 4);
    print(B, 4);
    print(C, 0);
    print(D, 1);
    print(E, 2);

    return 0; 
}

/*
    Sorts an array of n integers using Shell's O(n^2) sorting algorithm.

    Parameters: 
        arr : input array (integers)
        n : number of integers to sort 

    Output: 
        arr[0...n-1] is sorted in ascending order. 
*/
void shellSort(int arr[], int n) {
    int gap = n/2; 
    int key = -1; 
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            key = arr[i];
            int j = i - gap;
            while (j >= 0 && key < arr[j]) {
                arr[j + gap] = arr[j];
                j -= gap; 
            }
            arr[j + gap] = key;
        }

        gap /= 2; 
    }
}

void print(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}