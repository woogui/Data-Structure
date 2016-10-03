#include"stack.h"
#include<stdio.h>
#define MAX 100
int main(){
	STACK stack = newSTACK(sizeof(int));
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
	printf("%d\n", is_empty(&stack));
	for (int i = 0; i < MAX; i++){
		push(&stack, &a[i]);
	}
	printf("%d\n", is_empty(&stack));
	while (top(&stack)){
		printf("%d ", *(int*)pop(&stack));
	}
	printf("\n%d\n", is_empty(&stack));
	return 0;
}