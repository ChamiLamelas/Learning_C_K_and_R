#include <stdio.h>

void foo();

/*
    Run these commands: 

    gcc -c static_test.c -o static_test.o
    gcc -c static_test2.c -o static_test2.o 
    gcc -o main static_test.o static_test2.o   
    ./main.o 

    in running main, static_test2's main() function will use foo() from static_test
    it can't do that if foo() is declared static in that class.

    the functions to be used by the main() function/file should be collected in a header which is included
    in main class AND in implementing class. See textbook diagram p.82
*/
int main()
{
    foo();

    return 0;
}