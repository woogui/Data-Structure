#include"vector.h"
#include<stdio.h>
#define MAX 100
int main(){
	VECTOR v = newVECTOR(sizeof(int));
	int a[MAX];
	int b = 200;
	for (int i = 0; i < MAX; i++)
		a[i] = i;

	for (int i = 0; i < MAX; i++)
		push_back(&v, &a[i]);

	void* it;
	for (it = begin(&v); it != end(&v); it = to_next(&v, it)){
		printf("%d ", *(int*)it);
	}
	return 0;
}