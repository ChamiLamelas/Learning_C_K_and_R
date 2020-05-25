#include <stdio.h> 

int main() {
    // frequencies[i] = count of digit i for i in [0, 9]. 
    // frequencies[10] = count of ws characters
    // frequencies[11] = count of other characters 
    int frequencies[12];

    for (int i = 0; i < 12; i++) {
        frequencies[i] = 0; 
    }

    int currChar = getchar(); 
    while (currChar != EOF) {
        // again >= can be applied here and '0' and '9' will be substituted with their ascii values
        // to perform the integer comparison 
        if (currChar >= '0' && currChar <= '9') {
            frequencies[currChar - '0']++;
        }
        else if (currChar == ' ' || currChar == '\t' || currChar == '\n') {
            frequencies[10]++;
        }
        else {
            frequencies[11]++;
        }
        currChar = getchar();
    }   

    for (int i = 0; i <= 9; i++) {
        printf("%d count:\t\t%d\n",i,frequencies[i]);
    }

    printf("whitespace count:\t%d\n", frequencies[10]);
    printf("other char count:\t%d\n", frequencies[11]);
    return 0; 
}