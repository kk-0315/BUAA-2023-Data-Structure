#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//考察遍历
typedef struct Node
{
    int data;

    struct Node *left, *right, *mid;
} Node, *Tree;
Tree queue[200];
typedef struct _gate
{
    int no;
    int num;
} Gate;
int s[50];
int count;
int cmp1(const void *p1, const void *p2)
{
    if ((((struct _gate *)p1)->num) == (((struct _gate *)p2)->num)&&(((struct _gate *)p1)->no) > (((struct _gate *)p2)->no))
        
        return 1;
    else if ((((struct _gate *)p1)->num) < (((struct _gate *)p2)->num))
        return 1;
    else
        return -1;
}
Tree Insert(int x, Tree t);
Tree preorder(int x, Tree t);
void layerorder(Tree t);
int main()
{

    Tree T = NULL, t = NULL;
    int flag = 0;
    while (1)
    {
        int q = 0;
        scanf("%d", &s[q++]);
        if (s[q - 1] == -1)
            break;
        while (1)
        {
            scanf("%d", &s[q++]);
            if (s[q - 1] == -1)
                break;
        }
        if (q - 1 == 3)
        {
            t = Insert(s[0], T);
            t->left = Insert(s[1], NULL);
            t->right = Insert(s[2], NULL);
            t->mid = NULL;

            if (flag == 0)
            {
                T = t;
                flag = 1;
            }
        }
        else
        {
            t = Insert(s[0], T);
            t->left = Insert(s[1], NULL); // 调试过程中会在这一步出错，因为t==null
            t->mid = Insert(s[2], NULL);
            t->right = Insert(s[3], NULL);

            if (flag == 0)
            {
                T = t;
                flag = 1;
            }
        }
        memset(s, 0, 50);
    }

    int ans[200];
    memset(queue,0,200);
    layerorder(T);
    memset(ans, 0, 200);

    for (int i = 0; i < 200; i++)
    {
        if (queue[i] != NULL)
        {
            if (queue[i]->data < 100 &&queue[i]->data>0)
            {
                ans[count++] = queue[i]->data;
            }
        }
    }
    int k = 0, id = 0, flow = 0, m = 0;
    Gate g[200];
    while (k < count)
    {
        scanf("%d%d", &id, &flow);
        g[m].no = id;
        g[m++].num = flow;
        k++;
    }
    qsort(g, count, sizeof(struct _gate), cmp1);
    for (int i = 0; i < count; i++)
    {

        printf("%d->%d\n", g[i].no, ans[i]);
    }
}

Tree Insert(int x, Tree t)
{
    Tree f;
    if (t == NULL)
    {
        /*create and return a one-node tree*/
        t = (Tree)malloc(sizeof(struct Node));
        t->data = x;
        t->left = t->mid = t->right = NULL;
        return t;
    }
    else
    {
        return f = preorder(x, t);
    }
}
Tree preorder(int x, Tree t) // 这里有问题，求助
{
    Tree p = t;
    Tree a, b, c;
    if (p == NULL)
        return NULL;
    if (p->data == x)
        return p;
    a = preorder(x, p->left);
    b = preorder(x, p->mid);
    c = preorder(x, p->right);
    if (a == NULL)
    {
        if (b == NULL)
        {
            return c;
        }
        else
        {
            return b;
        }
    }
    else
    {
        return a;
    }
}
void layerorder(Tree t) // 按层次
{
    Tree p;
    int front, rear;
    if (t != NULL)
    {
        queue[0] = t;
        front = 0;
        rear = 0;
        while (front <= rear)
        { /* 若队列不空 */
            p = queue[front++];
            /* 访问p指结点 */
            if (p->left != NULL) /* 若左孩子非空 */
                queue[++rear] = p->left;
            if (p->mid != NULL) /* 若左孩子非空 */
                queue[++rear] = p->mid;
            if (p->right != NULL) /* 若右孩子非空 */
                queue[++rear] = p->right;
        }
    }
}