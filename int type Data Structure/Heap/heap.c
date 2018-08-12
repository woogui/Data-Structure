#include"heap.h"
#include<malloc.h>
#include<memory.h>

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//heapify down to up
void heapify_D2U(HEAP* h, int i){
	int idx = i;
	while (idx > 0 && *(h->base + idx) > *(h->base + ((idx - 1) >> 1))){
		swap(h->base + idx, h->base + ((idx - 1) >> 1));
		idx = (idx - 1) >> 1;
	}
}
//heapify up to down
void heapify_U2D(HEAP* h, int i){
	int idx = i, c = idx;
	while (idx < h->size){
		if (*(h->base + idx) < *(h->base + (idx << 1) + 1) && (idx << 1) + 1 < h->size)
			c = (idx << 1) + 1;
		if (*(h->base + c) < *(h->base + (idx << 1) + 2) && (idx << 1) + 2 < h->size)
			c = (idx << 1) + 2;
		if (c == idx)break;
		swap(h->base + idx, h->base + c);
		idx = c;
	}
}

void insert(HEAP* h, int data){
	if (h->size == h->capacity){
		h->capacity = h->capacity ? h->capacity * 2 : 1;
		int* tmp = (int*)malloc(h->capacity*sizeof(int));
		memcpy(tmp, h->base, h->size*sizeof(int));
		if (h->base)
			free(h->base);
		h->base = tmp;
	}
	*(h->base + h->size) = data;
	h->size++;
	int i = h->size;
	while (--i){
		heapify_D2U(h, i);
	}
}
void erase(HEAP* h){
	swap(h->base, h->base + --h->size);
	int i = h->size >> 1;
	while (i--){
		heapify_U2D(h, i);
	}
}

//If you want to change from the Max heap to Min heap is a change compared to the part of the Heapify function.