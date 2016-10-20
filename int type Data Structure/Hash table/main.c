#include"hash.h"
#include<stdio.h>
#include<time.h>

#define MAX 10
int arr[MAX];
int main(){
	HASH h = { NULL };
	clock_t start;
	double r = 0;
	for (int i = 0; i < MAX; i++){
		arr[i] = rand() % (MAX * 1000);
	}
	for (int i = 0; i < MAX; i++){
		start = clock();
		insert(&h, arr[i]);
		r += (clock() - start);
	}

	int* it;
	for (it = begin(&h); it != end(&h); it = to_next(&h, it)){
		printf("%d ", *it);
	}
	printf("\n");

	return 0;
}