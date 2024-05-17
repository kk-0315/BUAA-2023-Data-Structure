/*1.当检测的程序括号为'{'时，若其前序尚未匹配的括号为'('时，输出该'('左括号及所在行号； 
2.当遇到一个不匹配的右括号')'或'}'时，输出该右括号及所在行号；
3.当程序处理完毕时，还存在不匹配的左括号时，输出该左括号及所在行号。
若整个程序括号匹配，则按下面所示顺序输出括号匹配情况，中间没有空格。

坑1：无需判断换行符
坑2：转义字符 即形如"()" '()'的括号不应该被处理
*/
#include <stdio.h>
int top = -1, top1 = -1;
typedef struct __SqStack // 定义顺序栈，最常用
{
    char op;
    int line;
} SqStack;
int MAX = 300;
int BackwardLen(char target, char *start)//从start往后找target，返回之间的长度
{
    int len;
    for (len = 1; *(start + len) != '\0'; len++)
    {
        if (*(start + len) == target)
        {
            return len;
        }
    }
    return 0;
}
int main()
{
    char s[MAX];
    SqStack Stack[300], StackShow[300];
    for (int i = 0; i < 300; i++)
    {
        Stack[i].op = StackShow[i].op = 0;
        Stack[i].line = StackShow[i].line = 0;
    }
    FILE *in;
    in = fopen("example.c", "r");

    int count = 0;
    int len;
    while (fgets(s, MAX, in) != NULL)
    {
        /*if(s[0]=='\n')
        continue;*///网站上copy过来中间有空行，导致多一个换行实际上并不需要考虑这个
        count++;
        for (int i = 0; s[i] != 0; i += len)
        {
            len = 1;

            if (s[i] == '/')
            {
                if (s[i + 1] == '*')
                {
                    if (len = BackwardLen('*', &s[i + 1]))
                    {
                        if (s[i + 2 + len] == '/')
                            len += 3;
                        else
                            len = 2;
                    }
                    else
                        len = 2;
                }
                else if (s[i + 1] == '/')
                    break;
            }
            //形如"()" '()'的括号不应该被处理
            else if (s[i] == '\'')
            {
                if (!(len = BackwardLen('\'', &s[i])))
                    len = 1;
            }
            else if (s[i] == '\"')
            {
                if (!(len = BackwardLen('\"', &s[i])))
                    len = 1;
            }
            else if (s[i] == '{' || s[i] == '}' || s[i] == '(' || s[i] == ')')
            {
                if (s[i] == '{')
                {
                    if (top >= 0)
                    {
                        if (Stack[top].op != '(')
                        {
                            Stack[++top].line = count;
                            Stack[top].op = s[i];

                            StackShow[++top1].op = s[i];
                        }
                        else
                        {
                            printf("without maching '(' at line %d", Stack[top].line);
                            return 0;
                        }
                    }
                    if (top == -1)//如果栈里没东西，就入比较栈，同时入show栈
                    {
                        Stack[++top].line = count;
                        Stack[top].op = s[i];

                        StackShow[++top1].op = s[i];
                    }
                }
                if (s[i] == '(')
                {
                    Stack[++top].line = count;
                    Stack[top].op = s[i];

                    StackShow[++top1].op = s[i];
                }
                else if (s[i] == '}')
                {
                    if (top == -1)
                    {
                        printf("without maching '}' at line %d", count);
                        return 0;
                    }
                    if (top >= 0)
                    {
                        if (Stack[top].op == '{')
                        {
                            top--;
                            StackShow[++top1].op = '}';
                        }
                        else
                        {
                            printf("without maching '}' at line %d", count);
                            return 0;
                        }
                    }
                }
                else if (s[i] == ')')
                {
                    if (top == -1)
                    {
                        printf("without maching ')' at line %d", count);
                        return 0;
                    }
                    if (top >= 0)
                    {
                        if (Stack[top].op == '(')
                        {
                            top--;
                            StackShow[++top1].op = ')';
                        }
                        else
                        {
                            printf("without maching ')' at line %d", count);
                            return 0;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < MAX; i++)
            s[i] = 0;
    }
    if (top != -1)
        printf("without maching '%c' at line %d", Stack[top].op, Stack[top].line);
    if (top == -1)
        for (int i = 0; StackShow[i].op != 0; i++)
        {
            printf("%c", StackShow[i].op);
        }
}