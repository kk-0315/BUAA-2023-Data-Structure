/*检查字符串s中是否包含字符串t
若包含，则返回t在s中的开始位置（下标值）
*/
//kmp算法
int index(char s[], char t[])
{
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k]!='\0' && s[j] == t[k]; j++, k++)
            ;
        if ( t[k]=='\0' )
            return i;
    }
    return -1;
}