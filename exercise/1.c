#include <stdio.h>
#include <stdlib.h>
struct Tree
{
    int val; /* data */
    struct Tree *left;
    struct Tree *right;
};
typedef struct Tree tree, *TREE;
char c;
int num = 0;
int find(TREE root);
void dfs(TREE root,int height,int *curheight,int *curval);
struct Tree *createTree(int data);
struct Tree *insertTree1(struct Tree *root, int data);
int main()
{
    
    TREE root;
    
    
    while (scanf("%c", &c) != ']')
    {
        num=0;
        if (c >= '0' && c <= '9')
        {
            while (c >= '0' && c <= '9')
            {
                num = num * 10 + c - '0';
                scanf("%c", &c);
            }
            root=insertTree1(root,num);
        }
      
        
    }
    
    printf("%d",find(root));
    
}
int find(TREE root)
{
    int curheight=0,curval=0;
    dfs(root,0,&curheight,&curval);
    return curval;
}
void dfs(TREE root,int height,int *curheight,int *curval)
{
    if(root->val==-1)
    return ;
    height++;
    dfs(root->left,height,curheight,curval);
    dfs(root->right,height,curheight,curval);
    if(height>*curheight)
    {
        *curheight=height;
        *curval=root->val;
    }
}
// 创建新的结点
struct Tree *createTree(int data)
{
    struct Tree *newTree = (struct Tree *)malloc(sizeof(struct Tree));
    if (newTree == NULL)
    {
        printf("内存分配失败\n");
        exit(1);
    }

    newTree->val = data;
    newTree->left = NULL;
    newTree->right = NULL;

    return newTree;
}
// 按层次遍历顺序插入结点
struct Tree *insertTree1(struct Tree *root, int data)
{
    if (root == NULL)
    {
        return createTree(data);
    }

    struct Tree *queue[100]; // 假设二叉树最多有100个结点
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        struct Tree *current = queue[front++];

        if (current->left == NULL)
        {
            current->left = createTree(data);
            return root;
        }
        else
        {
            queue[rear++] = current->left;
        }

        if (current->right == NULL)
        {
            current->right = createTree(data);
            return root;
        }
        else
        {
            queue[rear++] = current->right;
        }
    }

    return root;
} 
