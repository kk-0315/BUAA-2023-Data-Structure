#include <stdio.h>
#include <stdlib.h>
typedef struct __C_LNode
{
    int room; // 存放单个节点的数据
    int pos;
    struct __C_LNode *next; // 存放下个节点的地址
} C_LNode, *C_LinkList;
void createList(C_LinkList *L, int n) // 长度为n的循环链表
{
    C_LinkList pnew, r = NULL;
    (*L) = NULL;
    int a, b; /* 创建一个空链表 */

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &a, &b); /* 取一个数据元素 */

        pnew = (C_LinkList)malloc(sizeof(C_LNode));
        pnew->pos = a;
        pnew->room = b;
        pnew->next = NULL;
        if ((*L) == NULL)
            (*L) = r = pnew;
        else
        {
            r->next = pnew; /* 将新结点链接在链表尾部 */
            r = r->next;
        }
    }
    r->next = (*L); // 循环的关键，尾结点重新接到头节点
}
// 查找  返回结点地址
C_LinkList Find(C_LinkList L, int e)
{

    C_LinkList node = L;
    // 遍历链表查找与e 相同的值
    while (node->next != L && node->pos != e)
    {
        node = node->next;
    }
    
    return node;
}
// 按值删
int Delete_Val(C_LinkList *L, int e)
{

    C_LinkList delnode = Find((*L), e);
    C_LinkList prenode = (*L);

    if (delnode == NULL)
    {
        return -1;
    }
    for (; prenode->next != delnode; prenode = prenode->next)
        ;
    prenode->next = delnode->next;
    if ((*L) == delnode)
    {
        (*L)=(*L)->next;//防止指向同一片内存空间导致头指针也被free掉就没有头指针了
        if((*L)->next==(*L))//防止死循环，如果只剩一个结点 就置空
        (*L)=NULL;
    }
    free(delnode);
    delnode = NULL;
    if((*L)==NULL)
    prenode=NULL;
    return 0;
}

int main()
{
    C_LinkList L;
    int n;
    scanf("%d", &n);
    int num = n;
    createList(&L, n);
    
    C_LinkList p = L;
    int x;
    while (1)
    {
        scanf("%d", &x);
        if (x == -1)
            break;
        int count = 0;
        int flag = -1;
        int min = 999999;

        if (p->room < min && p->room >= x)
        {
            min = p->room;
            flag = p->pos;
        }
        p = p->next;
        count++;
        while (count < num)
        {
            if (p->room < min && p->room >= x)
            {
                min = p->room;
                flag = p->pos;
            }

            p = p->next;
            count++;
        }
        if (flag != -1)
        {

            C_LinkList node = Find(L, flag);

            if (node->room != 0)
                p = Find(L, flag);
            (node)->room -= x;
            if (node->room == 0)
            {
                p = Find(L, flag)->next;
                Delete_Val(&L, flag);
                num--;
                if (num == 0)
                    p = NULL;
            }
        }
    }
    if (p != NULL)//如果存在结点才输出
    {
        C_LinkList pnode;
        for (pnode = p; pnode->next != p; pnode = pnode->next)
        {
            printf("%d %d\n", pnode->pos, pnode->room);
        }
        printf("%d %d", pnode->pos, pnode->room);
    }
}