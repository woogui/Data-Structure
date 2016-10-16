#include"hash.h"
#include<stdio.h>
#include<time.h>

#define MAX 100
int arr[MAX];
int main(){
	HASH h = { NULL };
	clock_t start;
	double r = 0;
	for (int i = 0; i < MAX; i++){
		arr[i] = rand()%(MAX*10);
	}
	for (int i = 0; i < MAX; i++){
		start = clock();
		insert(&h, arr[i]);
		r += (clock() - start);
	}

//	printf("%f\n", r);
//	r = 0;
//	for (int i = 0; i < MAX; i++){
//		start = clock();
//		erase(&h, find(&h, arr[i]));
//		r += (clock() - start);
//	}
	
//	printf("%f\n", r);
	int* it;
	for (it = begin(&h); it != end(&h); it = to_next(&h, it)){
		printf("%d ", *it);
	}
		

	return 0;
}