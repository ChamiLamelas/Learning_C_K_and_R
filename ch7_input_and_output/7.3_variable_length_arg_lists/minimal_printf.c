#include <stdarg.h>
#include <stdio.h>

int minPrintf(const char *f, ...);
int printInt(int i);
int printIntHelper(int i);
int printDouble(double d);
int printString(const char *s);

int main()
{
    int k = minPrintf("a%db%fc%s\n", 123, 1.23, "123");
    printf("%d\n", k);
    return 0;
}

int minPrintf(const char *f, ...)
{
    int len = 0;
    va_list argPtr;
    // as per bottom of p. 155, va_start must get started with final named argument (which there is only 1 of here)
    va_start(argPtr, f);
    const char *curr = f;

    while (*curr != '\0')
    {
        if (*curr == '%')
        {
            curr++;
            // as per top of p. 156, va_arg takes in argument pointer and type of next reading to know
            // what to return and how much to update the pointer
            if (*curr == 'd')
            {
                len += printInt(va_arg(argPtr, int));
            }
            else if (*curr == 'f')
            {
                len += printDouble(va_arg(argPtr, double));
            }
            else if (*curr == 's')
            {
                len += printString(va_arg(argPtr, char *));
            }
            else {
                return -1;
            }
        }
        else
        {
            putchar(*curr);
            len++;
        }
        curr++;
    }
    va_end(argPtr);
    return len;
}

int printInt(int i)
{
    if (i == 0)
    {
        putchar('0');
        return 1;
    }
    else
    {
        return printIntHelper(i);
    }
}

int printIntHelper(int i)
{
    if (i == 0)
    {
        return 0;
    }
    else
    {
        int r = printIntHelper(i / 10);
        putchar((i % 10) + '0');
        return r + 1;
    }
}

int printDouble(double d)
{
    return printf("%f", d);
}

int printString(const char *s)
{
    const char *curr = s;
    while (*curr != '\0')
    {
        putchar(*curr);
        curr++;
    }
    return curr - s;
}