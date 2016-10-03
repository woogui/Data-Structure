#include"BST.h"
#include<stdio.h>
#define MAX 100
int main(){
	TREE tree = newTREE(sizeof(int));
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
		insert(&tree, &a[i]);

	void* it;
	for (it = begin(&tree); it != end(&tree); it = to_next(it)){
		printf("%d ", *(int*)it);
	}
	clear(&tree);

	return 0;
}