#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define NHASH 3001

#define MULT 37
char word[20], buffer[20];
char dic[3500][20];
unsigned int hash(char *str);

typedef struct HASH
{
    char s[20];
    int f;
    struct HASH *next;
} Hs, *hashtable;
hashtable hash_table[3500];
int count, num;
struct _INDEX
{
    char alpha;
    int start;
    int number;
} index_table[30];
int main()
{
    FILE *dictionary;
    dictionary = fopen("dictionary3000.txt", "r");

    while (fscanf(dictionary, "%s", buffer) != EOF)
    {
        strcpy(dic[num++], buffer);
    }
    int op;
    scanf("%s %d", word, &op);
    if (op == 1)
    {
        int flag1 = 0;
        count = 0;
        for (int i = 0; i < num; i++)
        {
            count++;
            if (strcmp(word, dic[i]) == 0)
            {
                flag1 = 1;
                printf("1 %d\n", count);
            }
            else if (strcmp(word, dic[i]) < 0)
            {
                break;
            }
        }
        if (flag1 == 0)
        {
            printf("0 %d\n", count);
        }
    }
    else if (op == 2)
    {
        count = 0;
        int left = 0, right = num - 1;
        int mid;
        int flag = 0;
        while (left <= right)
        {
            count++;
            mid = (left + right) / 2;
            if (strcmp(dic[mid], word) == 0)
            {
                flag = 1;
                printf("1 %d\n", count);
                break;
            }
            else if (strcmp(dic[mid], word) > 0)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        if (flag == 0)
            printf("0 %d\n", count);
    }
    else if (op == 3)
    {
        count = 0;
        for (int i = 0; i < num; i++)
        {
            index_table[(int)(dic[i][0] - 'a')].alpha = dic[i][0];
            if (index_table[(int)(dic[i][0] - 'a')].number == 0)
                index_table[(int)(dic[i][0] - 'a')].start = i;
            index_table[(int)(dic[i][0] - 'a')].number++;
        }
        int left = index_table[(int)(word[0] - 'a')].start, right = index_table[(int)(word[0] - 'a')].start + index_table[(int)(word[0] - 'a')].number - 1;
        int mid;
        int flag = 0;
        while (left <= right)
        {
            count++;
            mid = (left + right) / 2;
            if (strcmp(dic[mid], word) == 0)
            {
                flag = 1;
                printf("1 %d\n", count);
                break;
            }
            else if (strcmp(dic[mid], word) > 0)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        if (flag == 0)
            printf("0 %d\n", count);
    }
    else
    {
        count = 0;
        hashtable r;
        for (int i = 0; i < 3500; i++)
        {
            hash_table[i] = (hashtable)malloc(sizeof(Hs));
            hash_table[i]->f = 0;
            hash_table[i]->next = NULL;
        }
        for (int i = 0; i < num; i++)
        {
            unsigned int pos = hash(dic[i]);
            if (hash_table[pos]->f == 0)
            {
                hash_table[pos]->f = 1;
                strcpy(hash_table[pos]->s, dic[i]);
            }
            else
            {
                hashtable p, r,tail;
                r = (hashtable)malloc(sizeof(Hs));
                p = hash_table[pos];
                while (p->next != NULL && strcmp(p->s, dic[i]) < 0)
                {
                    tail=p;
                    p = p->next;
                }
                if (p->next == NULL)
                {
                    r->f = 1;
                    r->next = NULL;
                    strcpy(r->s, dic[i]);
                    p->next = r;
                    
                }
                else if(strcmp(p->s, dic[i]) > 0)
                {
                     r->f = 1;
                    r->next = NULL;
                    strcpy(r->s, dic[i]);

                    r->next=p;
                    tail->next=r;
                    
                }
            }
        }

        unsigned int no = hash(word);
        hashtable q;
        q = hash_table[no];
        while (q != NULL && strcmp(q->s, word) <= 0)
        {
            count++;
            if (strcmp(q->s, word) == 0)
            {
                printf("1 %d\n", count);
                break;
            }

            q = q->next;
        }
        if (q == NULL)
        {
            
            printf("0 %d\n", count);
        }
        else if (strcmp(q->s, word) > 0)
        {
            count++;
            printf("0 %d\n", count);
        }
    }
}
unsigned int hash(char *str)

{

    unsigned int h = 0;

    char *p;

    for (p = str; *p != '\0'; p++)

        h = MULT * h + *p;

    return h % NHASH;
}