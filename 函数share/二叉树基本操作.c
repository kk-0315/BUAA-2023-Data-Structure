
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 创建二叉树
TreeNode* createTree() {
    int val;
    scanf("%d", &val);
    if (val == -1) {
        return NULL;
    }
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = val;
    root->left = createTree();
    root->right = createTree();
    return root;
}

// 前序遍历
void preOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

// 中序遍历
void inOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

// 后序遍历
void postOrder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->val);
}

// 计算二叉树的深度
int maxDepth(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}

// 计算二叉树的节点个数
int countNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return countNodes(root->left) + countNodes(root->right) + 1;
}

// 计算二叉树的叶子节点个数
int countLeaves(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}

// 判断两棵二叉树是否相同
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == NULL && q == NULL) {
        return true;
    }
    if (p == NULL || q == NULL) {
        return false;
    }
    if (p->val != q->val) {
        return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// 判断一棵二叉树是否是另一棵二叉树的子树
bool isSubtree(TreeNode* s, TreeNode* t) {
    if (s == NULL) {
        return false;
    }
    if (isSameTree(s, t)) {
        return true;
    }
    return isSubtree(s->left, t) || isSubtree(s->right, t);
}

// 翻转二叉树
TreeNode* invertTree(TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }
    TreeNode* left = invertTree(root->left);
    TreeNode* right = invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}

// 二叉树的最近公共祖先
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL || root == p || root == q) {
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }
    return root;
}

//定义线索二叉树结点结构体
typedef struct ThreadNode{
    int data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag; //左右线索标志
}ThreadNode, *ThreadTree;

//全局变量，始终指向刚刚访问过的结点
ThreadNode *pre;

//构造中序线索二叉树
void InThread(ThreadTree p){
    if(p){
        InThread(p->lchild); //递归左子树线索化
        if(!p->lchild){ //如果左子树为空，建立前驱线索
            p->lchild = pre;
            p->ltag = 1;
        }
        if(!pre->rchild){ //如果前驱结点的右子树为空，建立后继线索
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p; //保持pre指向p的前驱
        InThread(p->rchild); //递归右子树线索化
    }
}

//构造中序线索二叉树的主函数
void CreateInThread(ThreadTree T){
    pre = NULL; //初始化pre
    if(T){
        InThread(T); //中序线索化二叉树
        if(!pre->rchild){ //处理最后一个结点
            pre->rchild = NULL;
            pre->rtag = 1;
        }
    }
}
