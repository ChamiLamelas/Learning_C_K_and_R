#include <stdio.h>

int main() {
    int lowerCel = 0;
    int upperCel = 300; 
    int stepCel = 20;

    double curFahr = 0.0;

    printf("Celsius\tFahrenheit\n"); 
    for (int currCel = lowerCel; currCel <= upperCel; currCel += stepCel) {
        curFahr = (9.0/5.0) * currCel + 32;
        printf("%d\t%.1f\n", currCel, curFahr);
    }

    return 0;
}