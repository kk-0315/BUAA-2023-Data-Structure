#include <stdio.h>
#include <string.h>
#include<stdlib.h>
typedef struct __LMailNode
{
    char name[100];
    char num[20]; // 存放单个节点的数据
    int index;
    int rank;
} MailList;
int n;

int cmp1(const void *p1, const void *p2) {
	if(strcmp(((struct __LMailNode *)p1)->name,((struct __LMailNode *)p2)->name)==0) return 0;
	else if(strcmp(((struct __LMailNode *)p1)->name,((struct __LMailNode *)p2)->name)>0) return 1;
	else return -1;
}

int main()
{
    MailList a[100];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", a[i].name);
        scanf("%s", a[i].num);
        
    }
    int count;
    for (int i = 0; i < n; i++)
    {
        count = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(a[i].name, a[j].name) == 0)
            {
                if (strcmp(a[i].num, a[j].num) == 0)
                {
                    int len1=strlen(a[j].name);
                    int len2=strlen(a[j].num);
                    for (int k = 0; k < len1; k++)
                        a[j].name[k] = 0;

                    for (int k = 0; k < len2; k++)
                        a[j].num[k] = 0;

                    
                }
                else
                {
                    count++;
                    a[j].name[strlen(a[j].name)] = '_';
                    a[j].name[strlen(a[j].name) ] = count+'0';
                }
            }
        }
    }
    
    
    qsort(a,n,sizeof(struct __LMailNode),cmp1);
	

    for (int i = 0; i < n; i++)
    {
        printf("%s %s\n",a[i].name,a[i].num) ;
    }
}