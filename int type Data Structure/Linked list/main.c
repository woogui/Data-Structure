#include"list.h"
#include<stdio.h>
#define MAX 100000
int main(){
	LIST list = { NULL, };
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
	for (int i = 0; i < MAX; i++){
		push_back(&list, a[i]);
	}
	NODE* it;

	sort(&list);
	for (it = begin(&list); it != end(&list); it = to_next(it)){
		printf("%d ", it->data);
	}
	return 0;
}