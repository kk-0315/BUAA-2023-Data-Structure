/*可以使结果为小数的+-* /()计算器*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum SYMBOL {OP, NUM, ELSE, EQ};
enum OPERATOR {ADD, SUB, DIV, MUL, L_BRA, R_BRA};//分别赋值0123...
int Pri[] = {0,0,1,1,2,3};//!规定优先级

enum OPERATOR signStack[300];
int sTop = -1;
double numStack[300];
int nTop = -1;


union ELEMENT//联合体就是有的时候可以是一种类型，有的时候是另一种类型
{
    
    double num;
    enum OPERATOR op;
};


enum SYMBOL IdentifySym(union ELEMENT *item);//同时改变item的值
double Compute(double top, double bottom, enum OPERATOR);//返回结果
void Operator(enum OPERATOR);//后缀表达式逻辑判断, 符号入栈并进行一系列计算


enum OPERATOR PopS();//仅移动栈顶,数据直接覆盖
double PopN();

void PushS(enum OPERATOR);
void PushN(double);

int main()
{
    enum SYMBOL sym;
    union ELEMENT item;
    double top, bottom;
    enum OPERATOR op;
    while((sym=IdentifySym(&item)) != EQ)//判断读入的是什么
    {
        if (sym == OP)//是运算符，进行操作
        {
            Operator(item.op);
        }
        else if (sym == NUM)
        {
            PushN(item.num);
        }
    }
    if (sTop != -1)
    {
        while (nTop)
        {
            top = PopN();
            bottom = PopN();
            op = PopS();
            item.num = Compute(top, bottom, op);
           
            PushN(item.num);
        }
    }
    printf("%.2lf", PopN());
}

enum SYMBOL IdentifySym(union ELEMENT * s)
{
    char c;
    double n;
    while ((c=getchar()) != '='){
        if (c>='0' && c<='9')
        {
            for (n=0; c>='0' && c<='9'; c=getchar())
                n = n*10 + (double)(c-'0');
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
                default :
                    continue;
            }
        }
    }
    return EQ;
}

double Compute(double top, double bottom, enum OPERATOR sign)
{
    switch (sign)
    {
        case ADD:
            return top + bottom;
        case SUB:
            return bottom - top;
        case DIV:
            return bottom / top;
        case MUL:
            return bottom * top;
    }
}

void Operator(enum OPERATOR sign)
{
    double n = 0, top, bottom;
    enum OPERATOR op;
    if (sign == R_BRA)
    {
        for (op=PopS(); op!=L_BRA; op=PopS())
        {
            top = PopN();
            bottom = PopN();
            n = Compute(top, bottom, op);
            
            PushN(n);
        }
    }
    else
    {
        if (sTop == -1)
            PushS(sign);
        else
        {
            //!注意这里第一个判断条件, 循环pop可能导致stop出现-1,如果不加这个就会越界访问[-1]
            //!并且这个错误不会报错! 越界访问时会直接终止循环, 这个错误非常隐蔽
            while (sTop != -1 && Pri[signStack[sTop]] >= Pri[sign] && signStack[sTop] != L_BRA)
            {
                op = PopS();
                top = PopN();
                bottom = PopN();
                n = Compute(top, bottom, op);
                
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

double PopN()
{
    
    return numStack[nTop--];
}

void PushS(enum OPERATOR s)
{
    signStack[++sTop] = s;
}

void PushN(double num)
{
    numStack[++nTop] = num;
}