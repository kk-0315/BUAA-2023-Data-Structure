#include<stdio.h>
int Stack[200];
int top;
int main()
{
    int x,n;
    while(1)
    {
        scanf("%d",&x);
        if(x==-1)
        break;
        if(x==1)
        {
            scanf("%d",&n);
            Stack[top++]=n;
        }
        if(x==0)
        {
            if(top>0)
            {
                printf("%d ",Stack[top-1]);
                top--;
            }
            else
            printf("error ");
        }

    }
}