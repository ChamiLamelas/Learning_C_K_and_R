#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *f = NULL;
    for (int i = 1; i < argc; i++) {
        f = fopen(argv[i], "r");
        if (f == NULL) {
            fprintf(stderr, "Can't open %s.", argv[i]);
            exit(1);
            return 1;
        }
        else {
            int chr = getc(f);
            while (chr != EOF) {
                putchar(chr);
                chr = getc(f);
            }
            fclose(f);
        }
    }
    if (ferror(stdout)) {
        fprintf(stderr, "Could not write to stdout.");
        exit(2);
        return 2;
    }
    exit(0);
    return 0;
}