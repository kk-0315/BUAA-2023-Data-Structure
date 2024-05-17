#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
struct step
{
    int op;
    int num;
};
struct step stack[2000];
int top=-1;
int cur_op,cur_num;
void push(int op,int num);
int main()
{
    while(scanf("%d-%d",&cur_op,&cur_num))
    {
        if(cur_op==0)
        break;
        if(top!=-1)
        {
            if(stack[top].op==5&&cur_op==5)
            {
                stack[top].num+=cur_num;
            }
            else if(stack[top].op==5&&cur_op==6)
            {
                if(cur_num>stack[top].num)
                {
                    stack[top].op=6;
                    stack[top].num=cur_num-stack[top].num;
                }
                else
                {
                    stack[top].num-=cur_num;
                }
                if(stack[top].num==0)
                    top--;
            }
            else if(stack[top].op==6&&cur_op==5)
            {
                if(cur_num>stack[top].num)
                {
                    stack[top].op=5;
                    stack[top].num=cur_num-stack[top].num;
                }
                else
                {
                    stack[top].num-=cur_num;
                }
                if(stack[top].num==0)
                    top--;
            }
            else if(stack[top].op==6&&cur_op==6)
            {
                stack[top].num+=cur_num;
            }
            else if(stack[top].op==7&&cur_op==7)
            {
                stack[top].num+=cur_num;
            }
            else if(stack[top].op==8&&cur_op==8)
            {
                stack[top].num+=cur_num;
            }
            else if(stack[top].op==7&&cur_op==8)
            {
                if(cur_num>stack[top].num)
                {
                    stack[top].op=8;
                    stack[top].num=cur_num-stack[top].num;
                }
                else
                {
                    stack[top].num-=cur_num;
                }
                if(stack[top].num==0)
                    top--;
            }
            else if(stack[top].op==8&&cur_op==7)
            {
                if(cur_num>stack[top].num)
                {
                    stack[top].op=7;
                    stack[top].num=cur_num-stack[top].num;
                }
                else
                {
                    stack[top].num-=cur_num;
                }
                if(stack[top].num==0)
                    top--;
            }
            else
            {
                push(cur_op,cur_num);
            }


        }
        else
        push(cur_op,cur_num);
    }
    for(int i=top;i>=0;i--)
    {
        if(stack[i].op==6)
        {
            printf("%d-%d ",5,stack[i].num);
        }
        if(stack[i].op==5)
        {
            printf("%d-%d ",6,stack[i].num);
        }
        if(stack[i].op==7)
        {
            printf("%d-%d ",8,stack[i].num);
        }
        if(stack[i].op==8)
        {
            printf("%d-%d ",7,stack[i].num);
        }
    }
}
void push(int op,int num)
{
    stack[++top].num=num;
    stack[top].op=op;
}
