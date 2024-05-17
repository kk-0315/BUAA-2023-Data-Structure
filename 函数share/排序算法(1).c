#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void insertSort(int k[], int n){
	int i, j;
	int temp;
	for (i = 1; i<n; i++){
		temp = k[i];
		for (j = i-1; j>=0 && temp<k[j]; j--)
			k[j+1] = k[j];
		k[j+1] = temp;
	}
}
void insertBSort(int k[], int n){
	int i, j, mid, high, low;
	int temp;
	for (i = 1; i<n; i++){
		temp = k[i];
		low = 0;
		high = i-1;
		while (low<=high){
			mid = low+(high-low)/2;
			if (temp<k[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i-1; j>=low; j--)
			k[j+1] = k[j];
		k[low] = temp;
	}
}
void selectSort(int k[], int n){
	int i, j, d;
	int temp;
	for (i = 0; i<n; i++){
		d = i;
		for (j = i+1; j<n; j++)
			if (k[j]<k[d])
				d = j;
		if (d!=i){
			temp = k[d];
			k[d] = k[i];
			k[i] = temp;
		}
	}
}
void bubbleSort(int k[], int n){
	int i, j, flag = 1;
	int temp;
	for (i = n-1; i>0 && flag==1; i--){
		flag = 0;
		for (j = 0; j<i; j++){
			if (k[j]>k[j+1]){
				temp = k[j];
				k[j] = k[j+1];
				k[j+1] = temp;
				flag = 1;
			}
		}
	}
}
void shellSort (int k[], int n){
	int i, j, flag, gap = n;
	int temp;
	while (gap>1){
		gap /= 2;
		do{
			flag = 0;
			for (i = 0; i<n-gap; i++){
				j = i+gap;
				if (k[i]>k[j]){
					temp = k[i];
					k[i] = k[j];
					k[j] = temp;
					flag = 1;
				}
			}
		}while (flag != 0);
	}
}
//堆排序
void adjust(int k[], int i, int n){
	int j;
	int temp;
	temp = k[i];
	j = 2*i+1;
	while (j<n){
		if (j<n-1 && k[j]<k[j+1])
			j ++;
		if (temp>=k[j])
			break;
		k[(j-1)/2] = k[j];
		j = j*2+1;
	}
	k[(j-1)/2] = temp;
}
void heapSort(int k[], int n){
	int i;
	int temp;
	for (i = n/2-1; i>=0; i--)
		adjust(k, i, n);
	for (i = n-1; i>=1; i--){
		temp = k[i];
		k[i] = k[0];
		k[0] = temp;
		adjust(k, 0, i);
	}
}
//二路归并
void merge(int x[],int tmp[],int left, int leftend, int rightend){
	int i = left, j = leftend+1, q = left;
	while (i<=leftend && j<=rightend)
		if (x[i]<=x[j])
			tmp[q++] = x[i++];
		else
			tmp[q++] = x[j++];
	while (i<=leftend)
		tmp[q++] = x[i++];
	while (j<=rightend)
		tmp[q++] = x[j++];
	for (int i = left; i<=rightend; i++)
		x[i] = tmp[i];
}
void mSort(int k[], int tmp[], int left, int right){
	int center;
	if (left<right){
		center = (left+right)/2;
		mSort(k, tmp, left, center);
		mSort(k, tmp, center+1, right);
		merge(k, tmp, left, center, right);
	}
}
void mergeSort(int k[], int n){
	int *tmp;
	tmp = (int *)malloc(sizeof(int )*n);
	if (tmp != NULL){
		mSort(k, tmp, 0, n-1);
		free(tmp);
	}else
		printf("NO\n");
}
//快速排序
void swap(int *a, int *b){
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
void quickSort(int k[ ],int left,int right){     
	int i, last;
	if(left<right){
		last=left; 
		for(i=left+1;i<=right;i++)
			if(k[i]<k[left])
				swap(&k[++last],&k[i]); 
		swap(&k[left],&k[last]);
		printf("\n");
		for (int i = 0; i<10; i++)
			printf("%d ",k[i]);
		printf("\n");
		quickSort(k,left,last-1); 
		quickSort(k,last+1,right);   
	}
}

int main ()
{
	int a[] = {2,12,16,30,8,28,4,10,20,6,18};
	quickSort(a,0,10);
	return 0;
}
