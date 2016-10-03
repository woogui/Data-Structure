#include"vector.h"
#include<memory.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

//Iterators
int* begin(VECTOR* v){
	return v->base;
}
int* end(VECTOR* v){
	return v->base + v->size;
}
int* rbegin(VECTOR* v){
	return v->base + v->size - 1;
}
int* rend(VECTOR* v){
	return v->base - 1;
}

//Capacity
int size(VECTOR* v){
	return v->size;
}
int max_size(VECTOR* v){
	return 200000000 / sizeof(int);
}
void resize(VECTOR* v, int s){
	assert(s > 0);
	int*tmp = (int*)calloc(s, sizeof(int));
	memcpy(tmp, v->base, v->size*sizeof(int));
	if (v->base)
		free(v->base);
	v->base = tmp;
	v->size = v->capacity = s;
}
int capacity(VECTOR* v){
	return v->capacity;
}
int is_empty(VECTOR* v){
	return v->size ? 1 : 0;
}
void reserve(VECTOR* v, int s){
	assert(s > 0);
	int* tmp = (int*)malloc(s*sizeof(int));
	memcpy(tmp, v->base, v->size*sizeof(int));
	if (v->base)
		free(v->base);
	v->base = tmp;
	if (v->size > s)
		v->size = s;
	v->capacity = s;
}
void shrink_to_fit(VECTOR* v){
	resize(v, v->size);
}

//Modifiers
void assign(VECTOR* v, int s, int val){
	assert(s > 0);
	int* tmp = (int*)malloc(s*sizeof(int));
	if (v->base)
		free(v->base);
	v->base = tmp;
	for (int i = 0; i < s; i++)
		v->base[i] = val;
	v->capacity = v->size = s;
}
void push_back(VECTOR* v, int val){
	if (v->capacity == v->size){
		v->capacity = v->capacity ? v->capacity * 2 : 1;
		int* tmp = (int*)malloc(v->capacity*sizeof(int));
		memcpy(tmp, v->base, v->size*sizeof(int));
		if (v->base)
			free(v->base);
		v->base = tmp;
	}
	v->base[v->size] = val;
	v->size++;
}
void pop_back(VECTOR* v){
	assert(v->size > 0);
	v->size--;
}
void insert(VECTOR* v, int* i, int val){
	int idx = i - v->base;
	assert(idx >= 0 && idx < v->size);
	if (v->capacity == v->size)
		v->capacity = v->capacity ? v->capacity * 2 : 1;
	int* tmp = (int*)malloc(v->capacity*sizeof(int));
	memcpy(tmp, v->base, idx*sizeof(int));
	memcpy(tmp + idx + 1, v->base + idx, (v->size - idx)*sizeof(int));
	tmp[idx] = val;
	if (v->base)
		free(v->base);
	v->base = tmp;
	v->size++;
}
void erase(VECTOR* v, int* i){
	int idx = i - v->base;
	assert(idx >= 0 && idx < v->size);
	memmove(v->base + idx, v->base + idx + 1, (v->size - idx - 1)*sizeof(int));
	v->size--;
}
void clear(VECTOR* v){
	v->size = 0;
}

//Traversing
int* to_next(int* it){
	return ++it;
}
int* to_prev(int* it){
	return --it;
}