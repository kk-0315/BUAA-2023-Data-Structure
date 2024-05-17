#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD  200
typedef struct tnode {
    char word[MAXWORD];
    int count;
    struct tnode *left,*right;
}node,*BST; //BST,单词树结构
int getword(FILE *in,char *w);
struct tnode *addtree(struct tnode *p,char *w);
void treeprint( struct tnode *p);
void TurnRight(BST t, int num);
char word1[MAXWORD];
int main()
{

    FILE *in;
    in = fopen("article.txt", "r");
    BST root=NULL; //BST树根节点指针
    while( 1 ) //从文件中读入一个单词
         {
            int state=getword(in,word1);
            if(strlen(word1)!=0)//当且仅当传入word不为空再插入，不然可能会出现单词为空，打印“ 1”的情况
            root = addtree(root, word1);
            for(int i=0;i<200;i++)
            word1[i]=0;
            if(state==EOF)
            break;
         }
    TurnRight(root,3);

    treeprint(root);  //遍历输出单词树
    return 0;
} 
int getword(FILE *in,char *w)
{
    int q = 0;
    char c;
    A:
        while ((c = fgetc(in)) != EOF)
        {
            if (c >= 'A' && c <= 'Z')
            {
                c = 'a' - 'A' + c;
            }
            if (c >= 'a' && c <= 'z')
                w[q++] = c;
            else
                break;
        }
        if (q == 0 && c != EOF)
            goto A;
        if (c == EOF)
            return EOF;
        else
        return 0;
}
BST addtree(BST p,char *w)
{
    if(p == NULL){
        p = (BST)malloc(sizeof(node));
        strcpy(p->word,w);
        p->left = p->right = NULL;
        p->count=1;
    } 
    else if( strcmp(w,p->word)<0)
        p->left = addtree(p->left, w);
    else if( strcmp(w,p->word)>0)
       p->right = addtree(p->right,w);
    else   
       p->count++; //树中存在该元素
    return p;

}
void treeprint(BST p)
{
    if(p!=NULL){
    treeprint(p->left);
    printf("%s %d\n",p->word,p->count);
    treeprint(p->right);}
}
void TurnRight(BST t, int num)
{
    if((t->right==NULL&&num>=1)||(num==1&&t!=NULL))
    printf("%s\n", t->word);
    else if (t!=NULL && num!=0)
    {
        printf("%s ", t->word);
        TurnRight(t->right, --num);
    }
    
}