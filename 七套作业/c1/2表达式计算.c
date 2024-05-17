/*从标准输入中读入一个整数算术运算表达式，如5 - 1 * 2 * 3 + 12 / 2 / 2  = 。计算表达式结果，并输出。

要求：
1、表达式运算符只有+、-、*、/，表达式末尾的’=’字符表示表达式输入结束，表达式中可能会出现空格；
2、表达式中不含圆括号，不会出现错误的表达式；
3、出现除号/时，以整数相除进行运算，结果仍为整数，例如：5/3结果应为1。*/
#include<stdio.h>
long long num[500];

int main()
{
    long long sum=0,a,x,i=0;
    char op;
    scanf("%lld",&a);
 
		while(1){
		scanf(" %c",&op);
		if(op=='=')
		break;
	    if(op=='*')
		{
			scanf("%lld",&x);
			a*=x;
		}
		if(op=='/')
		{
			scanf("%lld",&x);
			a/=x;
		}
		if(op=='+')
		{
			num[i]=a;
			i++;
			scanf("%lld",&a);
		}
		if(op=='-')
		{
			num[i]=a;
			i++;
			scanf("%lld",&a);
			a=-a;

		}
		}
	for(int i=0;i<500;i++)
	{
		sum+=num[i];
		
	}

	
	printf("%lld",sum+a);
	return 0;
}
