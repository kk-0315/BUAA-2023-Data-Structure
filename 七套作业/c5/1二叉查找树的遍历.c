#include <stdio.h>
#include<stdlib.h>
typedef int Datatype;
struct node {
    Datatype data;
    int depth;
    struct node *left, *right;
};
int h,count=0;
typedef struct node BTNode, *BTNodeptr;
BTNodeptr  insertBST(BTNodeptr p, Datatype item);
void PostOrder(BTNodeptr T);
BTNodeptr  searchBST(BTNodeptr t,Datatype  key);
int main()
{
    int i, item,num;
    BTNodeptr  root=NULL,t=NULL;

    scanf("%d",&num);
    for(i=0; i<num; i++){ //构造一个有10个元素的BST树
         h=1;
         scanf("%d", &item);
         root = insertBST(root, item);
         
     }
    
    PostOrder(root);
    return 0;
}
BTNodeptr  insertBST(BTNodeptr p, Datatype item)
{
    if(p == NULL){
        p = (BTNodeptr)malloc(sizeof(BTNode));
        p->data = item;
        p->left = p->right = NULL;
        p->depth=h;
    } 
    else if( item < p->data){
        h++;
        p->left = insertBST(p->left, item);
        }
    else if( item >= p->data){
        h++;
       p->right = insertBST(p->right,item);
       }
    
    return p;
} 
void PostOrder(BTNodeptr T)//后序输出
{
    if(T->left!=NULL)
    PostOrder(T->left);
    if(T->right!=NULL)
    PostOrder(T->right);
    if(T->left==NULL&&T->right==NULL)
    printf("%d %d\n",T->data,T->depth);
    
}

BTNodeptr  searchBST(BTNodeptr t,Datatype  key)
{
      BTNodeptr  p=t;
      while(p!=NULL){
             if(key == p->data)  
                  {
                    count++;
                    return p;
                  }               /* 查找成功 */
             if(key > p->data)
                  {
                    p=p->right; 
                    count++;
                  }       /* 将p移到右子树的根结点 */
             else
                  {
                    p=p->left; 
                    count++;
                  }       /* 将p移到左子树的根结点 */
       }
       return NULL;                 /* 查找失败 */
}
