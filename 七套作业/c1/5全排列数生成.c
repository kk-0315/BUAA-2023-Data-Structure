/*【问题描述】输入整数N( 1 <= N <= 10 )，生成从1~N所有整数的全排列。*/
#include<stdio.h>
//1~n的字典序排列
int a[20];//储存于此
int used[20];//0表示没用过，1表示用过
void f(int);
int x;
int main()
{
	scanf("%d",&x);
	f(1);
	return 0;
}
void f(int n)
{
	
	if(n>x)//遍历结束，输出
	{
		for(int i=1;i<=x;i++)
		printf("%d ",a[i]);
		printf("\n");
		return ;
	}
	for(int i=1;i<=x;i++)
	{
		if(used[i]==0)
		{
			used[i]=1;
			a[n]=i;
			
			f(n+1);
			
			a[n]=0;
			used[i]=0;
		}
	}
}



