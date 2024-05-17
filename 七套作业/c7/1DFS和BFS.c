#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int vis[1005],temp[1005], n;
int a[1005][1005];
void DFS(int v)
{
    vis[v] = 1; // 该顶点被访问
    printf("%d ", v);
    for (int i = 1; i <= n; i++)
    {
        if (a[v][i] == 1 && vis[i] == 0) // 与之有连接的点是否被访问过
        {
            DFS(i);
        }
    }
}

void DFSG()
{
    for (int i = 0; i < n; i++)
    {
        if (vis[i] == 0)
        {
            DFS(i);
        }
    }
}

void BFS()
{
    int front, rear, start;
    front = rear = 0;
    vis[0] = 1;
    printf("%d ",0);
    temp[rear++] = 0;
    while (rear > front)
    {
        start = temp[front++];
        for (int i = 0; i < n; i++)
        {
            if (!vis[i] && a[start][i])
            {
                vis[i] = 1;
                printf("%d ",i);
                temp[rear++] = i;
            }
        }
    }
}

int main()
{
    int edge, k, t, del;
    scanf("%d%d", &n, &edge);
    for (int i = 0; i < edge; i++)
    {
        scanf("%d%d", &k, &t);
        a[k][t] = 1;
        a[t][k] = 1;
    }
    scanf("%d", &del);

    DFSG();
    printf("\n");
    memset(vis,0,1005);
    BFS();
    printf("\n");
    
    for(int i=0;i<n;i++)
    {
        a[del][i]=0;
        a[i][del]=0;
    }
    
    memset(vis,0,1005);
    vis[del]=1;
    DFSG();
    printf("\n");
    memset(vis,0,1005);
    vis[del]=1;
    BFS();
    printf("\n");
}