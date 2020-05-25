#include <stdio.h> 

// declare function before use
int power(int base, int exp);

int main() {
    int fiveTo0 = power(5, 0);
    int threeSquared = power(3, 2);
    int fourTo1 = power(4, 1);
    int neg2To3 = power(-2, 3);
    int neg2To2 = power(-2, 2);

    printf("%d\n%d\n%d\n%d\n%d\n", fiveTo0, threeSquared, fourTo1, neg2To3, neg2To2);

    return 0; 
}

int power(int base, int exp) {
    int res = 1; 

    for (int i = 0; i < exp; i++) {
        res *= base; 
    }

    return res;
}