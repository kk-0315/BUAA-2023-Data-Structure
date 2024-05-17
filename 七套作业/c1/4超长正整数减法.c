/*编写程序实现两个超长正整数（每个最长80位数字）的减法运算。
 
【输入形式】

从键盘读入两个整数，要考虑输入高位可能为0的情况（如00083）。
1. 第一行是超长正整数A；
2. 第二行是超长正整数B；
*/
#include <stdio.h> 
#include <math.h>   
#include <string.h> 
#include <stdlib.h>
#define min(a, b) ((a < b) ? (a) : (b))
#define max(a, b) ((a > b) ? (a) : (b))
#define swap(a, b) (a ^= (b ^= (a ^= b)))
char a[105], b[105];
int z1[105], z2[105], ans[105], ans1[105];
int n, m,count1,count2;
int compare1()
{
    if(n-count1==m-count2)
    {
        
        while(a[count1+1]-b[count2+1]!=0)
        {
            if(a[count1+1]-b[count2+1]>0)
            return 1;
            else
            return 0;
        }
    }
}
int compare()
{
    if(n-count1>m-count2||(n-count1==m-count2&&compare1()==1))
    return 0;
    else 
    return 1;
}
int main()
{
    
    int l, l1, len, len1;
    scanf("%s%s", a + 1, b + 1);
    
        int flag1=0,flag2=0;
        for (int i = 1; i <= 100; i++)
        {
            ans[i] = ans1[i] = 0;
            z1[i] = z2[i] = 0;

            if(a[i]=='0'&&flag1==0)
            count1++;

            if(b[i]=='0'&&flag2==0)
            count2++;

            if(a[i]!='0')
            flag1=1;
            if(b[i]!='0')
            flag2=1;
        }
        n = strlen(a + 1);
        m = strlen(b + 1);
        l = l1 = len = len1 = 0;
        if (compare() == 0) // a大于b
        {

            for (int i = n; i >= 1; i--)
            {
                z1[++l1] = a[i] - '0';
            }

            for (int i = m; i >= 1; i--)
            {
                z2[++len1] = b[i] - '0';
            }
        }
        else // b大于a
        {
            for (int i = m; i >= 1; i--)
            {
                z1[++len1] = b[i] - '0';
            }

            for (int i = n; i >= 1; i--)
            {
                z2[++l1] = a[i] - '0';
            }
        }

        len1 = max(len1, l1);
        for (int i = 1; i <= len1; i++)
        {
            ans1[i] = (ans1[i] + z1[i] - z2[i]);
            if (ans1[i] < 0)
            {
                ans1[i + 1]--;
                ans1[i] = ans1[i] + 10;
            }
        }
        
        while (ans1[len1] == 0 && len1 >= 1)
        {
            len1--;
        }
        if (len1 == 0)
        {
            printf("0");
        }
        if (compare() == 1&&len1!=0)
            printf("-");
        for (int i = len1; i >= 1; i--)
        {

            printf("%d", ans1[i]);
        }

        
    
    return 0;
}


