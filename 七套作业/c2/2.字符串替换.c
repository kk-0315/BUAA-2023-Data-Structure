#include <stdio.h>
#include <string.h>
#include<ctype.h>
char s1[50], s2[50], s[10000]; 
int flag[50];
int main()
{
    scanf("%s", s1);
    scanf("%s", s2);
    FILE *in, *out;
    in = fopen("filein.txt", "r");
    out = fopen("fileout.txt", "w");
    int t = 0, m = 0;
    char c;
    while ((c = fgetc(in)) != EOF)
    {
        s[t] = c;
        t++;
    }
    int len1=strlen(s1),len2=strlen(s2),len=strlen(s);
    int i,j,k;//识别的主要模块
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; s1[k] != '\0' && tolower(s[j]) == tolower(s1[k]); j++, k++);     
        if (s1[k] == '\0')
        {
            flag[m] = i;
            m++;
            
        }
    }
    if (len1< len2)
    {
        int n=0;
        while (n < m)
        {
            for (int i = len - 1+(len2-len1)*n; i >= flag[n]+(len2-len1)*n; i--)
            {
                s[i + len2] = s[i + len1];
                
            }
            for (int i = flag[n]+(len2-len1)*n,k1=0; i <= flag[n] + len2 - 1+(len2-len1)*n; i++,k1++)
            {
                s[i] = s2[k1];
            }
            n++;
        }
    }
    else{
        int n=0;
        while(n<m)
        {
            for (int i = flag[n]-(len1-len2)*n; i <= len - 1-(len1-len2)*n; i++)
            {
                s[i + len2] = s[i + len1];
                
            }
            for (int i = flag[n]-(len1-len2)*n,k2=0; i <= flag[n] + len2 - 1-(len1-len2)*n; i++,k2++)
            {
                s[i] = s2[k2];
            }
            n++;
        }
    }
    fputs(s,out);
    fclose(in);
    fclose(out);
    return 0;
}