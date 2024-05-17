/*编写一个程序，将用小数表示的浮点数，转换成科学计数法的形式输出。输入的数据没有符号，
小数点前后必有数字，且全为有效数据，即小数点后的末尾数字不为0；小数点前若只有一位数字，
可以为0，否则小数点前的最高位数字不为0。

提示：以字符串形式保存相关数据。
以小数形式输入数据，然后转换成科学计数法形式输出。
*/

#include<stdio.h>
#include<string.h>
char s[500];
int flag1,me,flag,len,count;
int main()
{
    gets(s);
    len=strlen(s);
    for(int i=0;i<len;i++)
    {
        if(s[i]=='.')
        {
            flag=i;
            break;
        }
    }
    int k=0;
    while(s[k]=='0')
    {
        s[k]=0;
        me++;
        k++;
        
        if(s[k]=='.')
        k++;
        flag1=1;
        
    }

    if(s[0]!='0')
    {
        me+=flag-1;

    }

    while(s[len-1]=='0')
    {
        s[len-1]=0;
    }
    for(int j=0;j<len;j++)
    {
        if(flag1==0)
            {
                if(j==1)
                printf(".");
            }
            
        if(s[j]!='.'&&s[j]!='\0')
        {
            count++;
            if(flag1==1&&count==2)
            {
                printf(".");
            }
            printf("%c",s[j]);   
        }
        
    }
    if(flag1==1)
    {
        printf("e%d",-me);
    }
    else
    printf("e%d",me);
}
