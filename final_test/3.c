#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
struct STACK_NUM
{
    int id;
    int n; // 子树个数
    struct STACK_NUM *link[105];
    struct STACK_NUM *parent;
    int flag; // 0为叶结点
    char time[50];
    char name[50];
};
struct STACK_NUM stack_num[1000];
struct STACK_NUM cur, h[1000];
char stack_op[1000];
int top_num = -1;
int top_op = -1;
char g[1000];
char NAME[50];
int ID;
int FLAG;
char TIME[100];
int main()
{

    FILE *in;
    char c;
    in = fopen("in.txt", "r");
    while ((c = fgetc(in)) != '\n')
    {
        int num = 0;
        if (c >= '0' && c <= '9')
        {

            while (c >= '0' && c <= '9')
            {
                num = num * 10 + c - '0';
                c = fgetc(in);
            }
            stack_num[++top_num].id = num;
        }

        if (c == ')')
        {
            int k = 0;
            if (stack_op[top_op] == ',')
            {
                while (stack_op[top_op] == ',')
                {
                    h[k++] = stack_num[top_num--];
                    top_op--;
                }
                if (stack_op[top_op] == '(')
                {

                    h[k++] = stack_num[top_num--];
                    top_op--;
                    for (int i = 0; i < k; i++)
                    {
                        stack_num[top_num].link[stack_num[top_num].n++] = &h[i];
                        h[i].parent = &stack_num[top_num];
                    }
                }
            }
            else if (stack_op[top_op] == '(')
            {
                cur = stack_num[top_num];
                top_num--;
                stack_num[top_num].link[stack_num[top_num].n++] = &cur;
                cur.parent = &stack_num[top_num];
                top_op--;
            }
        }
        else
        {
            stack_op[++top_op] = c;
        }
    }
    struct STACK_NUM p = stack_num[top_num];
    while (fscanf(in, "%d %s %d %s", &ID, NAME, FLAG, TIME) != EOF)
    {
        layerorder1(p, ID, NAME, FLAG, TIME);
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {

    }
}
void layerorder1(struct STACK_NUM t, int id, char name[], int flag, char time[]) // 按层次插入
{
    struct STACK_NUM queue[1000], p;
    int front, rear;

    queue[0] = t;
    front = 0;
    rear = 0;
    while (front <= rear)
    { /* 若队列不空 */
        p = queue[front++];
        if (p.id == id)
        {
            p.flag = flag;
            strcpy(p.name, name);
            strcpy(p.time, time);
        } /* 访问p指结点 */
        for (int i = 0; i < p.n; i++)
        {
            if (p.link[i] != NULL)
                queue[++rear] = *p.link[i];
        }
    }
}
void dfs(struct STACK_NUM *a, int deep)
{
    int i;
    if (a->id == 0)
    {
        if (strcmp(a->name, Target) == 0)
        {
            
        }
        return;
    }
    else
    {
        for (i = 0; i < a->n; i++)
        {
            dfs(a->link[i], deep + 1);
        }
    }
}