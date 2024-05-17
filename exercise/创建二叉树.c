#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点
struct Node
{
    int data;           // 结点数据
    struct Node *left;  // 左子节点指针
    struct Node *right; // 右子节点指针
};
// 创建新的结点
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
// 按层次遍历顺序插入结点
struct Node *insertNode1(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    struct Node *queue[100]; // 假设二叉树最多有100个结点
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        struct Node *current = queue[front++];

        if (current->left == NULL)
        {
            current->left = createNode(data);
            return root;
        }
        else
        {
            queue[rear++] = current->left;
        }

        if (current->right == NULL)
        {
            current->right = createNode(data);
            return root;
        }
        else
        {
            queue[rear++] = current->right;
        }
    }

    return root;
}
// 二叉排序树的插入（其实也类似一种中序遍历）
//  插入结点
struct Node *insertNode2(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data < root->data)
    {
        root->left = insertNode2(root->left, data);
    }
    else
    {
        root->right = insertNode2(root->right, data);
    }

    return root;
}
// 先序遍历的顺序创建二叉树
struct Node *insertNode3(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data == -1)
    {
        return NULL;
    }

    root->left = insertNode3(root->left, data);
    root->right = insertNode3(root->right, data);

    return root;
}
/*main函数里
    int preOrder[] = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
    //-1表示null
    int size = sizeof(preOrder) / sizeof(preOrder[0]);

    struct Node* root = NULL;

    for (int i = 0; i < size; i++) {
        root = insertNode(root, preOrder[i]);
    }
*/
// 遍历二叉树（前序）
void preOrderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}
void InOrder(struct Node *T) // 中序输出
{
    if (!T)
        return;
    InOrder(T->left);
    printf("%d ", T->data);
    InOrder(T->right);
}
void layerorder(struct Node * t) // 按层次
{
    struct Node * queue[100], *p;
    int front, rear;
    if (t != NULL)
    {
        queue[0] = t;
        front = 0;
        rear = 0;
        while (front <= rear)
        { /* 若队列不空 */
            p = queue[front++];
            printf("%d ",p->data);            /* 访问p指结点 */
            if (p->left != NULL) /* 若左孩子非空 */
                queue[++rear] = p->left;
            if (p->right != NULL) /* 若右孩子非空 */
                queue[++rear] = p->right;
        }
    }
}
int main()
{
    struct Node *root = NULL;

    // 插入数据
    root = insertNode1(root, 50);
    root = insertNode1(root, 30);
    root = insertNode1(root, 20);
    root = insertNode1(root, 40);
    root = insertNode1(root, 70);
    root = insertNode1(root, 60);
    root = insertNode1(root, 80);

    // 前序遍历输出二叉树
    printf("前序遍历结果: ");
    preOrderTraversal(root);
    printf("\n");
    printf("中序遍历结果: ");
    InOrder(root);
    printf("\n");
    printf("层次遍历结果: ");
    layerorder(root);
    printf("\n");

    return 0;
}
