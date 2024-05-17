#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
struct EDGE
{
    int vertex1;
    int vertex2;
};
int num;
struct VERTEX
{
    int hash_eno[1000]; // 结点哈希值(实际上存的是与邻接结点相连的直线的序号，便于排序）
    int size;           // 有多少个相邻节点
};
int vertex_size, edge_size;
struct VERTEX ver[1000];
struct EDGE edge[1000];
int visited[100];
char tmp[100];
int len, m;
char path[1000][1000];
void add(int v1, int v2);
void DFS(int begin, int end);
void bubbleSort(int k[], int n);
int main()
{
    int v1, v2;
    scanf("%d%d", &vertex_size, &edge_size);
    for (int i = 0; i < edge_size; i++)
    {
        scanf("%d%d%d", &num, &v1, &v2);
        add(v1, v2);
    }
    DFS(0, vertex_size - 1);
    for (int i = 0, t = 0; i < m; i++, t = 0)
    {
        while (path[i][t])
        {
            printf("%d ", (int)path[i][t++]);
        }
        printf("\n");
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

void add(int v1, int v2)
{
    edge[num].vertex1 = v1;
    edge[num].vertex2 = v2;
    ver[v1].hash_eno[ver[v1].size] = num;
    ver[v1].size++;
    bubbleSort(ver[v1].hash_eno, ver[v1].size);
    ver[v2].hash_eno[ver[v2].size] = num;
    ver[v2].size++;
    bubbleSort(ver[v2].hash_eno, ver[v2].size);
}
void DFS(int begin, int end) // 回溯算法!
{
    int tmp_edge, j;
    if (begin == end)
    {
        // 回溯，返回上一个结点，重新判断下一步往哪走
        visited[begin] = 0; // 这么做的原因是：虽然这条路已经不能再往这走了（i++）但是如果继续返回上一结点，仍有可能往这走，因此得置0
        strcpy(path[m++], tmp);
        tmp[len--] = 0;
        return;
    }
    visited[0] = 1;
    for (int i = 0; i < ver[begin].size; i++)
    {
        tmp_edge = ver[begin].hash_eno[i];
        j = edge[tmp_edge].vertex1 + edge[tmp_edge].vertex2 - begin; // 得到另一个结点的序号
        if (!visited[j])
        {
            visited[j] = 1;
            tmp[len++] = (char)tmp_edge;
            DFS(j, end);
            // 当end==begin时return回来，之后i++也就是到了下一个邻接结点，判断这个结点能不能到达end
            // 如果这个是最后一个邻接结点，for循环退出
        }
    }
    // 也就是这个节点所有到达end的方式都遍历了，此时只能再返回上一个结点，继续重新判断下一步怎么走
    visited[begin] = 0; // 回溯清除当前这个结点的访问记录，以便之后可能的顺利访问
    tmp[len--] = 0;     // 清除tmp
}