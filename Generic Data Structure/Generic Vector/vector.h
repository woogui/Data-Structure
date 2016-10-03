#ifndef DATA_STRUCTURE_GENERIC_VECTOR_16_10_01_WC_INCLUDE
#define DATA_STRUCTURE_GENERIC_VECTOR_16_10_01_WC_INCLUDE
#include<stddef.h>
typedef struct tagVECTOR VECTOR;
struct tagVECTOR{
	size_t size, capacity, type_size;
	void* base;
};

VECTOR newVECTOR(size_t type_size);

//Iterators
void* begin(VECTOR* v);
void* end(VECTOR* v);
void* rbegin(VECTOR* v);
void* rend(VECTOR* v);

//Capacity
size_t size(VECTOR* v);
size_t max_size(VECTOR* v);
void resize(VECTOR* v, size_t s);
size_t capacity(VECTOR* v);
int is_empty(VECTOR* v);
void reserve(VECTOR* v, size_t s);
void shrink_to_fit(VECTOR* v);

//Modifiers
void assign(VECTOR* v, size_t s, void* val);
void push_back(VECTOR* v, void* val);
void pop_back(VECTOR* v);
void insert(VECTOR* v, void* i, void* val);
void erase(VECTOR* v, void* i);
void clear(VECTOR* v);

//Traversing
void* to_next(VECTOR* v, void* it);
void* to_prev(VECTOR* v, void* it);

#endif