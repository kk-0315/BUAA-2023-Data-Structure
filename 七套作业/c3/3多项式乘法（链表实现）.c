/*多项式乘法的链表实现*/

#include<stdio.h>
#include<stdlib.h>
typedef struct pnode
{
    int coe; // 系数
    int pow; // 指数
    struct pnode *next;
} Polynode, *Polynomial;
void Create_R(Polynomial *L)//尾插法创建链表
{
    Polynomial s, r;
    (*L) = (Polynode *)malloc(sizeof(Polynode));
    (*L)->next = NULL;
    r = (*L);
    int a, b;
    char c;
    do
    {
        s = (Polynode *)malloc(sizeof(Polynode));
        scanf("%d%d%c", &a, &b, &c);
        s->coe = a;
        s->pow = b;
        r->next = s;
        r = s;
    } while (c != '\n');
    r->next = NULL;
}
void Sort(Polynomial *L)//把链表按照指数从大到小排序
{
    Polynomial p, pre, q;
    p = (*L)->next;
    if (p != NULL)//L有一个以上的数据结点
    {
        q = p->next;//q保存p结点后的后继结点
        p->next = NULL;//构造只含有一个数据结点的有序表
        p = q;
        while (p != NULL)//扫描剩下的数据结点
        {
            q = p->next;////q保存p结点后的后继结点，继续向后推进
            pre = (*L);
            
            while (pre->next != NULL && pre->next->pow > p->pow)
            pre = pre->next;//寻找插入结点的前驱结点
            
            p->next = pre->next;//将p插入pre之后
            pre->next = p;
            p = q;//向后推进
        }
    }
}
void Multi(Polynomial ha,Polynomial hb,Polynomial *hc)
{
    Polynomial pa,pb,s,pc;
    pa=ha->next;
    (*hc) = (Polynode *)malloc(sizeof(Polynode));
    pc=(*hc);
    while(pa!=NULL)
    {
        pb=hb->next;
        while(pb!=NULL)
        {
            s = (Polynode *)malloc(sizeof(Polynode));
            s->coe=pa->coe*pb->coe;
            s->pow=pa->pow+pb->pow;
            pc->next=s;
            pc=s;

            pb=pb->next;//b链表中每一项乘a中的一项，赋给链表c
        }
        pa=pa->next;//a向后推进一项
    }
    pc->next=NULL;

}
void Comb(Polynomial *L)
{
    Polynomial pre,p;
    pre=(*L)->next;
    if(pre==NULL)
    return ;

    p=pre->next;

    while(p!=NULL)
    {
        while(p->pow==pre->pow)//比较前后指数是否相同（前提是已经排序过）
        {
            pre->coe+=p->coe;
            pre->next=p->next;
            free(p);//删掉p结点
            p=pre->next;//p结点继续下一项比较直到不等
        }
        pre=p;//pre向后推进一项，也就是这个时候的p
        p=p->next;//p也向后推进一项
    }
}
void Delete0(Polynomial *L)
{
    Polynomial pre,p;
    pre=(*L);
    p=pre->next;//均需要三个结点（头节点（空）、pre结点、p结点）通常是pre和p进行比较，比完都要向后推进
    while(p!=NULL)
    {
        if(p->coe==0)
        {
            pre->next=p->next;
            free(p);
        }
        pre=p;
        p=p->next;//向后推进
    }
}
int main()
{
    Polynomial Poly1,Poly2,Poly3;
    Create_R(&Poly1);
    Create_R(&Poly2);
    Sort(&Poly1);
    Sort(&Poly2);

    Multi(Poly1,Poly2,&Poly3);

    Sort(&Poly3);

    Comb(&Poly3);

    Delete0(&Poly3);

    Polynomial p;
    p=Poly3->next;

    while(p!=NULL)
    {
        printf("%d %d ",p->coe,p->pow);
        p=p->next;
    }

}