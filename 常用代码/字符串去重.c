#include<stdio.h>
#include<string.h>

void del(char *p);
void del_1(char *p);
int main(void){
    char p[100];
    scanf("%s",p);
    del_1(p);
    printf("%s\n",p);
}

//方法1：找到重复的字符后将其后面的字符全部向前移一位，删除该重复的字符
void del(char *p){
    int len=strlen(p);
    for(int i=1;i<len;i++)
        for(int j=0;j<i;j++)
            if(p[i]==p[j]){
                for(int k=i;k<len;k++)
                    p[k]=p[k+1];
                len--; //提高代码执行效率，降低时间复杂度
                i--;    //不加这一句的话，会跳着比较查找，漏掉一些字符
           }
}
    
//方法2：让每一个字符i和它后面的字符j比较，如果不一样就保存字符j
void del_1(char *p){
    int len=strlen(p);
    for(int i=0;i<len;i++){
        int k=i+1;
        for(int j=i+1;j<len;j++){
            if(p[j]!=p[i])
                p[k++]=p[j]; 
        }
        p[k]='\0';  //添加字符串结束标志
    }
}