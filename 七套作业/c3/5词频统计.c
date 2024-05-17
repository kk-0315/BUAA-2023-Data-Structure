#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct NODE
{
    char cha[50];
    int count;
} Character;
int cmp1(const void *p1, const void *p2)
{
    if (strcmp(((struct NODE *)p1)->cha, ((struct NODE *)p2)->cha) == 0)
        return 0;
    else if (strcmp(((struct NODE *)p1)->cha, ((struct NODE *)p2)->cha) > 0)
        return 1;
    else
        return -1;
}
char s[50], s1[50];
char c;
int main()
{

    Character danci[100];
    for (int i = 0; i < 100; i++)
    {
        danci[i].count = 1;
        for (int j = 0; j < 50; j++)
            danci[i].cha[j] = 0;
    }

    FILE *in;
    in = fopen("article.txt", "r");
    int count1 = 0;
    

    while (1)
    {
        int q = 0;
    A:
        while ((c = fgetc(in)) != EOF)
        {
            if (c >= 'A' && c <= 'Z')
            {
                c = 'a' - 'A' + c;
            }
            if (c >= 'a' && c <= 'z')
                s[q++] = c;
            else
                break;
        }
        if (q == 0 && c != EOF)
            goto A;
        if (c == EOF)
            break;
        
        
        

        int flag = 0;
        for (int i = 0; i < count1; i++)
        {
            if (strcmp(s, danci[i].cha) == 0)
            {
                danci[i].count++;
                flag = 1;
            }
        }
        if (flag == 0)
        {

            for (int i = 0; i < q; i++)
            danci[count1].cha[i] = s[i];
            count1++;
        }

        for (int i = 0; i < 500; i++)
        {
            s[i] = 0;
            
        }
    }
    qsort(danci, count1, sizeof(struct NODE), cmp1);

    for (int i = 0; i < count1; i++)
    {

        printf("%s %d\n", danci[i].cha, danci[i].count);
    }
}