#include <stdio.h>

// Modification of exercise 1-4 (that is, conversion celsius -> fahrenheit)

int main() {
    int lowerCel = 0;
    int upperCel = 300; 
    int stepCel = 20;

    double curFahr = 0.0;

    printf("Celsius\tFahrenheit\n");  
    for (int currCel = upperCel; currCel >= lowerCel; currCel -= stepCel) {
        curFahr = (9.0/5.0) * currCel + 32;
        printf("%d\t%.1f\n", currCel, curFahr);
    }

    return 0;
}