#include"vector.h"
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include<assert.h>

VECTOR newVECTOR(size_t type_size){
	VECTOR v;
	v.base = NULL;
	v.capacity = v.size = 0;
	v.type_size = type_size;
	return v;
}

//Iterators
void* begin(VECTOR* v){
	return v->base;
}
void* end(VECTOR* v){
	return (char*)v->base + v->type_size*v->size;
}
void* rbegin(VECTOR* v){
	return (char*)v->base + v->type_size*(v->size-1);
}
void* rend(VECTOR* v){
	return (char*)v->base - v->type_size;
}

//Capacity
size_t size(VECTOR* v){
	return v->size;
}
size_t max_size(VECTOR* v){
	return 200000000 / v->type_size;
}
void resize(VECTOR* v, size_t s){
	assert(s > 0);
	char* tmp = (char*)calloc(s, v->type_size);
	memcpy(tmp, v->base, v->size*v->type_size);
	if (v->base)
		free(v->base);
	v->base = tmp;
	v->size = v->capacity = s;
}
size_t capacity(VECTOR* v){
	return v->capacity;
}
int is_empty(VECTOR* v){
	return v->size ? 1 : 0;
}
void reserve(VECTOR* v, size_t s){
		assert(s > 0);
		int* tmp = (int*)malloc(s*v->type_size);
		memcpy(tmp, v->base, v->size*v->type_size);
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
void assign(VECTOR* v, size_t s, void* val){
	assert(s > 0);
	char* tmp = (char*)malloc(s*v->type_size);
	if (v->base)
		free(v->base);
	v->base = tmp;
	for (int i = 0; i < s; i++)
		memcpy((char*)v->base + i*v->type_size, val, v->type_size);
	v->capacity = v->size = s;
}
void push_back(VECTOR* v, void* val){
	if (v->size == v->capacity){
		v->capacity = v->capacity ? v->capacity * 2 : 1;
		char* tmp = (char*)malloc(v->capacity*v->type_size);
		memcpy(tmp, v->base, v->size*v->type_size);
		if (v->base)
			free(v->base);
		v->base = tmp;
	}
	memcpy((char*)v->base + v->size*v->type_size, val, v->type_size);
	v->size++;
}
void pop_back(VECTOR* v){
	assert(v->size > 0);
	v->size--;
}
void insert(VECTOR* v, void* i, void* val){
	size_t idx = ((char*)i - v->base)/v->type_size;
	assert(idx >= 0 && idx < v->size);
	if (v->size == v->capacity)
		v->capacity = v->capacity ? v->capacity * 2 : 1;
	char* tmp = (char*)malloc(v->capacity*v->type_size);
	memcpy(tmp, v->base, idx*v->type_size);
	memcpy(tmp + idx*v->type_size, val, v->type_size);
	memcpy(tmp + (idx + 1)*v->type_size, (char*)v->base + idx*v->type_size, (v->size - idx)*v->type_size);
	if (v->base)
		free(v->base);
	v->base = tmp;
	v->size++;
}
void erase(VECTOR* v, void* i){
	size_t idx = ((char*)i - v->base) / v->type_size;
	assert(idx >= 0 && idx < v->size);
	memmove((char*)v->base + idx*v->type_size, (char*)v->base + (idx + 1)*v->type_size, (v->size - idx - 1)*v->type_size);
	v->size--;
}
void clear(VECTOR* v){
	v->size = 0;
}

//Traversing
void* to_next(VECTOR* v, void* it){
	return (char*)it + v->type_size;
}
void* to_prev(VECTOR* v, void* it){
	return (char*)it - v->type_size;
}