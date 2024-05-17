/*包含插入、删除、撤销
关键在于用栈保存已经进行的操作，方便后面进行撤销操作
*/
#include <stdio.h>
#include<string.h>
typedef struct __SqStack // 定义顺序栈，最常用
{
    int op;
    int pos;
    char s[600];
} SqStack;
int top = -1;
int main()
{
    SqStack Stack[500];
    char a[600], str[600], str1[600];
    int oper, position, pos1, pos2, delnum;
    gets(a);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %s", &oper, &position, &str);
        
        Stack[++top].op = oper;
        Stack[top].pos = position;
        int len = strlen(str);
        for (int j = 0; j < len; j++)
            Stack[top].s[j] = str[j];
    }
    int x;
    while (1)
    {
        scanf("%d", &x);
        if (x == -1)
            break;
        if (x == 1)
        {
            scanf("%d %s", &pos1, &str1);
            
            Stack[++top].op = 1;
            Stack[top].pos = pos1;
            int len1 = strlen(str1);
            for(int i=0;i<600;i++)
            Stack[top].s[i]=0;
            for (int j = 0; j < len1; j++)
                Stack[top].s[j] = str1[j];
            int q = 0;
            int LEN = strlen(a);
            for (int k = LEN-1; k >= pos1 ; k--)
            {
                a[k + len1] = a[k];
                
            }
            for(int i=pos1;i<pos1+len1;i++)
            a[i]=str1[q++];
        }
        else if (x == 2)
        {
            int p = 0;
            scanf("%d %d", &pos2, &delnum);
            
            Stack[++top].op = 2;
            Stack[top].pos = pos2;
            
            for(int i=0;i<600;i++)
            Stack[top].s[i]=0;
            for (int j = pos2; j < pos2 + delnum; j++)
            {
                Stack[top].s[p++] = a[j];
            }
            int LEN = strlen(a);
            for (int k = pos2+delnum ; k<LEN+delnum; k++)
            {
                a[k-delnum]=a[k];
                
            }
        }
        else if (x == 3)
        {
            if (top >= 0)
            {
                if (Stack[top].op == 1)
                {
                    int LEN = strlen(a);
                    for (int i = Stack[top].pos +strlen(Stack[top].s); i<LEN+strlen(Stack[top].s); i++)
                    {
                        a[i-strlen(Stack[top].s)]=a[i];
                    }
                    
                }
                else if (Stack[top].op == 2)
                {
                    int LEN = strlen(a), k = 0;
                    for (int j = LEN-1; j>=Stack[top].pos; j--)
                    {
                        a[j + strlen(Stack[top].s)] = a[j];
                        
                    }
                    for(int i=Stack[top].pos;i<Stack[top].pos+strlen(Stack[top].s);i++)
                    a[i]=Stack[top].s[k++];
                }
                top--;
            }
        }
    }
   
    for(int i=0;i<600;i++)
    {
        if(a[i]!=0)
        printf("%c",a[i]);
    }
}