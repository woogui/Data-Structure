#ifndef DATA_STRUCTURE_GENERIC_ARRAY_STACK_16_10_03_WC_INCLUDE
#define DATA_STRUCTURE_GENERIC_ARRAY_STACK_16_10_03_WC_INCLUDE
#include<stddef.h>

typedef struct tagSTACK STACK;
struct tagSTACK{
	void* base;
	size_t capacity, size, type_size;
};

STACK newSTACK(size_t type_size);

//Iterators
void* top(STACK* stack);

//Capacity
int is_empty(STACK* stack);
size_t size(STACK* stack);

//Modifiers
void push(STACK* stack, void* val);
void* pop(STACK* stack);

#endif