#include "string.h"
#include <stddef.h> // needed for size_t
#include <stdio.h>
#include <ctype.h>

// size_t is the library data type for sizeof() operator (in case string's length is greater than int capacity)
size_t strlen(const char *s)
{
    const char *curr = s;
    while (*curr != '\0')
    {
        curr++;
    }
    return curr - s;
}

void strcopy(const char *src, char *dest)
{
    *dest = *src;
    while (*dest != '\0')
    {
        src++;
        dest++;
        *dest = *src;
    }
}

int strcmp(const char *s, const char *t)
{
    while (*s == *t && *s != '\0' && *t != '\0')
    {
        s++;
        t++;
    }
    return *s - *t;
}

void strconcat(char *s, const char *t)
{
    while (*s != '\0')
    {
        s++;
    }

    *s = *t;
    while (*s != '\0')
    {
        s++;
        t++;
        *s = *t;
    }
}

int strend(const char *s, const char *t)
{
    int lenS = strlen(s);
    int lenT = strlen(t);

    if (lenT > lenS)
    {
        return 0;
    }

    s += lenS - lenT;

    while (*s != '\0')
    {
        if (*s != *t)
        {
            return 0;
        }
        s++;
        t++;
    }

    return 1;
}

int strindex(const char *s, char c)
{
    const char *curr = s;
    while (*curr != '\0')
    {
        if (*curr == c)
        {
            return curr - s;
        }
        curr++;
    }
    return -1;
}

int substr(const char *s, const char *t)
{
    const char *itrS = s;
    const char *currS = NULL;
    const char *currT = NULL;

    while (*itrS != '\0')
    {
        if (*itrS == *t)
        {
            currS = itrS;
            currT = t;
            while (*currS != '\0' && *currT != '\0' && *currS == *currT)
            {
                currS++;
                currT++;
            }
            if (*currT == '\0')
            {
                return itrS - s;
            }
        }
        itrS++;
    }

    return -1;
}

void reverse(char *s)
{
    if (*s == '\0')
    {
        return;
    }
    char *t = s;
    while (*t != '\0')
    {
        t++;
    }
    t--;
    char tmp = '\0';
    while (s < t)
    {
        tmp = *s;
        *s = *t;
        *t = tmp;
        s++;
        t--;
    }
}

int stringToInt(const char *s)
{
    int sign = 1;
    if (*s == '-')
    {
        sign = -1;
        s++;
    }

    int res = 0;
    while (*s != '\0')
    {
        if (!isdigit(*s))
        {
            return 0;
        }
        res = res * 10 + (*s - '0');
        s++;
    }

    return res * sign;
}

void intToString(char *s, int n)
{
    if (n == 0)
    {
        *s = '0';
        *(s + 1) = '\0';
        return;
    }

    if (n < 0)
    {
        *s = '-';
        s++;
        n *= -1;
    }

    int m = n;
    int count = 0;
    while (m > 0)
    {
        count++;
        m /= 10;
    }

    s += count;
    *s = '\0';
    while (n > 0)
    {
        s--;
        *s = (n % 10) + '0';
        n /= 10;
    }
}

double stringToDouble(const char *s)
{
    int sign = 1;
    if (*s == '-')
    {
        sign = -1;
        s++;
    }

    double res = 0.0;

    while (isdigit(*s))
    {
        res = res * 10 + (*s - '0');
        s++;
    }

    if (*s == '.')
    {
        double pow = 10.0;
        s++;
        while (*s != '\0')
        {
            if (!isdigit(*s))
            {
                return 0.0;
            }
            res += (*s - '0') / pow;
            pow *= 10.0;
            s++;
        }
    }
    else if (*s != '\0')
    {
        return 0.0;
    }

    return res * sign;
}

size_t getline(char *s, int MAX_LEN)
{
    int currChar = getchar();
    if (currChar == EOF)
    {
        return EOF;
    }

    int len = 0;
    while (currChar != '\n' && currChar != EOF)
    {
        if (len < MAX_LEN - 1)
        {
            *s = currChar;
            s++;
        }
        len++;
        currChar = getchar();
    }

    *s = '\0';
    return len;
}

void trim(char *s)
{
    char *t = s;
    while (isspace(*s))
    {
        s++;
    }

    if (*s == '\0')
    {
        *t = '\0';
        return;
    }

    char *lastNonWS = t;
    while (*s != '\0')
    {
        if (!isspace(*s))
        {
            lastNonWS = t;
        }
        *t = *s;
        t++;
        s++;
    }

    *(lastNonWS + 1) = '\0';
}

void toLowerCase(char *s)
{
    while (*s != '\0')
    {
        if (*s >= 'A' && *s <= 'Z')
        {
            *s = (*s - 'A') + 'a';
        }
        s++;
    }
}

void toUpperCase(char *s)
{
    while (*s != '\0')
    {
        if (*s >= 'a' && *s <= 'z')
        {
            *s = (*s - 'a') + 'A';
        }
        s++;
    }
}

int toLower(int c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (c - 'A') + 'a';
    }
    else
    {
        return c;
    }
}

int toUpper(int c)
{
    if (c >= 'a' && c <= 'z')
    {
        return (c - 'a') + 'A';
    }
    else
    {
        return c;
    }
}