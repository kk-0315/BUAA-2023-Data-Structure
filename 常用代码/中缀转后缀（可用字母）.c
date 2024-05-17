#include <stdio.h>
#define maxSize 20

int getPriority(char i)
{
    switch (i)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
}

int getStringSize(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

int infixToPostfix(char infix[], char s2[])
{
    char s1[maxSize];
    int top1 = -1, top2 = -1;
    int stackMax = 0;
    int i = 0;

    while (infix[i] != '\0')
    {
        if (('a' <= infix[i] && infix[i] <= 'z') || ('0' <= infix[i] && infix[i] <= '9'))
        {
            s2[++top2] = infix[i];
            i++;
        }
        else if (infix[i] == '(')
        {
            s1[++top1] = '(';
            if (top1 > stackMax)
                stackMax = top1;
            i++;
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
        {
            if (top1 == -1 || s1[top1] == '(' || getPriority(infix[i]) > getPriority(s1[top1]))
            {
                s1[++top1] = infix[i];
                if (top1 > stackMax)
                    stackMax = top1;
                i++;
            }
            else
                s2[++top2] = s1[top1--];
        }
        else if (infix[i] == ')')
        {
            while (s1[top1] != '(')
                s2[++top2] = s1[top1--];
            top1--;
            i++;
        }
    }

    while (top1 != -1)
        s2[++top2] = s1[top1--];

    return stackMax + 1;
}

int main()
{
    int top2 = -1;
    char s2[maxSize];
    char infix[maxSize] = "a-(b+c/d)*e";
    printf("%d\n", infixToPostfix(infix, s2));
    int i = 0;
    while (s2[i] != '\0')
        printf("%c", s2[i++]);
    printf("\n");
    return 0;
}
