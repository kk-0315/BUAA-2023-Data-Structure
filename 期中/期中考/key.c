#include <stdio.h>
#include <string.h>
char key1[1000], key[1000],key2[1000]; // cha=英语字母
int cha[1000];
int main()
{
    gets(key1);
    int len1 = strlen(key1);
    for (int i = 0; i < len1; i++)
    {
        if(key1[i]>='A'&&key1[i]<='Z')
        key1[i]=key1[i]-'A'+'a';
        if (key1[i] >= 'a' && key1[i] <= 'z')
        {
            cha[key1[i] - 'a']++; // 表示出现过
            if (cha[key1[i] - 'a'] == 2)
            {
                cha[key1[i] - 'a'] = 1;
                key1[i] = 0;
            }
        }
        else
        {
            key1[i]=0;
        }
        
    }
    int len = 0;
    for (int i = 0; i < len1; i++)
    {
        if (key1[i] != '\0')
        {
            key2[len] = key1[i];
            len++;
        }
    }

    int h,g;
    for( g=0,h=len-1;g<len,h>=0;++g,--h)
	key[g]=key2[h];

    for (int i = 'z'; i >= 'a'; i--)
    {
        if (cha[i - 'a'] == 0)
        {
            key[len++] = i;
        }
    }
    for(int i=0;i<26;i++)
    {
        printf("%c %c\n",i+'a',key[i]);
    }
    
}