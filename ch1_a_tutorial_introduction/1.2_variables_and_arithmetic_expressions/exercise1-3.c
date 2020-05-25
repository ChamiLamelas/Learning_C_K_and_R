#include <stdio.h>

int main() {
    int lowerFahr = 0;
    int upperFahr = 300; 
    int stepFahr = 20;

    double curCel = 0.0;
     
    printf("Fahrenheit\tCelsius\n");
    for (int currFahr = lowerFahr; currFahr <= upperFahr; currFahr += stepFahr) {
        curCel = (5.0/9.0) * (currFahr - 32);
        printf("%d\t\t%.1f\n", currFahr, curCel);
    }

    return 0;
}