#define MaxV 256
typedef struct edge
{
    int adj;
    int wei;
    struct edge *next;
} Elink;
typedef struct ver
{
    Elink *link;
} Vlink;
Vlink G[MaxV];
int Visited[N] = {0}; // 标识顶点是否被访问，N为顶点数
void travelBFS(Vlink G[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        Visited[i] = 0;
    for (i = 0; i < n; i++)
        if (!Visited[i])
            BFS(G, i);
}
void BFS(Vlink G[], int v)
{
    Elink *p;
    Visited[v] = 1; // 标识某顶点已入队
    enQueue(Q, v);
    while (!emptyQ(Q))
    {
        v = deQueue(Q);                             // 取出队头元素
        VISIT(G, v);                                // 访问当前顶点
        for (p = G[v].link; p != NULL; p = p->next) // 访问该顶点的每个邻接顶点
            if (!Visited[p->adjvex])
            {
                Visited[p->adjvex] = 1; // 标识某顶点入队
                enQueue(G, p->adjvex);
            }
    }
}
