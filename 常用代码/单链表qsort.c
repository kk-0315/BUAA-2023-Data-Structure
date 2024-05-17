#include <stdio.h>
#include <malloc.h>
typedef struct Lnode
{
    int key;
    struct Lnode *next;
} Lnode, *Linklist;
// 链表结构体类型
Linklist createList(Linklist L, int n)
{
    L = (Linklist)malloc(sizeof(Lnode));
    L->next = NULL;
    Lnode *p, *r;
    r = L;
    p = (Lnode *)malloc(sizeof(Lnode));
    scanf("%d", &r->key);
    for (int i = 1; i < n; i++)
    {
        p = (Lnode *)malloc(sizeof(Lnode));
        scanf("%d", &p->key);
        r->next = p;
        r = p;
    }
    r->next = NULL;
    return L;
}
// 初始初始化及尾插法（正序）创建单链表
Linklist getTail(Linklist L)
{
    while (L->next)
        L = L->next;
    return L;
}
// 得到尾指针
void Print(Linklist L)
{
    Lnode *p;
    p = L;
    while (p)
    {
        printf("%d ", p->key);
        p = p->next;
    }
}
// 遍历单链表
Linklist Quicksort(Linklist *listHead, Linklist *listTail)
{
    Lnode *current;
    Lnode *lessHead = NULL, *lessTail = NULL, *moreHead = NULL, *moreTail = NULL;
    current = (*listHead)->next;   // 每次取首节点为枢纽，current指向第二个节点用于遍历
    if ((*listHead)->next != NULL) // 当链表节点数不为1时(说明链表未排好序)
    {
        for (current = (*listHead)->next; current; current = current->next)
        {
            if (current->key < (*listHead)->key)
            {
                if (lessHead == NULL)
                    lessHead = current;
                else
                    lessTail->next = current;
                lessTail = current;
            } // current结点key小于枢纽key时放入less链表
            else
            {
                if (moreHead == NULL)
                    moreHead = current;
                else
                    moreTail->next = current;
                moreTail = current;
            } // current结点key大于枢纽key时放入more链表
        }
        // 根据枢纽结点将T链表分为less和more两个链表
        if (moreTail)
            moreTail->next = NULL;
        if (lessTail)
            lessTail->next = NULL;
        // 将more链表尾结点next域置空
        if (moreHead != NULL)
        {
            moreTail->next = NULL;
            Quicksort(&moreHead, &moreTail);
            (*listHead)->next = moreHead;
            *listTail = moreTail;
        }
        // 若moreHead不空，则current为more链表的尾结点，对more链表进行递归处理,将more链表接在枢纽节点后
        else
        {
            (*listHead)->next = NULL;
            *listTail = *listHead;
        }
        // 若moreHead为空，则只有less链表(即结点key全小于枢纽)，将枢纽结点接在less节点后
        if (lessHead != NULL)
        {
            lessTail->next = NULL;
            Quicksort(&lessHead, &lessTail);
            lessTail->next = *listHead;
            *listHead = lessHead;
        }
        // 若lesseHead不空，对less链表进行递归处理，再将枢纽节点接在less链表后
        else
        {
            lessHead = *listHead;
        }
        // 若lesseHead为空，则枢纽结点作为首节点
        return lessHead;
    }
    else
        return *listHead;
}
int main()
{
    Lnode *L = NULL;
    int n;
    printf("请输入元素个数\n");
    scanf("%d", &n);
    printf("请输入元素\n");
    L = createList(L, n);
    Lnode *listTail;
    listTail = getTail(L);
    Quicksort(&L, &listTail);
    printf("排序后元素序列为\n");
    Print(L);
    return 0;
}
