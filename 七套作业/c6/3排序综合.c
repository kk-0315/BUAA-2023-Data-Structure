//排序综合
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int num[105], num_1[105], num_2[105], num_3[105], num_4[105], num_5[105];
int count;
//选择排序（选最小值）
void selectSort(int array[], int n);
//冒泡排序
void bubbleSort(int k[], int n);
//堆排序
void heapSort(int k[], int n);
void adjust(int k[], int i, int n);
//二路归并排序
void mergeSort(int k[], int n);
void mSort(int k[], int tmp[], int left, int right);
void merge(int x[], int tmp[], int left, int leftend, int rightend);
//快速排序
void quick(int k[], int left, int right);
void quickSort(int k[], int n);
void swap(int v[], int i, int j);

int main()
{
    int n, op;
    scanf("%d %d", &n, &op);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }

    if (op == 1)
    {
        for (int i = 0; i < n; i++)
            num_1[i] = num[i];
        selectSort(num_1, n);
        for (int i = 0; i < n; i++)
            printf("%d ", num_1[i]);
        printf("\n");
        printf("%d", count);
    }
    else if (op == 2)
    {
        for (int i = 0; i < n; i++)
            num_2[i] = num[i];

        bubbleSort(num_2, n);
        for (int i = 0; i < n; i++)
            printf("%d ", num_2[i]);
        printf("\n");
        printf("%d", count);
    }
    else if (op == 3)
    {
        for (int i = 0; i < n; i++)
            num_3[i] = num[i];
        heapSort(num_3, n);
        for (int i = 0; i < n; i++)
            printf("%d ", num_3[i]);
        printf("\n");
        printf("%d", count);
    }
    else if (op == 4)
    {
        for (int i = 0; i < n; i++)
            num_4[i] = num[i];
        mergeSort(num_4, n);
        for (int i = 0; i < n; i++)
            printf("%d ", num_4[i]);
        printf("\n");
        printf("%d", count);
    }
    else
    {
        for (int i = 0; i < n; i++)
            num_5[i] = num[i];
        quickSort(num_5, n);
        for (int i = 0; i < n; i++)
            printf("%d ", num_5[i]);
        printf("\n");
        printf("%d", count);
    }
}
void selectSort(int k[], int n)
{
    int i, j, d;
    int temp;
    for (i = 0; i < n - 1; i++)
    {
        d = i;
        for (j = i + 1; j < n; j++)
        {
            count++;
            if (k[j] < k[d])
                d = j;
        }
        if (d != i)
        {
            /* 最小值元素非未排序元素的第一个元素时 */
            temp = k[d];
            k[d] = k[i];
            k[i] = temp;
        }
    }
}

void bubbleSort(int k[], int n)
{
    int i, j, flag = 1;
    int temp;
    for (i = n - 1; i > 0 && flag == 1; i--)
    {
        flag = 0; /* 每趟排序前标志flag置0 */
        for (j = 0; j < i; j++)
        {
            count++;
            if (k[j] > k[j + 1])
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
void heapSort(int k[], int n)
{
    int i;
    int temp;
    for (i = n / 2 - 1; i >= 0; i--)
        adjust(k, i, n);
    for (i = n - 1; i >= 1; i--)
    {
        temp = k[i];
        k[i] = k[0];
        k[0] = temp;
        adjust(k, 0, i);
    }
}
void adjust(int k[], int i, int n)
{
    int j, temp;
    temp = k[i];
    j = 2 * i + 1;
    while (j < n)
    {
        count++;
        if (j < n - 1 && k[j] < k[j + 1])
            j++;
        if (temp >= k[j])
            break;
        k[(j - 1) / 2] = k[j];
        j = 2 * j + 1;
    }
    k[(j - 1) / 2] = temp;
}
void mergeSort(int k[], int n)
{
    int *tmp;
    tmp = (int *)malloc(sizeof(int) * n);
    if (tmp != NULL)
    {
        mSort(k, tmp, 0, n - 1);
        free(tmp);
    }
}
void mSort(int k[], int tmp[], int left, int right)
{
    int center;
    if (left < right)
    {
        center = (left + right) / 2;
        mSort(k, tmp, left, center);
        mSort(k, tmp, center + 1, right);
        merge(k, tmp, left, center, right);
    }
}
void merge(int x[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left;
    while (i <= leftend && j <= rightend)
    {
        count++;
        if (x[i] <= x[j])
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
}
void quickSort(int k[], int n)
{
    quick(k, 0, n - 1);
}

void quick(int k[], int left, int right)

{

    int i, last;
    if (left < right)
    {
        last = left;
        for (i = left + 1; i <= right; i++)
        {
            count++;
            if (k[i] < k[left])
                swap(k, ++last, i);
        }
        swap(k, left, last);
        quick(k, left, last - 1);
        quick(k, last + 1, right);
    }
}
void swap(int v[], int i, int j)
{
    int tmp;
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
