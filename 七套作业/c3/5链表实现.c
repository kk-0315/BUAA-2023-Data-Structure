#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct __LNode
{
    int count;
    char character[500];  // 存放单个节点的数据
    struct __LNode *next; // 存放下个节点的地址
} LNode, *LinkList;
char s[500];
int find(LinkList *L, char s[])
{
    LinkList p = (*L);
    for (; p != NULL; p = p->next)
    {
        if (strcmp((p->character), s) == 0)
        {
            p->count++;
            return 1; // 找到
        }
    }
    return 0; // 没找到
}
void BubbleSort(LinkList *L)
{
    int i, count = 0, num; // count记录链表结点的个数，num进行内层循环，
    LinkList p, q, tail;    // 创建三个指针，进行冒泡排序
    p = (*L);
    while (p->next != NULL) // 计算出结点的个数
    {
        count++; // 注释①
        p = p->next;
    }
    for (i = 0; i < count - 1; i++) // 外层循环，跟数组冒泡排序一样
    {
        num = count - i - 1; // 记录内层循环需要的次数，跟数组冒泡排序一样，
        q = (*L)->next;         // 令q指向第一个结点
        p = q->next;         // 令p指向后一个结点
        tail = (*L);            // 让tail始终指向q前一个结点，方便交换，也方便与进行下一步操作
        while (num--)        // 内层循环 次数跟数组冒泡排序一样
        {
            if (strcmp(q->character,p->character)>0) // 如果该结点的值大于后一个结点，则交换
            {
                q->next = p->next;
                p->next = q;
                tail->next = p;
            }
            tail = tail->next; // 注释②
            q = tail->next;    // 注释②
            p = q->next;       // 注释②
        }
    }
}
int main()
{
    LinkList L, r;
    L = (LinkList)malloc(sizeof(LNode));
    L = NULL;
    r = L;
    FILE *in;
    in = fopen("article.txt", "r");

    char c;
    while (1)
    {
        int q = 0;
    A:
        while ((c = fgetc(in)) != EOF)
        {
            if (c >= 'A' && c <= 'Z')
            {
                c = 'a' - 'A' + c;
            }
            if (c >= 'a' && c <= 'z')
                s[q++] = c;
            else
                break;
        }
        if (q == 0 && c != EOF)
            goto A;
        if (c == EOF)
            break;
        LinkList pnew;
        pnew = (LinkList)malloc(sizeof(LNode));

        int len = strlen(s);
        for (int i = 0; i < len; i++)
        {
            pnew->character[i] = s[i];
        }
        for (int i = len; i < 500; i++)
            pnew->character[i] = 0;
        pnew->next = NULL;
        pnew->count = 1;
        if (L == NULL)
        {
            L = r = pnew;
        }
        else
        {
            if (find(&L, s) == 0)
            {

                r->next = pnew; // 注意有没有可能操作了空指针
                r = r->next;
            }
        }
        for (int i = 0; i < 500; i++)
        {
            s[i] = 0;
        }
    }
    LinkList node;
    node = (LinkList)malloc(sizeof(LNode));
    node->next=L;
    L=node;
    BubbleSort(&L);
    LinkList q;
    for (q = L->next; q != NULL; q = q->next)
    {
        printf("%s %d\n", q->character, q->count);
    }
}