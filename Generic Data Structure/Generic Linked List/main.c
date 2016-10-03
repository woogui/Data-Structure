#include"list.h"
#include<stdio.h>
#define MAX 100
int main(){
	LIST list = newLIST(sizeof(int));
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
		push_back(&list, &a[i]);
	}
	void* it;
	sort(&list);
	for (it = begin(&list); it != end(&list); it = to_next(it)){
		printf("%d ", *(NODE*)it);
	}
	return 0;
}