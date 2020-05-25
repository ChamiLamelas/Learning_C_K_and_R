#include <stdio.h>

/* 
    NOTES: 

    1. Values differ whether integer division by 9 is applied after OR before multiplication by 5.
        Multiplication by 5 (as expected) being done first results in higher celsius values 
        Multiplication by 5 is done first (indicated by abscence of () around currFahr - 32 in division by 9)
    2. Mathematical expression could be written with (float)(5/9), but abscence of cast requires 
        division of currFahr - 32 by 9 or each value of currCel would be 0 (because 5/9 = 0). 
 */
int main()
{
    int lowerFahr = 0;
    int upperFahr = 300;
    int stepFahr = 20;
    int currCel = 0;

    for (int currFahr = lowerFahr; currFahr <= upperFahr; currFahr += stepFahr)
    {
        currCel = 5 * (currFahr - 32) / 9;
        printf("%d\t%d\n", currFahr, currCel);
    }

    return 0;
}