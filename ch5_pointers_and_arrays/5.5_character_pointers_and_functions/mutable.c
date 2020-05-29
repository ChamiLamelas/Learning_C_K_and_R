#include <stdio.h>

int main()
{
    char amessage[] = "array";
    char *pmessage = "pointer";

    printf("%s\n", amessage);
    printf("%s\n", pmessage);

    amessage[0] = 'A';
    *pmessage = 'P'; // this causes a crash (can't modify a string constant)

    printf("%s\n", amessage);
    printf("%s\n", pmessage);

    return 0;
}