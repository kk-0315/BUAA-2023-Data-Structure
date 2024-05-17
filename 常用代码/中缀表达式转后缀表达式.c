#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Node {
    char ch;
    struct Node *next;
} Node, *LinkNode;
 
typedef struct LinkStack {
    LinkNode top;
    int count;
} LinkStack;
 
//初始化栈
void InitStack(LinkStack *stack) {
    stack->top = NULL;
    stack->count = 0;
}
 
//判断字符是否为数字
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}
 
//压栈
void Push(LinkStack *s, char ch) {
    LinkNode node = (LinkNode) malloc(sizeof(Node));
    node->ch = ch;
    node->next = s->top;
    s->top = node;
    s->count++;
}
 
//得到栈顶元素，但不出栈
char GetPop(LinkStack s) {
    return s.top->ch;
}
 
//出栈
char Pop(LinkStack *s) {
    LinkNode node = s->top;
    char ch = node->ch;
    s->top = node->next;
    free(node);
    s->count--;
    return ch;
}
 
//输出栈中所有元素
void PopAll(LinkStack *s) {
    int n = s->count;
    for (int i = 0; i < n; ++i) {
        printf("%c ", Pop(s));
    }
}
 
//中缀表达式转后缀表达式
void Infixtosuffix(char *str, LinkStack stack) {
 
    for (int i = 0; i < strlen(str); ++i) {
        char ch = str[i];
        //如果是左括号，直接入栈
        if (ch == '(') {
            Push(&stack, ch);
        }
            //如果是数字，则输出数字
        else if (isDigit(ch)) {
            if (isDigit(str[i + 1]) && i != strlen(str) - 1) {
                printf("%c", ch);
            } else {
                printf("%c ", ch);
            }
        }
            //如果是乘除符号，除非遇到栈顶为'+'， '-'， '(' 外进栈，否则遇到栈顶为'*'，'/' 时，栈顶出栈
        else if (ch == '*' || ch == '/') {
            while (stack.count) {
                char topch = GetPop(stack);
                if (topch == '+' || topch == '-' || topch == '(') {
                    break;
                } else {
                    char outch = Pop(&stack);
                    printf("%c ", outch);
                }
            }
            Push(&stack, ch);
        }
            //如果是加减符号，除非栈顶遇到'('，否则栈顶出栈
        else if (ch == '+' || ch == '-') {
            while (stack.count) {
                char topch = GetPop(stack);
                if (topch == '(') {
                    break;
                } else {
                    char outch = Pop(&stack);
                    printf("%c ", outch);
                }
            }
            Push(&stack, ch);
        }
            //如果是右括号，除非栈顶遇到'('，否则栈顶出栈
        else if (ch == ')') {
            while (stack.count) {
                char topch = GetPop(stack);
                if (topch == '(') {
                    Pop(&stack);
                    break;
                } else {
                    char outch = Pop(&stack);
                    printf("%c ", outch);
                }
            }
        }
    }
    //遍历完后，弹出栈中所有元素
    PopAll(&stack);
}
 
 
int main() {
    LinkStack stack;
    InitStack(&stack);
    char *str = "1*(2+3)-(4+5)";
    Infixtosuffix(str, stack);
    
}