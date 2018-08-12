#include"heap.h"
#include<stdio.h>
#define MAX 10
int main(){
	HEAP h = { NULL, };
	int a[MAX];
	for (int i = 0; i < MAX; i++){
		a[i] = i;//rand() % (MAX * 10);
	}
	for (int i = 0; i < MAX; i++){
		int r = rand() % MAX;
		int tmp = a[r];
		a[r]  = a[i];
		a[i] = tmp;
	}
	for (int i = 0; i < MAX; i++){
		insert(&h, a[i]);
	}
	
	for (int i = 0; i < MAX; i++){
		printf("%d ", *h.base);
		erase(&h);
	}
	return 0;
}