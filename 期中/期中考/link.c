#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef struct __LNode
{
    int data;
    int count;            // 存放单个节点的数据
    struct __LNode *next; // 存放下个节点的地址
} LNode, *LinkList;
void Insert_end(LinkList *L, int num);
void delete(LinkList *L, int num);
void Insert_Head(LinkList *L, LinkList p);
int seek(LinkList L,int num,int *t);
int count1=0;
int main()
{
    int n, num,t;
    scanf("%d", &n);
    // 创建单链表
    LinkList L;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL; // 初始化
    
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num);

        if (seek(L,num,&t) == 0) // 没找到
        {
            Insert_end(&L, num);
        }
        else
        {
            
            LinkList p;
            p = (LinkList)malloc(sizeof(LNode));
            p->count=t+1;
            p->data=num;
            delete (&L,num);
            
            Insert_Head(&L, p);
        }
    }
    LinkList q;
    int number;
    for (q = L->next,number=0; (q != NULL)&&number<5; q = q->next,number++)
    {
        printf("%d %d\n", q->data, q->count);
    }
    printf("%d",count1);
}
void Insert_end(LinkList *L, int num)
{
    LinkList p;
    p = (*L);
    while (p->next != NULL)
    {
        p = p->next;
    }
    LinkList q;
    q = (LinkList)malloc(sizeof(LNode));
    q->data = num;
    q->count = 1;
    q->next = NULL;
    p ->next= q;
}
void delete(LinkList *L, int num)
{
    LinkList p=NULL, q=NULL; /*p指向要删除的结点，q为p的前一个结点*/
    for (p = (*L); p != NULL; q = p, p = p->next){
        if (p->data == num) /*找到要删除的链结点*/
            {
                
                break;
            }
        
    }
    if (q->next != NULL)
    { /* 删除p指向的结点*/
        q->next = p->next;
        free(p);
    }
    
}

void Insert_Head(LinkList *L, LinkList p)
{
    LinkList q;
    q=(*L)->next;
    (*L)->next=p;
    p->next=q;
}

int seek(LinkList L,int num,int *t)
{
    LinkList p=L->next;
    while(p!=NULL&&p->data!=num)
    {
        
        p=p->next;
        count1++;
    }
    if(p!=NULL)
    count1++;
    if(p==NULL)
    return 0;
    else
    {
        (*t)=p->count;
        return 1;
    }
}