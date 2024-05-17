#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define min(a,b) ((a<b)?(a):(b))
char s[100];

int main()
{
    char c,op,ch;
    int m,n;
    scanf("%c",&c);
    scanf("%c",&op);
    if(op=='-')//右对齐，左边填充
    {
        scanf("%d:%d",&m,&n);
        while(getchar() != '\n');
        
        gets(s);
        int len=strlen(s);
        if(m>=len)//全部输出字符串
        {
            if(n>len)//多于位置填充
            {
                int num=n-len;
                for(int i=0;i<num;i++)
                printf("#");
                printf("%s",s);
            }
            else
            {
                printf("%s",s);
            }
        }
        else//输出前m个
        {
            if(n>len)//多于位置填充
            {
                int num=n-m;
                for(int i=0;i<num;i++)
                printf("#");
                for(int i=0;i<m;i++)
                printf("%c",s[i]);
            }
            else
            {
                for(int i=0;i<m;i++)
                printf("%c",s[i]);
            }
        }
    }
    else
    {
        ungetc(op, stdin);
        scanf("%d:%d",&m,&n);
        while(getchar() != '\n');
        
        gets(s);
        int len=strlen(s);
        if(m>=len)//全部输出字符串
        {
            if(n>len)//多于位置填充
            {
                int num=n-len;
                
                printf("%s",s);
                for(int i=0;i<num;i++)
                printf("#");
            }
            else
            {
                printf("%s",s);
            }
        }
        else//输出前m个
        {
            if(n>len)//多于位置填充
            {
                int num=n-m;
                
                for(int i=0;i<m;i++)
                printf("%c",s[i]);
                for(int i=0;i<num;i++)
                printf("#");
            }
            else
            {
                for(int i=0;i<m;i++)
                printf("%c",s[i]);
            }
        }
    }
}