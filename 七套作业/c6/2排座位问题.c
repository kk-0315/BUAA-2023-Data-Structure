#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define max(a, b) ((a > b) ? (a) : (b))
#define min(a, b) ((a < b) ? (a) : (b))
struct info
{
    char no[20]; // 学号
    char name[20];
    int sit_no; // 座位号
    int flag;
} list[105];
int miss[105];

int MAX, MAX1;
void stable_sort(struct info k[], int n);
void find_miss(struct info k[], int n);
void find_repeat(struct info k[], int n);
void sort(struct info k[], int n);
int main()
{
    FILE *in, *out;
    in = fopen("in.txt", "r");
    out = fopen("out.txt", "w");

    for (int i = 0; i < 105; i++)
    {
        list[i].flag = 0;
        list[i].sit_no = 0;
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(in, " %s", list[i].no);
        fscanf(in, " %s", list[i].name);
        fscanf(in, " %d\n", &list[i].sit_no);
    }

    stable_sort(list, n);
    find_miss(list, n);

    find_repeat(list, n);
    sort(list, n);

    for (int i = 0; i < n; i++)
    {
        fprintf(out, "%s ", list[i].no);
        fprintf(out, "%s ", list[i].name);
        fprintf(out, "%d\n", list[i].sit_no);
    }
}
void stable_sort(struct info k[], int n)
{
    int i, j, flag = 1;
    struct info temp;
    for (i = n - 1; i > 0 && flag == 1; i--)
    {
        flag = 0; /* 每趟排序前标志flag置0 */
        for (j = 0; j < i; j++)
        {

            if (k[j].sit_no > k[j + 1].sit_no)
            {
                temp = k[j];
                k[j] = k[j + 1];
                k[j + 1] = temp; /* 交换两个元素的位置 */
                flag = 1;        /* 标志flag置1 */
            }
        }
    }
}
void find_miss(struct info k[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (k[i].sit_no > MAX)
            MAX = k[i].sit_no;
    }
    int q = min(n, MAX);
    int p = 0;
    for (int i = 1; i <= q; i++)
    {
        int flag = 0;
        for (int j = 0; j < n; j++)
        {
            if (k[j].sit_no == i)
            {
                flag = i;
                break;
            }
        }
        if (flag == 0)
        {
            miss[p++] = i;
        }
    }

    for (int i = 0; i < p; i++)
    {
        int flag1=0;
        stable_sort(k,n);
        for(int j=0;j<=n-i-1;j++)
        {
            if(k[j+1].sit_no-k[j].sit_no>1)
            {
                flag1=1;
                break;
            }
        }
        if(flag1==1)
        k[n - 1].sit_no = miss[i];
        else
        break;
    }
}
void find_repeat(struct info k[], int n)
{

    int t = 1;
    for (int i = 0; i < n; i++)
    {
        if (k[i].sit_no > MAX1)
            MAX1 = k[i].sit_no;
    }

    for (int i = 0; i < n; i++)
    {
        if (k[i].sit_no == k[i + 1].sit_no)
        {
            k[i + 1].sit_no = MAX1 + t;
            t++;
        }
    }
}
void sort(struct info k[], int n)
{
    int i, j, flag = 1;
    struct info temp;
    for (i = n - 1; i > 0 && flag == 1; i--)
    {
        flag = 0; /* 每趟排序前标志flag置0 */
        for (j = 0; j < i; j++)
        {

            if (strcmp(k[j].no, k[j + 1].no) > 0)
            {
                temp = k[j];
                k[j] = k[j + 1];
                k[j + 1] = temp; /* 交换两个元素的位置 */
                flag = 1;        /* 标志flag置1 */
            }
        }
        if (flag == 0)
            break;
    }
}