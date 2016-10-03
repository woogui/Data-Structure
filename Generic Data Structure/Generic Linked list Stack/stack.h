#ifndef DATA_STURCTURE_GENERIC_LINKED_LIST_STACK_16_10_03_WC_INCLUDE
#define DATA_STURCTURE_GENERIC_LINKED_LIST_STACK_16_10_03_WC_INCLUDE
#include<stddef.h>

typedef struct tagNODE NODE;
struct tagNODE{
	NODE* prev;
};

typedef struct tagSTACK STACK;
struct tagSTACK{
	NODE* top;
	size_t size, type_size;
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