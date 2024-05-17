#include <stdio.h>
typedef struct NODE
{
    int pos;
    int room;
} Line;
int main()
{
    Line line[200];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &line[i].pos, &line[i].room);
    }
    int x = 0;
    int begin=0;
    while (1)
    {
        scanf("%d", &x);
        if(x==-1)
        break;
        int mode=0,flag=0;
        int min=999999;
        
        for (int i = begin; i < begin+n; i++)
        {
            
            if (line[i%n].room >= x&&line[i%n].room<min)
            {
                min = line[i%n].room;
                flag = i%n;
                mode=1;
            }
        }
        if(mode==1)
        {
            line[flag].room-=x;
            if(line[flag].room==0)
            begin=(flag+1)%n;
            else
            begin=flag;
        }
        
    }
    for(int i=begin;i<(n+begin);i++)
    {
        if(line[i%n].room!=0)
        {
            printf("%d %d\n",line[i%n].pos,line[i%n].room);
        }
    }
}