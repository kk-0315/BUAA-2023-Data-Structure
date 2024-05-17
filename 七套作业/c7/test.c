#include <stdio.h>
#define VNUM 7
#define INFINITY 999


int Weights[VNUM][VNUM]={
    INFINITY,3,2,3,INFINITY,INFINITY,INFINITY,
    INFINITY,INFINITY,3,INFINITY,1,INFINITY,INFINITY,
    INFINITY,INFINITY,INFINITY,INFINITY,3,INFINITY,INFINITY,
    INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,3,INFINITY,
    INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,1,
    INFINITY,INFINITY,1,INFINITY,INFINITY,INFINITY,5,
    INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY
};
int Spath[VNUM] = {0};
int Sweight[VNUM], wfound[VNUM];

void Dijkstra(int v0)
{
    int i, j, v, minweight;
    char wfound[VNUM] = {0}; // 用于标记从v0到相应顶点是否找到最短路径，0未找到，1找到
    for (i = 0; i < VNUM; i++)
    {
        Sweight[i] = Weights[v0][i];
        Spath[i] = v0;
    } // 初始化数组Sweight和Spath
    Sweight[v0] = 0;
    wfound[v0] = 1;
    for (i = 0; i < VNUM - 1; i++)
    { // 迭代VNUM-1次
        minweight = INFINITY;
        for (j = 0; j < VNUM; j++) // 找到未标记的最小权重值顶点
            if (!wfound[j] && (Sweight[j] < minweight))
            {
                v = j;
                minweight = Sweight[v];
            }
        wfound[v] = 1;             // 标记该顶点为已找到最短路径
        for (j = 0; j < VNUM; j++) // 找到未标记顶点且其权值大于v的权值+(v,j)的权值，更新其权值
            if (!wfound[j] && (minweight + Weights[v][j] < Sweight[j]))
            {
                Sweight[j] = minweight + Weights[v][j];
                Spath[j] = v; // 记录前驱顶点
            }
    }
}

int main()
{
    
    Dijkstra(0);
    for(int i=0;i<VNUM;i++)
    printf("%d ",Spath[i]);
}