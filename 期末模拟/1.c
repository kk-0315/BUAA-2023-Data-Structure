#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
struct std
{
    char index[20];
    char name[20];
    int id;//机器序号
    char time[20];
    int flag;
};
int cmp(const void *p1, const void *p2) {
	if(strcmp(((struct std *)p1)->time,((struct std *)p2)->time)==0) return 0;
	else if(strcmp(((struct std *)p1)->time,((struct std *)p2)->time)>0) return 1;
	else return -1;
}
int cmp1(const void *p1, const void *p2) {
	if(strcmp(((struct std *)p1)->index,((struct std *)p2)->index)==0) return 0;
	else if(strcmp(((struct std *)p1)->index,((struct std *)p2)->index)>0) return 1;
	else return -1;
}
struct std student[200];
struct std ans[200];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s",student[i].index);
        scanf("%s",student[i].name);
        scanf("%d",&student[i].id);
        scanf("%s",student[i].time);

    }
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    {
        if(strcmp(student[i].index,student[j].index)==0&&(student[i].id!=student[j].id))
        {
            student[i].flag=student[j].flag=1;
        }
    }

    qsort(student,n,sizeof(struct std),cmp);
    int count=0;
    
    for(int i=0;i<n;i++)
    {
        int flag1=0;
        if(student[i].flag==1)
        {
            for(int j=0;j<count;j++)
            {
                if(strcmp(student[i].index,ans[j].index)==0)
                {
                    flag1=1;
                    break;
                }
            }
            if(flag1!=1)
            {
                
                strcpy(ans[count].index,student[i].index);
                strcpy(ans[count++].name,student[i].name);
            }
        }
    }
    qsort(ans,count,sizeof(struct std),cmp1);
    for(int i=0;i<count;i++)
    {
        printf("%s %s\n",ans[i].index,ans[i].name);
    }
}