#include <stdio.h>
#include <math.h>
#include <string.h>
#define min(a, b) ((a < b) ? (a) : (b))
#define max(a, b) ((a > b) ? (a) : (b))
#define swap(a, b) (a ^= (b ^= (a ^= b)))
int n, p;
char key[1005];
int a[1005];
char s[1005];
char s1[1005];
int mode[250];
char ans[1005];
int go(int x) // 去找下一个人
{
    x = (x + 1) % n;
    while (a[x] == 1) // 如果下一个人以及出列了，再找下一个人
        x = (x + 1) % n;
    return x;
}
int main()
{
    // 读入密钥
    gets(key);
    n=126-32+1;
    int len = strlen(key);
    // 删除密钥中重复出现的
    int t=0,flag=0;
    for (int i = 0; i < len; i++)
    {
        flag=0;
        mode[key[i]-32]=1;
        for(int j=0;j<i;j++)
        {
            if(key[j]==key[i])
            {
                flag=1;
            }
        }
        if(flag==0)
        {
            s[t++]=key[i];
        }
    }
    // 将密钥以及未出现的整理成s【】
    
    for(int i=0;i<=126-32;i++)
    {
        if(mode[i]==0)
        {
            s[t++]=i+32;
        }
    }
    // 根据规则找到每一个可见符对应从字符s1【】
    
    a[p]=1;
    int flag1;
    for(int i=0;i<94;i++)
	{
		flag1=p;
        len=s[p];
        for(int j=1;j<=len;j++)
		{
			p = (p + 1) % n;
            while (a[p] == 1) // 如果下一个人以及出列了，再找下一个人
            p = (p + 1) % n;
		}
		s1[s[flag1]-32]=s[p];
		a[p]=1;//标记已经出列
		
        
	}
    s1[s[p]-32]=s[0];
    
    // 替换
    FILE *in, *out;
    in = fopen("in.txt", "r");
    out = fopen("in_crpyt.txt", "w");
    int h=0;
    char c;
    while ((c = fgetc(in)) != EOF)
    {
        ans[h] = c;
        h++;
    }

    for(int i=0;i<h;i++)
    {
        if(ans[i]>=32&&ans[i]<=126)
        {
            ans[i]=s1[ans[i]-32];
        }
    }

    
        fputs(ans,out);
    

    fclose(in);
    fclose(out);
}