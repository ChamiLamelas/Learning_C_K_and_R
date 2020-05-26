#include <stdio.h> 

int binarySearch(const int arr[], int n, int key);

int main() {
    int arr[] = {1, 2, 4, 5}; 
    printf("%d\n", binarySearch(arr, 4, 3));
    printf("%d\n", binarySearch(arr, 4, 0));
    printf("%d\n", binarySearch(arr, 4, 6));
    return 0; 
}

int binarySearch(const int arr[], int n, int key) {
    int l = 0; 
    int r = n - 1; 
    int mid = -1; 

    while (l <= r) {
        mid = (l + r) / 2; 
        if (key < arr[mid]) {
            r = mid - 1; 
        }
        else if (key > arr[mid]){
            l = mid + 1; 
        }
        else {
            return mid;
        }
    }

    return -(l + 1);
}