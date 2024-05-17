
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


enum SYMBOL
{
    OP,
    NUM,
    ELSE,
    EQ
};
enum OPERATOR
{
    ADD,
    SUB,
    DIV,
    MUL,
    L_BRA,
    R_BRA
}; 
char opChar[] = {'+', '-', '/', '*', '(', ')'};
int Pri[] = {0, 0, 1, 1, 2, 3}; //! 规定优先级

union ELEMENT
{
    float num;
    enum OPERATOR op;
};



typedef struct NODE
{
    union ELEMENT value;
    int isBottom; // 0代表在底层, 是数字
    struct NODE *left;
    struct NODE *right;
} *TREE_;
TREE_ Insert(union ELEMENT, TREE_ T);
int Compute(int top, int bottom, char c)
{
    switch (c)
    {
    case '+':
        return top + bottom;
    case '-':
        return bottom - top;
    case '/':
        return bottom / top;
    case '*':
        return bottom * top;
    }
    return 0;
}


TREE_ Insert(union ELEMENT x, TREE_ t)
{
    if (t == NULL)
    {
        /*create and return a one-node tree*/
        t = (TREE_)malloc(sizeof(struct NODE));
        t->value = x;
        t->left = t->right = NULL;
    }
    return t;
}

struct VALUE
{
    int type; // 0代表t, 1代表num, 2代表sign
    int num;
    TREE_ t;
    char c;
};

enum OPERATOR signStack[300];
int sTop = -1;
struct VALUE numStack[300];
int nTop = -1;
int stack[300];
int top = -1;

int Pop()
{
    return stack[top--];
}
void Push(int tmp)
{
    stack[++top] = tmp;
    return;
}

// kernel
enum SYMBOL IdentifySym(union ELEMENT *); // 同时读取入地址
void Operator(enum OPERATOR);             // 后缀表达式逻辑判断, 符号入栈并进行一系列计算
void OutPut(TREE_ t);

// normal
enum OPERATOR PopS(); // 仅移动栈顶,数据直接覆盖
struct VALUE PopN();

void PushS(enum OPERATOR);
void PushN(struct VALUE);

void PostOrder(TREE_ t)
{
    struct VALUE tmp;
    if (t != NULL)
    {
        PostOrder(t->left);
        PostOrder(t->right);
        if (!t->isBottom)
        {
            tmp.type = 1;
            tmp.num = t->value.num;
        }
        else
        {
            tmp.type = 2;
            tmp.c = opChar[t->value.op];
        }
        PushN(tmp);
    }
}

int main()
{
    int i, up, down;
    enum SYMBOL sym;
    union ELEMENT item;
    TREE_ t = NULL;
    struct VALUE a, top, bottom;
    while ((sym = IdentifySym(&item)) != EQ)
    {
        if (sym == OP)
        {
            Operator(item.op);
        }
        else if (sym == NUM)
        {
            a.type = 1;
            a.num = item.num;
            PushN(a);//数字栈
        }
    }
    if (sTop != -1)
    {
        while (nTop!=0)
        {
            item.op = PopS();
            t = Insert(item, NULL);
            t->isBottom = 1;
            if ((top = PopN()).type == 0)//ntop-- //是运算符
                t->right = top.t;
            else//是数字
            {
                item.num = top.num;
                t->right = Insert(item, NULL);
                t->right->isBottom = 0;
            }

            if ((bottom = PopN()).type == 0)//ntop--
                t->left = bottom.t;
            else
            {
                item.num = bottom.num;
                t->left = Insert(item, NULL);
                t->left->isBottom = 0;
            }
            a.type = 0;
            a.t = t;
            PushN(a); // 0代表已经造出来树了//ntop++
        }
    }
    //numstack[]中现在是若干颗树
    a = PopN();//ntop--之后ntop==-1
    t = a.t;//最上面的是根节点
    printf("%c ", opChar[t->value.op]);//根节点
    if (t->left != NULL)//根节点的右子节点
    {
        if (t->left->isBottom)
            printf("%c ", opChar[t->left->value.op]);
        else
            printf("%d ", (int)t->left->value.num);
    }
    if (t->right != NULL)//根节点的左子节点
    {
        if (t->right->isBottom)
            printf("%c\n", opChar[t->right->value.op]);
        else
            printf("%d\n", (int)t->right->value.num);
    }

    // 后序遍历树，将数字或者运算符全都输入numstack[]（从栈底开始因为此时ntop==-1）
    PostOrder(t);
    for (i = 0; i <= nTop; i++)
    {
        if (numStack[i].type == 1)//是数字，压入答案栈
            Push(numStack[i].num);
        else
        {
            up = Pop();
            down = Pop();
            Push(Compute(up, down, numStack[i].c));//是运算符，计算后压入答案栈
        }
    }
    printf("%d", stack[0]);
}

enum SYMBOL IdentifySym(union ELEMENT *s)
{
    char c;
    float n;
    while ((c = getchar()) != '=')
        if (c >= '0' && c <= '9')
        {
            for (n = 0; c >= '0' && c <= '9'; c = getchar())
                n = n * 10 + (float)(c - '0');
            ungetc(c, stdin);
            s->num = n;
            return NUM;
        }
        else
        {
            switch (c)
            {
            case '+':
                s->op = ADD;
                return OP;
            case '-':
                s->op = SUB;
                return OP;
            case '*':
                s->op = MUL;
                return OP;
            case '/':
                s->op = DIV;
                return OP;
            case '(':
                s->op = L_BRA;
                return OP;
            case ')':
                s->op = R_BRA;
                return OP;
            default:
                continue;
            }
        }

    return EQ;
}

void Operator(enum OPERATOR sign)
{
    struct VALUE n, top, bottom;
    union ELEMENT ele;
    TREE_ t = NULL;
    enum OPERATOR op;
    if (sign == R_BRA)
    {
        for (op = PopS(); op != L_BRA; op = PopS())
        {
            ele.op = op;
            t = Insert(ele, NULL);//创建单节点树
            t->isBottom = 1;//不是数字

            //取出top和bottom两个东西出来（有可能是树或者数字）
            if ((top = PopN()).type == 0)
                t->right = top.t;//是一颗树
            else//是数字
            {
                ele.num = top.num;
                t->right = Insert(ele, NULL);
                t->right->isBottom = 0;
            }
            if ((bottom = PopN()).type == 0)
                t->left = bottom.t;
            else
            {
                ele.num = bottom.num;
                t->left = Insert(ele, NULL);
                t->left->isBottom = 0;
            }
            n.type = 0;
            n.t = t;
            PushN(n); // 0代表已经造出来树了，存入树
        }
    }
    else
    {
        if (sTop == -1)
            PushS(sign);
        else
        {
            while (sTop != -1 && Pri[signStack[sTop]] >= Pri[sign] && signStack[sTop] != L_BRA)
            {
                ele.op = PopS();
                t = Insert(ele, NULL);
                t->isBottom = 1;
                if ((top = PopN()).type == 0)
                    t->right = top.t;
                else
                {
                    ele.num = top.num;
                    t->right = Insert(ele, NULL);
                    t->right->isBottom = 0;
                }
                if ((bottom = PopN()).type == 0)
                    t->left = bottom.t;
                else
                {
                    ele.num = bottom.num;
                    t->left = Insert(ele, NULL);
                    t->left->isBottom = 0;
                }
                n.type = 0;
                n.t = t;
                PushN(n);
            }
            PushS(sign);
        }
    }
}

enum OPERATOR PopS()
{
    return signStack[sTop--];
}

struct VALUE PopN()
{
    return numStack[nTop--];
}

void PushS(enum OPERATOR s)
{
    signStack[++sTop] = s;
}

void PushN(struct VALUE v)
{
    numStack[++nTop] = v;
}