#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 多重链表的表示
#define MaxTree 100 // 定长
typedef struct node
{
    int data;
    struct node *child[MaxTree]; // 每个结点都先分配给你这么多空间的指针
} tree, *tree;

// 不定长链表的表示 加一个int degree
typedef struct i_node
{
    int data;
    int degree;
    struct i_node *child[MaxTree];
} I_tree, *i_tree;

// 三重链表的表示
typedef struct t_node
{
    int data;
    struct Node *child, *parent, *brother;
} T_tree, *t_tree;

// 二叉树的表示
typedef struct d_node
{
    char data;
    struct d_node *lchild;
    struct d_node *rchild;
} D_tree, *d_tree;

// 二叉树的基本操作

// 二叉初始化
void init_d_tree(d_tree root)
{
    root->data = " ";
    root->lchild = NULL;
    root->rchild = NULL;
}

// 二叉树的创建
d_tree create(d_tree root)
{
    char ch;
    scanf("%c", &ch);
    if (ch == ' ') // 规定字符为空格时 指针域置零
        root = NULL;
    else
    {
        root = (d_tree)malloc(sizeof(D_tree)); // 申请空间
        root->data = ch;
        create(root->lchild); // 递归建立左树
        create(root->rchild); // 递归建立右树
    }
    return root;
}

// 判断二叉树是否空
int d_tree_empty(d_tree root)
{
    if (root->data == ' ')
        return 0;
    else
        return 1;
}

// 二叉树叶结点数目
int d_tree_leaf(d_tree t)
{
    if (t == NULL)
        return 0;
    if (t->lchild == NULL && t->rchild == NULL) // 叶节点没有孩子
        return 1;
    return (d_tree_leaf(t->lchild) + d_tree_leaf(t->rchild)); // 递归树的叶节点=左树叶节点+右树叶节点
}

// 二叉树的深度
int d_tree_depth(d_tree t)
{
    int leftdepth, rightdepth;
    if (t == NULL)
        return 0;
    else
    {
        /*找到左右树中深度最大的*/
        leftdepth = d_tree_depth(t->lchild);
        rightdepth = d_tree_depth(t->rchild);
        if (leftdepth > rightdepth)
            return leftdepth + 1;
        else
            return rightdepth + 1;
    }
}

// 二叉树的遍历
// 前序遍历 根——左——右
void dlr_search(d_tree t)
{
    if (t != NULL)
    {
        printf("%c\n", t->data); // 访问t 这里代指打印
        dlr_search(t->lchild);
        dlr_search(t->rchild);
    }
}

// 中序遍历
void ldr_search(d_tree t)
{
    if (t != NULL)
    {
        dlr_search(t->lchild);
        printf("%c\n", t->data);
        dlr_search(t->rchild);
    }
}

// 后序遍历
void lrd_search(d_tree t)
{
    if (t != NULL)
    {
        dlr_search(t->lchild);
        dlr_search(t->rchild);
        printf("%c\n", t->data);
    }
}

// 非递归的遍历

// 中序遍历的非递归算法
#define M 50
void dis_ldf_search(d_tree t)
{
    d_tree stack[M], p = t;
    int top = -1;
    if (t != NULL)
    {
        do
        {
            while (p != NULL) // 左边全进栈
            {
                stack[++top] = p;
                p = p->lchild;
            }
            p = stack[top--];        // 出栈
            printf("%c\n", p->data); // 访问p
            p = p->rchild;
        } while (!(p == NULL && top == -1));
    }
}

// 后序遍历的非递归算法
void dis_lrd_search(d_tree t)
{
    d_tree stack1[M], p = t;
    int stack2[M], flag, top = -1;
    if (t != NULL)
    {
        do
        {
            while (p != NULL)
            {
                stack1[++top] = p;
                stack2[top] = 0; // 0标志左边进栈
                p = p->lchild;
            }
            p = stack1[top];
            flag = stack2[top--];
            if (flag == 0)
            {
                stack1[++top] = p;
                stack2[top] = 1; // 标志表示右边进栈
                p = p->rchild;
            }
            else
            {
                printf("%c\n", p->data); // 访问p
                p = NULL;
            }
        } while (!(p == NULL && top == -1));
    }
}

// 按层遍历
void floor_search(d_tree t)
{
    d_tree queue[50], p;
    int front, rear;
    if (t != NULL)
    {
        queue[0] = t;
        front = -1;
        rear = 0;
        while (front < rear) // 这p的孩子所在层是否还有节点
        {
            p = queue[++front]; // 出队列
            // 访问p；
            /*------------------------------------------------------------------*/
            printf("%c", p->data);
            /*------------------------------------------------------------------*/
            if (p->lchild != NULL)
                queue[++rear] = p->lchild; // 入队列
            if (p->rchild != NULL)
                queue[++rear] = p->rchild; // 入队列
        }
    }
}

// 求二叉树以某值为根的子树深度
int x_depth(d_tree root, char x)
{
    if (root == NULL)
        return 0;

    if (root->data == x)
        return d_tree_depth(root);
    else
    {
        x_depth(root->lchild, x);
        x_depth(root->rchild, x);
    }
}

// 求指定结点的层数
int x_floor(d_tree root, char x)
{
    int f, l, r;
    if (root == NULL)
        f = 0;
    else if (root->data == x)
        f = 1;
    else
    {
        l = x_floor(root->lchild, x);
        r = x_floor(root->rchild, x);
        if (l == 0 && r == 0)
            f = 0;
        else
        {
            f = ((l > r) ? l : r) + 1;
        }
    }
    return f;
}

// 统计结点数目
int node_num(d_tree root)
{
    if (root == NULL)
        return 0;
    else
        return (node_num(root->lchild) + node_num(root->rchild)) + 1;
}

// 二叉树的销毁
void destroy_tree(d_tree root)
{
    if (root != NULL)
    {
        destroy_tree(root->lchild);
        destroy_tree(root->rchild);
        free(root);
    }
}

// 二叉树的复制
d_tree copy_tree(d_tree t1)
{
    d_tree t2;
    if (t1 == NULL)
        return NULL;
    else
    {
        t2 = (d_tree)malloc(sizeof(D_tree));
        t2->data = t1->data;
        t2->lchild = copy_tree(t1->lchild);
        t2->rchild = copy_tree(t1->rchild);
    }
    return t2;
}

// 二叉树是否等价
int equal_tree(d_tree t1, d_tree t2)
{
    if (t1 == NULL && t2 == NULL)
        return 1;
    if (t1 != NULL && t2 != NULL && t1->data == t2->data && equal_tree(t1->lchild, t2->lchild) && equal_tree(t1->rchild, t2->rchild))
        return 1;
    return 0;
}

// 二叉树是否相似
int similar_tree(d_tree t1, d_tree t2)
{
    if (t1 == NULL && t2 == NULL)
        return 1;
    if (t1 != NULL && t2 != NULL && similar_tree(t1->lchild, t2->lchild) && similar_tree(t1->rchild, t2->rchild))
        return 1;
    return 0;
}

// 删除指定item的结点和该结点的子树 ??

// 交换所有结点的左、右子树的位置。
void exchange_tree(d_tree t)
{
    d_tree queue[50], temp, p = t;
    int front, rear;
    if (t != NULL)
    {
        queue[0] = t;
        front = -1;
        rear = 0;
        while (front < rear)
        {
            p = queue[++front]; // 出队
            /*交换左右节点*/
            temp = p->lchild;
            p->lchild = p->rchild;
            p->rchild = temp;
            // 入队
            if (p->lchild != NULL)
                queue[++rear] = p->lchild;
            if (p->rchild != NULL)
                queue[++rear] = p->rchild;
        }
    }
}

/*二叉排序树*/

// 二叉排序树的插入
d_tree sort_tree_insert(d_tree t, char item)
{
    if (t == NULL)
    {
        t = (d_tree)malloc(sizeof(D_tree));
        t->data = item;
        t->lchild = NULL;
        t->rchild = NULL;
    }
    else if (item < t->data)
    {
        t->lchild = sort_tree_insert(t->lchild, item);
    }
    else
    {
        t->rchild = sort_tree_insert(t->rchild, item);
    }
    return t;
}

// 二叉树的查找
d_tree d_tree_sort(d_tree t, char item)
{
    d_tree p = t;
    while (p != NULL)
    {
        if (p->data == item)
            return p;
        if (item < p->data)
            p = p->lchild;
        else
            p = p->rchild;
    }
    return NULL;
}

// 线索二叉树
typedef struct detail
{
    int data;
    struct detail *lchild, *rchild;
    int lbit, rbit;
} Det_node, *det_node;

// 求直接前驱
det_node tree_inprior(det_node x)
{
    det_node s;
    s = x->lchild;
    if (x->lbit == 1)
    {
        while (s->rbit == 1)
        {
            s = s->rchild;
        }
    }
    return (s);
}

// 求直接后继
det_node tree_insucc(det_node x)
{
    det_node s;
    s = x->rchild;
    if (x->rbit == 1)
    {
        while (x->lbit == 1)
        {
            s = s->lchild;
        }
    }
    return (s);
}

// 线索二叉树的遍历
void search_tree(det_node head)
{
    det_node p = head;
    while (1)
    {
        p = tree_insucc(p);
        if (p == NULL)
            break;
        // 对p进行访问
        printf("%d", p->data);
    }
}

// 求所有度为1的个数 链式存储方式 一个遍历解决问题
typedef struct bnode
{
    d_tree data;
    struct bnode *link;
} bque, *Bque;

int cont_du1_tree(d_tree t)
{
    d_tree p = t;
    Bque top = NULL, q;
    int n = 0;
    if (t != NULL)
    {
        do
        {
            while (p != NULL)
            {
                if ((p->lchild != NULL && p->rchild == NULL) | (p->lchild == NULL && p->rchild != NULL))
                    n++;
                q = (Bque)malloc(sizeof(bque));
                q->data = p;
                q = top;
                p = p->lchild;
            }
            p = top->data;
            q = top;
            top = top->link;
            free(q);
            p = p->rchild;
        } while (!(p == NULL && top == NULL));
    }
    return n;
}

// 打印求信息是item的结点的所有祖先结点 后序遍历
void ansestor_tree(d_tree t, int item)
{
    d_tree stack1[M], p = t;
    int stack2[M], top = -1, flag;
    if (t != NULL && t->data != item)
    {
        do
        {
            while (p != NULL)
            {
                stack1[++top] = p;
                stack2[top] = 0;
                p = p->lchild;
            }
            p = stack1[top];
            flag = stack2[top--];
            if (flag == 0)
            {
                stack1[++top] = p;
                stack2[top] = 1;
                p = p->rchild;
            }
            else
            {
                if (p->data == item)
                {
                    while (top != -1)
                    {
                        printf("%4d", stack1[top--]->data);
                    }
                    break;
                }
                else
                {
                    p = NULL;
                }
            }
        } while (!(p == NULL && top == -1));
    }
}

/*哈夫曼树-最优二叉树*/

int main()
{
    return 0;
}