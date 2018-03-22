#include <stdio.h>

void meragesort(int *arr, int n);
void meragepass(int *init_list, int *merage_list, int n, int s);
void merage(int *init_list, int *merage_list, int i, int m, int n);
void print(int *arr);

int arr[8] = { 22,25,7,3,30,3,14,7 };

void main() {
	print(arr);
	meragesort(arr, 8);
	print(arr);
}
/* 
purpose: sorting the array 
input: int arr input num
output: none */
void meragesort(int *arr, int n) {
	int s = 1;
	int extra[10];

	while (s < n) {
		meragepass(arr, extra, n, s);
		s *= 2;
		meragepass(extra, arr, n, s);
		s *= 2;
		print(arr); 
	}
}
/*purpose:  perform one pass
input: int init array, int result array, int number of index in array,int size of sublist
output:none*/
void meragepass(int *init_list, int *merage_list, int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merage(init_list, merage_list, i, i + s - 1, i + 2 * s - 1);
	if (i + s - 1 < n)
		merage(init_list, merage_list, i, i + s - 1, n);
	else
		for (j = i; j <= n; j++)
			merage_list[j] = init_list[j];
}
/*
purpose: merge two array
input: int init array, int result array int index ,int last index of sublist,int last index of sublist
output: none*/
void merage(int *init_list, int *merage_list, int i, int m, int n) {
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (init_list[i] <= init_list[j])
			merage_list[k++] = init_list[i++];
		else
			merage_list[k++] = init_list[j++];
	}
	if (i > m) {
		for (t = j; t <= n; t++)
			merage_list[t] = init_list[t];
	}
	else
		for (t = i; t <= m; t++)
			merage_list[k + t - i] = init_list[t];


}

/*
Purpose: to print all of number in insertion array
Input: int array
Ouptut: none
*/

void print(int *arr) {
	for (int i = 0; i < 8; i++) {
		printf("%d ", arr[i]);
		
	}
	printf("\n\n");
}
