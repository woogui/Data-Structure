#include"BST.h"
#include<stdio.h>
#define MAX 10000
int main(){
	TREE tree = { NULL, };
	int a[MAX];
	for (int i = 0; i < MAX; i++){
		a[i] = i;
	}
	for (int i = 0; i < MAX; i++){
		int r = rand() % MAX;
		int tmp = a[r];
		a[r] = a[i];
		a[i] = tmp;
	}

	for (int i = 0; i < MAX; i++)
		insert(&tree, a[i]);
	NODE* it;
	for (it = rbegin(&tree); it != rend(&tree); it = to_prev(it)){
		printf("%d ", it->key);
	}

	return 0;
}