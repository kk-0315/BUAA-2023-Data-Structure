#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXNUM 512 // 地铁最大站数
#define MAXLEN 16  // 地铁站名的最大长度
#define INFINITY 32767
int Spath[MAXNUM];
int Sweight[MAXNUM];
int wfound[MAXNUM];
int final_path[MAXNUM];
struct station
{                       // 车站信息
    char sname[MAXLEN]; // 车站名
    int ischange;       // 是否为换乘站，0-否，1-换乘
};
struct weight
{
    int wei; // 两个站间的权重，即相差站数，缺省为1
    int lno; // 两个顶点所在的线号
};
struct station BGvertex[MAXNUM];         // 地铁网络图顶点数组
struct weight BGweights[MAXNUM][MAXNUM]; // 网络图权重数组，邻接矩阵
int Vnum = 0;                            // 实际地铁总站数
int path_num = 0;
char start[20], end[20];
int addVertex(struct station st);
void initMap();
void Dijkstra(int v0);
void put_path();
int main()
{
    for (int i = 0; i < MAXNUM; i++)
    {
        for (int j = 0; j < MAXNUM; j++)
        {
            BGweights[i][j].wei = INFINITY;
            BGweights[i][j].lno = 0;
        }
    }

    initMap();
    scanf("%s", start);
    scanf("%s", end);
    int flag1 = 0, flag2 = 0;

    for (int i = 0; i < Vnum; i++)
    {
        if (!strcmp(start, BGvertex[i].sname))
        {
            flag1 = i;
        }
        if (!strcmp(end, BGvertex[i].sname))
        {
            flag2 = i;
        }
    }
    Dijkstra(flag1);

    int tmp = flag2;
    while (tmp != flag1)
    {
        final_path[path_num++] = tmp;
        tmp = Spath[tmp];
    }
    final_path[path_num++] = tmp;

    int tmp_path[MAXNUM] = {0};
    for (int i = 0; i < path_num; i++)
    {
        tmp_path[i] = final_path[path_num - i - 1];
    }
    for (int i = 0; i < path_num; i++)
    {
        final_path[i] = tmp_path[i];
    }
    /*for (int i = 0; i < path_num; i++)
        printf("%s ", BGvertex[final_path[i]].sname);*/
    put_path();
}
void put_path()
{
    int last=0,now=1;
    int count=0;
    int line_now;
    line_now=BGweights[final_path[last]][final_path[now]].lno;
    printf("%s",BGvertex[final_path[last]].sname);
    while(now<path_num)
    {
        if(line_now!=BGweights[final_path[last]][final_path[now]].lno)
        {
            printf("-%d(%d)-%s",line_now,count,BGvertex[final_path[last]].sname);
            count=0;
            line_now=BGweights[final_path[last]][final_path[now]].lno;
        }
        last=now;
        count++;
        now++;
    }
    printf("-%d(%d)-%s",line_now,count,end);
}
int addVertex(struct station st)
{
    if (!st.ischange)
    { 
        BGvertex[Vnum++] = st;
        return Vnum - 1; 
    }
    else
    {
        for (int i = 0; i < Vnum; i++)
        {
            if (!strcmp(st.sname, BGvertex[i].sname))
                return i;
        }
        BGvertex[Vnum++] = st;
        return Vnum - 1;
    }
}
void initMap()
{
    FILE *fp;
    fp = fopen("bgstations.txt", "r");
    int i, j, snum, lno, lnum, v1, v2;
    struct station st;
    fscanf(fp, "%d", &snum);
    for (i = 0; i < snum; i++)
    {
        fscanf(fp, "%d %d", &lno, &lnum);
        v1 = v2 = -1;
        for (j = 0; j < lnum; j++)
        {
            fscanf(fp, "%s %d", st.sname, &st.ischange);
            v2 = addVertex(st); // 将该站加到站信息数组中，返回其下标
            if (v1 != -1)
            {
                BGweights[v1][v2].wei = BGweights[v2][v1].wei = 1;
                BGweights[v1][v2].lno = BGweights[v2][v1].lno = lno;
            }
            v1 = v2;
        }
    }
    fclose(fp);
    return;
}
void Dijkstra(int v0)
{
    int i, j, v, minweight;
    // 用于标记从v0到相应顶点是否找到最短路径，0未找到，1找到
    for (i = 0; i < Vnum; i++)
    {
        Sweight[i] = BGweights[v0][i].wei;
        Spath[i] = v0;
    } // 初始化数组Sweight和Spath
    Sweight[v0] = 0;
    wfound[v0] = 1;
    for (i = 0; i < Vnum - 1; i++)
    { // 迭代Vnum-1次
        minweight = INFINITY;
        for (j = 0; j < Vnum; j++) // 找到未标记的最小权重值顶点
            if (!wfound[j] && (Sweight[j] < minweight))
            {
                v = j;
                minweight = Sweight[v];
            }
        wfound[v] = 1;             // 标记该顶点为已找到最短路径
        for (j = 0; j < Vnum; j++) // 找到未标记顶点且其权值大于v的权值+(v,j)的权值，更新其权值
            if (!wfound[j] && (minweight + BGweights[v][j].wei < Sweight[j]))
            {
                Sweight[j] = minweight + BGweights[v][j].wei;
                Spath[j] = v; // 记录前驱顶点
            }
    }
}
