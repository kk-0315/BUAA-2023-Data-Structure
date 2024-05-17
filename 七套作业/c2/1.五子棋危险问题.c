#include<stdio.h>
int s[35][35];
int flag,x,y,count;
int main()
{
    for(int i=0;i<19;i++)
    for(int j=0;j<19;j++)
    scanf("%d",&s[i][j]);

    for(int i=19;i<35;i++)
    for(int j=19;j<35;j++)
    s[i][j]=-1;
    //横向
    for(int i=0;i<19;i++)
    for(int j=0;j<19;j++)
    {
        //1 win
        if(s[i][j]==0&&s[i][j+1]==1&&s[i][j+2]==1&&s[i][j+3]==1&&s[i][j+4]==1&&s[i][j+5]==2)
        {
            flag=1;
            x=i;
            y=j+1;
            break;
        }

        if(s[i][j]==2&&s[i][j+1]==1&&s[i][j+2]==1&&s[i][j+3]==1&&s[i][j+4]==1&&s[i][j+5]==0)
        {
            flag=1;
            x=i;
            y=j+1;
            break;
        }

        //2 win
        if(s[i][j]==0&&s[i][j+1]==2&&s[i][j+2]==2&&s[i][j+3]==2&&s[i][j+4]==2&&s[i][j+5]==1)
        {
            flag=2;
            x=i;
            y=j+1;
            break;
        }
        if(s[i][j]==1&&s[i][j+1]==2&&s[i][j+2]==2&&s[i][j+3]==2&&s[i][j+4]==2&&s[i][j+5]==0)
        {
            flag=2;
            x=i;
            y=j+1;
            break;
        }
    }

    //竖向
    for(int i=0;i<19;i++)
    for(int j=0;j<19;j++)
    {
        //1 win
        if(s[i][j]==0&&s[i+1][j]==1&&s[i+2][j]==1&&s[i+3][j]==1&&s[i+4][j]==1&&s[i+5][j]==2)
        {
            flag=1;
            x=i+1;
            y=j;
            break;
        }

        if(s[i][j]==2&&s[i+1][j]==1&&s[i+2][j]==1&&s[i+3][j]==1&&s[i+4][j]==1&&s[i+5][j]==0)
        {
            flag=1;
            x=i+1;
            y=j;
            break;
        }

        //2 win
        if(s[i][j]==0&&s[i+1][j]==2&&s[i+2][j]==2&&s[i+3][j]==2&&s[i+4][j]==2&&s[i+5][j]==1)
        {
            flag=2;
            x=i+1;
            y=j;
            break;
        }
        if(s[i][j]==1&&s[i+1][j]==2&&s[i+2][j]==2&&s[i+3][j]==2&&s[i+4][j]==2&&s[i+5][j]==0)
        {
            flag=2;
            x=i+1;
            y=j;
            break;
        }
    }
    //左斜
    for(int i=0;i<19;i++)
    for(int j=5;j<19;j++)
    
    {
        //1 win
        if(s[i][j]==0&&s[i+1][j-1]==1&&s[i+2][j-2]==1&&s[i+3][j-3]==1&&s[i+4][j-4]==1&&s[i+5][j-5]==2)
        {
            flag=1;
            x=i+1;
            y=j-1;
            break;
        }

        if(s[i][j]==2&&s[i+1][j-1]==1&&s[i+2][j-2]==1&&s[i+3][j-3]==1&&s[i+4][j-4]==1&&s[i+5][j-5]==0)
        {
            flag=1;
            x=i+1;
            y=j-1;
            break;
        }

        //2 win
        if(s[i][j]==1&&s[i+1][j-1]==2&&s[i+2][j-2]==2&&s[i+3][j-3]==2&&s[i+4][j-4]==2&&s[i+5][j-5]==0)
        {
            flag=2;
            x=i+1;
            y=j-1;
            break;
        }
        if(s[i][j]==0&&s[i+1][j-1]==2&&s[i+2][j-2]==2&&s[i+3][j-3]==2&&s[i+4][j-4]==2&&s[i+5][j-5]==1)
        {
            flag=2;
            x=i+1;
            y=j-1;
            break;
        }
    }
    //右斜
    for(int i=0;i<19;i++)
    for(int j=0;j<19;j++)
    
    {
        //1 win
        if(s[i][j]==0&&s[i+1][j+1]==1&&s[i+2][j+2]==1&&s[i+3][j+3]==1&&s[i+4][j+4]==1&&s[i+5][j+5]==2)
        {
            flag=1;
            x=i+1;
            y=j+1;
            break;
        }

        if(s[i][j]==2&&s[i+1][j+1]==1&&s[i+2][j+2]==1&&s[i+3][j+3]==1&&s[i+4][j+4]==1&&s[i+5][j+5]==0)
        {
            flag=1;
            x=i+1;
            y=j+1;
            break;
        }

        //2 win
        if(s[i][j]==1&&s[i+1][j+1]==2&&s[i+2][j+2]==2&&s[i+3][j+3]==2&&s[i+4][j+4]==2&&s[i+5][j+5]==0)
        {
            flag=2;
            x=i+1;
            y=j+1;
            break;
        }
        if(s[i][j]==0&&s[i+1][j+1]==2&&s[i+2][j+2]==2&&s[i+3][j+3]==2&&s[i+4][j+4]==2&&s[i+5][j+5]==1)
        {
            flag=2;
            x=i+1;
            y=j+1;
            break;
        }
    }
    if(flag)
    {
        printf("%d:%d,%d\n",flag,x+1,y+1);
    }
    else
    printf("No\n");


}