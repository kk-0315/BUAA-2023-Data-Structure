#include<stdio.h>
#include<stdlib.h>

struct NODE{
    int x1;
    int y1;
    int x2;
    int y2;
    int mode;
} Line[120];

int cmp(const void *str1, const void *str2){
    struct NODE A = *(struct NODE *)str1, B = *(struct NODE *)str2;
    return A.x1 - B.x1;
}

int main()
{
    int n, i, j;
    int MaxNum = 0, MaxStart = 0, TmpNum, TmpStart, TmpLast;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%d%d%d", &Line[i].x1, &Line[i].y1, &Line[i].x2, &Line[i].y2);
    }
    qsort(Line, n, sizeof(struct NODE), cmp);

    for (i = 0; i < n; i++)
    {
        
        TmpNum = 1;
        TmpStart = i;
        TmpLast = i;
        Line[i].mode = 1;
        for (j = i+1; j < n; j++)
        {
            if (Line[j].mode != 1 && Line[TmpLast].x2 == Line[j].x1 && Line[TmpLast].y2 == Line[j].y1)
            {
                TmpLast = j;
                TmpNum++;
                Line[j].mode = 1;
            }
        }
        if (TmpNum > MaxNum)
        {
            MaxNum = TmpNum;
            MaxStart = TmpStart; 
        }
    }
    printf("%d %d %d", MaxNum, Line[MaxStart].x1, Line[MaxStart].y1);
    return 0;
}

