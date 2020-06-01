#include "string.h"
#include <stdio.h>
#include "C:\Users\Chami\programming\c\kernigan_ritchie\ch5_pointers_and_arrays\5.4_address_arithmetic\memory_allocation.h"

int main()
{
    printf("%d\n", strlen("abc"));          // 3
    printf("%d\n", strlen(""));             // 0
    printf("%d\n", strcmp("abc", "abcd"));  // negative
    printf("%d\n", strcmp("", "abcd"));     // negative
    printf("%d\n", strcmp("abcd", "abc"));  // positive
    printf("%d\n", strcmp("abcd", "abcd")); // 0
    printf("%d\n", strcmp("", ""));         // 0

    char *s = "abc";
    char *t = alloc(4);

    strcopy(s, t);
    printf("%s\n", t); // abc

    char *name = alloc(10);
    char *lname = "Smith";
    *name = 'J';
    *(name + 1) = 'o';
    *(name + 2) = 'h';
    *(name + 3) = 'n';
    *(name + 4) = '\0';

    printf("[%s] [%s]\n", name, lname);
    strconcat(name, lname);
    printf("%s\n", name);

    printf("%d %d %d %d %d %d %d %d\n", strend("", ""), strend("ab", "ab"), strend("ab", "b"), strend("abc", "bc"), strend("ab", "a"), strend("abc", "ab"), strend("abc", ""), strend("abab", "ab")); // 1 1 1 1 0 0 1 1
    printf("%d %d %d %d\n", strindex("abc", 'a'), strindex("abc", 'b'), strindex("abc", 'c'), strindex("abc", 'd'));                                                                                  // 0 1 2 -1
    printf("%d %d %d %d %d %d\n", substr("ababcabcd", "abcd"), substr("ababcabc", "abcd"), substr("abc", "abcd"), substr("abc", ""), substr("abc", "a"), substr("abc", "abc"));                                                // 5 -1 -1 -1
    
    char *ab = alloc(3);
    *ab = 'a';
    *(ab + 1) = 'b';
    *(ab + 2) = '\0';
    char *abc = alloc(4);
    *abc = 'a';
    *(abc + 1) = 'b';
    *(abc + 2) = 'c';
    *(abc + 3) = '\0';
    char *empty = alloc(1);
    *empty = '\0';
    char *a = alloc(2);
    *a = 'a';
    *(a + 1) = '\0';
    char *abcd = alloc(5);
    *abcd = 'a';
    *(abcd + 1) = 'b';
    *(abcd + 2) = 'c';
    *(abcd + 3) = 'd';
    *(abcd + 4) = '\0';
    char *abcde = alloc(6);
     *abcde = 'a';
    *(abcde + 1) = 'b';
    *(abcde + 2) = 'c';
    *(abcde + 3) = 'd';
    *(abcde + 4) = 'e';
    *(abcde + 5) = '\0';

    reverse(ab);
    reverse(abc);
    reverse(empty);
    reverse(a);
    reverse(abcd);
    reverse(abcde);

    printf("[%s] [%s] [%s] [%s] [%s] [%s]\n", ab, abc, empty, a, abcd, abcde); // [ba] [cba] [] [a] [dcba] [edcba]

    printf("%d %d %d %d %d\n", stringToInt("10200"), stringToInt("-10200"), stringToInt("0"), stringToInt("1"), stringToInt("-1")); // 10200 -10200 0 1 -1 

    char *s1 = alloc(6);
    char *s2 = alloc(7);
    char *s3 = alloc(2);
    char *s4 = alloc(2);
    char *s5 = alloc(3);

    intToString(s1, 10200);
    intToString(s2, -10200);
    intToString(s3, 0);
    intToString(s4, 1);
    intToString(s5, -1);

    printf("%s %s %s %s %s\n", s1, s2, s3, s4, s5); // 10200 -10200 0 1 -1
    printf("%f %f %f %f %f %f %f\n", stringToDouble("1.1"), stringToDouble("-1.1"), stringToDouble("123.456"), stringToDouble("-123.456"), stringToDouble("0.0"), stringToDouble("1"), stringToDouble("-1")); // 1.1 -1.1 123.456 -123.456 0.0 1.0 -1.0 

    char *s6 = alloc(8);
    *s6 = ' ';
    *(s6 + 1) = 'a';
    *(s6 + 2) = ' ';
    *(s6 + 3) = 'b';
    *(s6 + 4) = ' ';
    *(s6 + 5) = 'c';
    *(s6 + 6) = ' ';
    *(s6 + 7) = '\0';
    char *s7 = alloc(4);
    *s7 = ' ';
    *(s7 + 1) = 'a';
    *(s7 + 2) = ' ';
    *(s7 + 3) = '\0';
    char *s8 = alloc(2);
    *s8 = ' ';
    *(s8 + 1) = '\0';
    char *s9 = alloc(1);
    *s9 = '\0';
    char *s10 = alloc(3);
    *s10 = ' ';
    *(s10 + 1) = 'a';
    *(s10 + 2) = '\0';
    char *s11 = alloc(3);
    *s11 = 'a';
    *(s11 + 1) = ' ';
    *(s11 + 2) = '\0';

    trim(s6);
    trim(s7);
    trim(s8);
    trim(s9);
    trim(s10);
    trim(s11);

    printf("[%s] [%s] [%s] [%s] [%s] [%s]\n", s6, s7, s8, s9, s10, s11); // [a b c] [a] [] [] [a] [a]

    toUpperCase(s6);
    toUpperCase(s7);
    toUpperCase(s8);

    printf("[%s] [%s] [%s]\n", s6, s7, s8);

    toLowerCase(s6);
    toLowerCase(s7);
    toLowerCase(s8);

    printf("[%s] [%s] [%s]\n", s6, s7, s8);
    
    char *lineBuf = alloc(100);
    int len = getline(lineBuf, 100);
    while (len != EOF) {
        printf("%s\n", lineBuf);
        len = getline(lineBuf, 100);
    }

    free(lineBuf);
    free(s11);
    free(s10);
    free(s9);
    free(s8);
    free(s7);
    free(s6);
    free(s5);
    free(s4);
    free(s3);
    free(s2);
    free(s1);
    free(abcde);
    free(abcd);
    free(empty);
    free(abc);
    free(ab);
    free(name);
    free(t);

    return 0;
}