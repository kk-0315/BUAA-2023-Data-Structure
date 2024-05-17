#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct __SLibrary
{
    char name[100];
    char author[100]; // 存放单个节点的数据
    char press[100];
    char year[100];
} Library;
char key[100];
int cmp1(const void *p1, const void *p2) {
	if(strcmp(((struct __SLibrary *)p1)->name,((struct __SLibrary *)p2)->name)==0) return 0;
	else if(strcmp(((struct __SLibrary *)p1)->name,((struct __SLibrary *)p2)->name)>0) return 1;
	else return -1;
}
int main()
{
    Library a[200];
    FILE *in, *out;
    in = fopen("books.txt", "r");
    out = fopen("ordered.txt", "w");

    int count = 0;
    while (fscanf(in, "%s %s %s %s", a[count].name, a[count].author, a[count].press, a[count].year) != EOF)
    {
        count++;
    }
    qsort(a,count,sizeof(struct __SLibrary),cmp1);

    int op;
    while (scanf("%d", &op) != EOF)
    {
        if (op == 1)
        {
            scanf("%s %s %s %s", a[count].name, a[count].author, a[count].press, a[count].year);
            count++;
            qsort(a,count,sizeof(struct __SLibrary),cmp1);
        }
        if (op == 2)
        {
            scanf("%s", key);
            
            int i, j, k, m=0;
            while (m < count)
            {
                for (i = 0; a[m].name[i] != '\0'; i++)
                {
                    for (j = i, k = 0; key[k] != '\0' && a[m].name[j] == key[k]; j++, k++);
                        
                    if (key[k] == '\0')
                    {
                        
                        printf("%-50s%-20s%-30s%-10s\n", a[m].name, a[m].author, a[m].press, a[m].year);
                    }
                }
                m++;
            }

            for(int i=0;i<100;i++)
            {
                key[i]=0;
            }
        }
        if(op==3)
        {
            scanf("%s", key);
            
            int i, j, k, m=0;
            while (m < count)
            {
                for (i = 0; a[m].name[i] != '\0'; i++)
                {
                    for (j = i, k = 0; key[k] != '\0' && a[m].name[j] == key[k]; j++, k++);
                        
                    if (key[k] == '\0')
                    {
                        for(int p=0;p<100;p++)
                        {
                            a[m].author[p]=0;
                            a[m].name[p]=0;
                            a[m].press[p]=0;
                            a[m].year[p]=0;
                        }
                    }
                }
                m++;
            }

            for(int i=0;i<100;i++)
            {
                key[i]=0;
            }
        }
        if(op==0)
        {
            for(int i=0;i<count;i++)
            {
                if(a[i].name[0]!=0)
                fprintf(out,"%-50s%-20s%-30s%-10s\n",a[i].name,a[i].author,a[i].press,a[i].year);
                
            }
            break;
        }
    }
    fclose(in);
    fclose(out);
    
}