#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define maxSize 20

typedef struct StackNode {
    char data[maxSize];
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, char data[]) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    strncpy(newNode->data, data, maxSize);
    newNode->next = stack->top;
    stack->top = newNode;
}

char* pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack is empty.\n");
        return NULL;
    }

    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    char* poppedData = strdup(temp->data);
    free(temp);
    return poppedData;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

char* infixToPrefix(char expression[]) {
    int length = strlen(expression);
    Stack* stack = createStack();

    for (int i = length - 1; i >= 0; i--) {
        if (isalnum(expression[i])) {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = expression[i];
            operand[1] = '\0';
            push(stack, operand);
        } else if (isOperator(expression[i])) {
            char* operand1 = pop(stack);
            char* operand2 = pop(stack);

            char* newExpression = (char*)malloc((strlen(operand1) + strlen(operand2) + 4) * sizeof(char));
            strcpy(newExpression, "(");
            strcat(newExpression, operand1);
            strncat(newExpression, &expression[i], 1);
            strcat(newExpression, operand2);
            strcat(newExpression, ")");

            push(stack, newExpression);

            free(operand1);
            free(operand2);
        }
    }

    char* infixExpression = pop(stack);
    free(stack);

    return infixExpression;
}

int main() {
    char expression[maxSize] = "+-*abc/defg";
    char* infixExpression = infixToPrefix(expression);

    printf("Infix Expression: %s\n", infixExpression);

    free(infixExpression);

    return 0;
}
