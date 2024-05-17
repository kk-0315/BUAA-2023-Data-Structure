int max(x,y) 
{ if(x >y)  return x; else return y; }
int  heightTree(BiTree  p)
{
    if(p == NULL)
        return 0;
    else
        return 1 + max(heightTree(p->left), 
                                 heightTree(p->right));
 }     //计算树的高度


