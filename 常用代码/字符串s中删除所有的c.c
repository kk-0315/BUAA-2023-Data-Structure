//下面程序的功能是将字符串s中所有的字符“c”删除。请选择填空。
#include <stdio.h>
int main()
{
    char s[80];
    int i, j;
    gets(s);
    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != 'c') s[j++]=s[i];
    s[j] = '\0';
    puts(s);

    return 0;
}