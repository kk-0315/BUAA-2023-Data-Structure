#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXVER  512
#define INFINITY1   32767
struct edge {
	int id;
	int wei;
};
struct edge graph[MAXVER][MAXVER];//邻接矩阵
int edges[MAXVER]={0};//生成树数组
int ans[MAXVER];
int count;
int vertax_size,edge_size;
void Prim(struct edge  weights[][ MAXVER], int n, int src, int edges[ ]);
void bubbleSort(int k[], int n);
int main()
{
    int eno,v1,v2,w;
    scanf("%d%d",&vertax_size,&edge_size);
    for(int i=0;i<vertax_size;i++)
    for(int j=0;j<vertax_size;j++)
    {
        graph[i][j].wei=INFINITY1;
        graph[i][j].id=0;
    }
    for(int i=0;i<edge_size;i++)
    {
        scanf("%d%d%d%d",&eno,&v1,&v2,&w);
        graph[v1][v2].id=eno;
        graph[v1][v2].wei=w;
        graph[v2][v1].id=eno;
        graph[v2][v1].wei=w;
    }

    Prim(graph,vertax_size,0,edges);

    for(int i=1;i<vertax_size;i++)
    {
        ans[i]=graph[i][edges[i]].id;
        count+=graph[i][edges[i]].wei;
    }
    bubbleSort(ans,vertax_size);
    printf("%d\n",count);
    for(int i=1;i<vertax_size;i++)
    {
        printf("%d ",ans[i]);
    }
}
void bubbleSort(int k[], int n)
{
    int i, j, flag = 1;
    int temp;
    for (i = n - 1; i > 0 && flag == 1; i--)
    {
        flag = 0; /* 每趟排序前标志flag置0 */
        for (j = 0; j < i; j++)
        {
            
            if (k[j] > k[j + 1])
            {
                temp = k[j];
                k[j] = k[j + 1];
                k[j + 1] = temp; /* 交换两个元素的位置 */
                flag = 1;        /* 标志flag置1 */
            }
        }
        if (flag == 0)
            break;
    }
}
void Prim(struct edge  weights[][ MAXVER], int n, int src, int edges[ ])
{ //weights为权重数组、n为顶点个数、src为最小树的第一个顶点、edge为最小生成树边
    int minweight [MAXVER], min;
    int i, j, k;
    for(i=0; i<n; i++){  //初始化相关数组
        minweight[i] = weights[src][i].wei;  //将src顶点与之有边的权值存入数组
        edges[i]  = src;  //初始时所有顶点的前序顶点设为src，(src,i）
     }
    minweight[src]  = 0;   //将第一个顶点src顶点加入生成树
    for(i=1; i< n; i++){
        min = INFINITY1;
        for(j=0, k=0;  j<n; j++)
            if(minweight[j] !=0 && minweight[j] < min) {  //在数组中找最小值，其下标为k
                min = minweight[j];  k = j;
            }
        minweight[k] = 0;  //找到最小树的一个顶点
        for(j=0;  j<n; j++) 
             if(minweight[j] != 0 && weights[k][j].wei < minweight[j] ) {  
                  minweight[j] = weights[k][j].wei;    //将小于当前权值的边(k,j)权值加入数组中
                  edges[j] = k;   //将边(j,k)信息存入边数组中
             }
    }
}