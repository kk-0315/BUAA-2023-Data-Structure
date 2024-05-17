#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
struct info
{
    char phone[20];
    char id;
    char in_time[20];
    char out_time[20];
};
struct info g[1000],ans[1000];
char target[20];
char in[20],out[20];
char target_id;
int count;
int cmp(const void *p1, const void *p2) {
	if(strcmp(((struct info *)p1)->phone,((struct info *)p2)->phone)==0) 
    {
        if((((struct info *)p1)->id)>(((struct info *)p2)->id))
        return 1;
        else
        return -1;
    }
	else if(strcmp(((struct info *)p1)->phone,((struct info *)p2)->phone)>0) return -1;
	else return 1;
}
int main()
{
    int n;
    scanf("%d",&n);
    
    for(int i=0;i<n;i++)
    {
        scanf("%s %c %s %s",g[i].phone,&g[i].id,g[i].in_time,g[i].out_time);
    }

    scanf("%s",target);

    for(int i=0;i<n;i++)
    {
        if(strcmp(target,g[i].phone)==0)
        {
            strcpy(in,g[i].in_time);
            strcpy(out,g[i].out_time);
            target_id=g[i].id;
            for(int j=0;j<n;j++)
            {
                if(strcmp(g[j].phone,target)!=0)
                {
                    if(((strcmp(g[j].in_time,out)<=0&&strcmp(g[j].out_time,in)>=0)||(strcmp(g[j].out_time,in)>=0&&strcmp(g[j].in_time,out)<=0))&&(g[j].id==target_id))
                    {
                        strcpy(ans[count].phone,g[j].phone);
                        ans[count++].id=g[j].id;
                    }
                }
            }
        }
    }
    qsort(ans,count,sizeof(struct info),cmp);
    for(int i=0;i<count;i++)
    {
        if((strcmp(ans[i].phone,ans[i+1].phone)==0)&&(ans[i].id==ans[i+1].id))
        {
            continue;
        }
        printf("%s %c\n",ans[i].phone,ans[i].id);
    }
}