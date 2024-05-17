#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Stack {
    char** data;
    int top;
    int capacity;
} Stack;

Stack* create_stack(int capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->data = (char**) malloc(capacity * sizeof(char*));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int is_empty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char* item) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = item;
}

char* pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack underflow\n");
        return NULL;
    }
    return stack->data[stack->top--];
}

int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

char* postfix_to_infix(const char* postfix) {
    Stack* stack = create_stack(strlen(postfix));
    for (int i = 0; postfix[i]; ++i) {
        if (isalnum(postfix[i])) {
            char* operand = (char*) malloc(2 * sizeof(char));
            operand[0] = postfix[i];
            operand[1] = '\0';
            push(stack, operand);
        } else if (is_operator(postfix[i])) {
            char* right_operand = pop(stack);
            char* left_operand = pop(stack);
            int length = strlen(left_operand) + strlen(right_operand) + 4;
            char* expr = (char*) malloc(length * sizeof(char));
            snprintf(expr, length, "(%s%c%s)", left_operand, postfix[i], right_operand);
            push(stack, expr);
            free(left_operand);
            free(right_operand);
        }
    }
    char* infix = pop(stack);
    free(stack->data);
    free(stack);
    return infix;
}

int main() {
    const char* postfix = "3x95/6-*+";
    printf("Postfix: %s\n", postfix);
    char* infix = postfix_to_infix(postfix);
    printf("Infix: %s\n", infix);
    free(infix);
    return 0;
}
