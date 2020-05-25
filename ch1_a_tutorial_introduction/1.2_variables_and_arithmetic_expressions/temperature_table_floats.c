#include <stdio.h>

/*
    NOTES: 

    To print an integer use formatting string %d
    To print a floating point number use formatting string %f 
    To specify number of places use format: %x.yf 
        x = # places before decimal (can be omitted for no constraint)
        y = # places after decimal 
*/
int main() {
    int lowerFahr = 0;
    int upperFahr = 300; 
    int stepFahr = 20;

    double curCel = 0.0;
     
    for (int currFahr = lowerFahr; currFahr <= upperFahr; currFahr += stepFahr) {
        curCel = (5.0/9.0) * (currFahr - 32);
        printf("%d\t%.1f\n", currFahr, curCel);
    }

    return 0;
}