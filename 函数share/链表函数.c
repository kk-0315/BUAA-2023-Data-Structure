
//定义链表节点结构体
typedef struct Node{
    int data; //数据域
    struct Node *next; //指针域
}Node;

//创建链表
Node* createList(int n){
    Node *head, *p, *q;
    head = (Node*)malloc(sizeof(Node)); //创建头节点
    head->next = NULL; //头节点指针域为空
    q = head; //q指向头节点
    for(int i=0; i<n; i++){
        p = (Node*)malloc(sizeof(Node)); //创建新节点
        scanf("%d", &p->data); //输入新节点数据
        p->next = NULL; //新节点指针域为空
        q->next = p; //将新节点插入到链表尾部
        q = p; //q指向新节点
    }
    return head; //返回头节点
}

//插入节点
Node* insertNode(Node *head, int pos, int data){
    Node *p, *q;
    p = (Node*)malloc(sizeof(Node)); //创建新节点
    p->data = data; //新节点数据域为data
    p->next = NULL; //新节点指针域为空
    q = head; //q指向头节点
    for(int i=0; i<pos-1; i++){
        q = q->next; //q指向要插入位置的前一个节点
    }
    p->next = q->next; //将新节点插入到链表中
    q->next = p;
    return head; //返回头节点
}

//删除节点
Node* deleteNode(Node *head, int pos){
    Node *p, *q;
    p = head; //p指向头节点
    for(int i=0; i<pos-1; i++){
        p = p->next; //p指向要删除位置的前一个节点
    }
    q = p->next; //q指向要删除的节点
    p->next = q->next; //将要删除的节点从链表中删除
    free(q); //释放要删除的节点的内存空间
    return head; //返回头节点
}

//修改节点
Node* modifyNode(Node *head, int pos, int data){
    Node *p;
    p = head; //p指向头节点
    for(int i=0; i<pos; i++){
        p = p->next; //p指向要修改的节点
    }
    p->data = data; //修改节点数据域为data
    return head; //返回头节点
}

//查找节点
int searchNode(Node *head, int data){
    Node *p;
    p = head->next; //p指向第一个节点
    int pos = 1; //记录节点位置
    while(p != NULL){
        if(p->data == data){ //找到节点
            return pos;
        }
        p = p->next; //p指向下一个节点
        pos++; //位置加1
    }
    return -1; //未找到节点
}
