//定义栈结构体
typedef struct Stack{
    int *data; //存储数据的数组
    int top; //栈顶指针
    int size; //栈的大小
}Stack;

//初始化栈
void initStack(Stack *s, int size){
    s->data = (int*)malloc(sizeof(int)*size);
    s->top = -1;
    s->size = size;
}

//判断栈是否为空
int isEmpty(Stack *s){
    return s->top == -1;
}

//判断栈是否已满
int isFull(Stack *s){
    return s->top == s->size - 1;
}

//入栈
void push(Stack *s, int x){
    if(isFull(s)){
        printf("Stack is full!\n");
        return;
    }
    s->data[++s->top] = x;
}

//出栈
int pop(Stack *s){
    if(isEmpty(s)){
        printf("Stack is empty!\n");
        return -1;
    }
    return s->data[s->top--];
}

//获取栈顶元素
int getTop(Stack *s){
    if(isEmpty(s)){
        printf("Stack is empty!\n");
        return -1;
    }
    return s->data[s->top];
}

//销毁栈
void destroyStack(Stack *s){
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->size = 0;
}
