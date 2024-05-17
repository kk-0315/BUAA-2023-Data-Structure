#include<stdio.h>
//以邻接矩阵存储
int vis[1005],n=6;
int G[1005][1005];

void DFS(int v)
{
    vis[v] = 1; // 该顶点被访问
    printf("%d ", v);
    for (int i = 1; i <= n; i++)
    {
        if (G[v][i] == 1 && vis[i] == 0) // 与之有连接的点是否被访问过
        {
            DFS(i);
        }
    }
}

void travelDFS()
{
    for (int i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            DFS(i);
        }
    }
}
int main()
{
    G[0][1]=1,G[0][4]=1,G[0][2]=1;
    G[1][0]=1,G[1][4]=1;
    G[2][0]=1,G[2][5]=1;
    G[5][2]=1,G[5][3]=1;
    G[4][3]=1,G[4][1]=1,G[4][0]=1;
    G[3][5]=1,G[3][4]=1;
    travelDFS();
}