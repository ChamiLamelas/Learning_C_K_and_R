#include <stdio.h>
#include <ctype.h>

/*
    TODO: 

    Exercises 4-5, 4-6 would require more extensive rewriting. 

    NOTES: 

    This implementation follows the instruction of exercise 4-10 which doesn't use get, unget from
    the buffer as a line is read entirely. 

    Furthermore, it handles negatives as required in exercise 4-3 (% could be added in evaluate())

    atoi in stdlib.h not ctype.h

    scope of an external variable: declaration point to end of file 
        declaring stack, size, and top after main(), getline(), and evaluate hides those variables
        from them and opens them only to push() and pop(). 
            --> motivation for separate files (headers)

    something not covered in text: 
        external array size must be set with DEFINE not with CONST INT 
        https://stackoverflow.com/questions/18848537/can-a-const-variable-be-used-to-declare-the-size-of-an-array-in-c
        https://bytes.com/topic/c/answers/222781-specifying-global-array-size-const-int
*/

int getline(char line[], int MAX_LENGTH);
void evaluate(const char line[]);
double stringToDouble(const char s[]);
void push(double element);
double pop(void);
int size(void);

int main()
{
    printf("Type expression to evaluate or EOF to exit: \n\n");

    const int MAX_LINE_LENGTH = 1000;
    char line[MAX_LINE_LENGTH];

    int len = getline(line, MAX_LINE_LENGTH);
    while (len != EOF)
    {
        evaluate(line);
        len = getline(line, MAX_LINE_LENGTH);
    }

    return 0;
}

// see ch1_a_tutorial_introduction/1.9_character_arrays/exercise1-16.c
int getline(char line[], int MAX_LENGTH)
{
    int currChar = getchar();

    if (currChar == EOF)
    {
        return EOF;
    }
    else if (currChar == '\n')
    {
        line[0] = '\0';
        return 0;
    }

    int i = 0;
    while (currChar != EOF && currChar != '\n')
    {
        if (i < MAX_LENGTH - 1)
        {
            line[i] = currChar;
        }
        i++;
        currChar = getchar();
    }

    if (i < MAX_LENGTH - 1)
    {
        line[i] = '\0';
    }
    else
    {
        line[MAX_LENGTH - 1] = '\0';
    }

    return i;
}

/*
    Evaluates a line of polish calculator input. It is assumed that the input is valid. That is, 
        1.  Inputs are only numbers and operators in appropriate places. 
        2.  There is no division by 0. 
        3.  Numbers are groups of digits until the next whitespace 
        4.  Input integers are less than 20 characters

    Parameters: 
        line : a line of polish calculator input 

    Output: 
        Prints result of evaluating line of polish calculator input or 
        an error message if any of 1-4 are violated above.
*/
void evaluate(const char line[])
{
    const int MAX_NUM_LENGTH = 20;
    char buf[MAX_NUM_LENGTH];
    int i = 0;

    while (line[i] != '\0')
    {
        while (line[i] != '\0' && isspace(line[i]))
        {
            i++;
        }

        if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/')
        {
            if (size() < 2)
            {
                printf("Not enough operands (%d) to apply operator %c at index %d.\n", size(), line[i], i);
                return;
            }
            double operand2 = pop();
            double operand1 = pop();
            double result;

            if (line[i] == '+')
            {
                result = operand1 + operand2;
            }
            else if (line[i] == '-')
            {
                result = operand1 - operand2;
            }
            else if (line[i] == '*')
            {
                result = operand1 * operand2;
            }
            else
            {
                if (operand2 == 0)
                {
                    printf("Division by 0. Evaluation terminated.\n");
                    return;
                }
                result = operand1 / operand2;
            }

            push(result);
            i++;
        }
        else if (isdigit(line[i]))
        {
            int j = 0;
            while (line[i] != '\0' && isdigit(line[i]))
            {
                buf[j] = line[i];
                j++;
                i++;
            }
            if (line[i] == '.')
            {
                buf[j] = '.';
                while (line[i] != '\0' && isdigit(line[i]))
                {
                    if (j == MAX_NUM_LENGTH)
                    {
                        printf("Encountered number that spanned at least %d characters.", MAX_NUM_LENGTH);
                        return;
                    }
                    buf[j] = line[i];
                    j++;
                    i++;
                }
            }
            buf[j] = '\0';

            double num = stringToDouble(buf);

            // printf("%s %f\n", buf, num);

            push(num);
        }
        else if (line[i] != '\0')
        {
            printf("Invalid character %c at index %d.\n", line[i], i);
            return;
        }

        // else line[i] = '\0', do nothing (loop will terminate)
    }

    if (size() > 1) {
        printf("Insufficient number of operators in calculator input. Number of operands remaining: %d.\n", size());
        return;
    }
    printf("%f\n", pop());
}

/*
    Converts a string to a double (floating point) number. To get a valid result, the input
    string should only be a floating point number (positive or negative). 

    Parameters: 
        s : a string array (const) 

    Output: 
        A floating point number (Double) of the data in the input string. 
        0.0 if the input string is not a floating point number. 
*/
double stringToDouble(const char s[])
{
    double num = 0;
    int dig;
    int i = 0;
    int sign = 1;
    if (s[0] == '-')
    {
        sign = -1;
        i++;
    }
    while (s[i] != '\0' && s[i] != '.')
    {
        if (!isdigit(s[i])) {
            return 0.0;
        }
        dig = s[i] - '0';
        num = num * 10 + dig;
        i++;
    }

    if (s[i] == '.')
    {
        i++;
        double pow = 10.0;
        while (s[i] != '\0')
        {
            if (!isdigit(s[i])) {
                return 0.0;
            }
            dig = s[i] - '0';
            num += dig / pow;
            pow *= 10;
            i++;
        }
    }

    return num * sign;
}

// external variables used to maintain stack info
#define STACK_SIZE 1000
double stack[STACK_SIZE];
int top = 0;

/*
    Pushes a double element onto the top of the double stack. 

    Parameters: 
        element : a double element to add to the stack

    Output: 
        element is added to the top of the stack as long as there is space on the stack. 
*/
void push(double element)
{
    if (top < STACK_SIZE)
    {
        stack[top] = element;
        top++;
    }
}

/*
    Pops the top element from the double stack and returns it. 

    Parameters: 
        None 
    
    Output: 
        The former top element of the stack that has since been removed. 
        0.0 if there was no top to pop.
*/
double pop(void)
{
    // error will be 0
    if (top == 0)
    {
        return 0.0;
    }

    double res = stack[top - 1];
    top--;
    return res;
}

/*
    Returns the size of the stack. 
*/
int size(void)
{
    return top;
}