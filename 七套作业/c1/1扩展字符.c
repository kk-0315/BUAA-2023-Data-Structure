/*【问题描述】
从键盘输入包含扩展符'-'的字符串，将其扩展为等价的完整字符，例如将a-d扩展为abcd，并输出扩展后的字符串。
要求：只处理[a-z]、[A-Z]、[0-9]范围内的字符扩展，即只有当扩展符前后的字符同时是小写字母、大写字母或数字，
并且扩展符后的字符大于扩展符前的字符时才进行扩展，其它情况不进行扩展，原样输出。
例如：a-R、D-e、0-b、4-B等字符串都不进行扩展。*/
#include<stdio.h>
#include<string.h>

char s[500];
int main()
{
    gets(s);
    for(int i=1;i<strlen(s);i++)
    {
        if(s[i]=='-')
        {
            if(s[i-1]>='a'&&s[i+1]<='z'&&s[i-1]<s[i+1])
            {
                for(char t=s[i-1];t<s[i+1];t++)
                printf("%c",t);
                i++;
            }
            else if(s[i-1]>='A'&&s[i+1]<='Z'&&s[i-1]<s[i+1])
            {
                for(char t=s[i-1];t<s[i+1];t++)
                printf("%c",t);
                i++;
            }
            else if(s[i-1]>='0'&&s[i+1]<='9'&&s[i-1]<s[i+1])
            {
                for(char t=s[i-1];t<s[i+1];t++)
                printf("%c",t);
                i++;
            }
            else
            printf("%c",s[i-1]);
        }
        else
        printf("%c",s[i-1]);
    }
    printf("%c",s[strlen(s)-1]);
    return 0;
}
