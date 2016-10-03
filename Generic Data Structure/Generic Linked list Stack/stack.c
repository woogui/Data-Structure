#include"stack.h"
#include<stdlib.h>
#include<memory.h>
#include<assert.h>

STACK newSTACK(size_t type_size){
	STACK stack;
	stack.top = NULL;
	stack.size = 0;
	stack.type_size = type_size;
	return stack;
}
//Iterators
void* top(STACK* stack){
	return stack->top?stack->top + 1:NULL;
}

//Capacity
int is_empty(STACK* stack){
	return stack->size ? 1 : 0;
}
size_t size(STACK* stack){
	return stack->size;
}

//Modifiers
void push(STACK* stack, void* val){
	NODE* n = (NODE*)malloc(sizeof(NODE)+stack->type_size);
	memcpy(n + 1, val, stack->type_size);
	n->prev = stack->top;
	stack->top = n;
	stack->size++;
}
void* pop(STACK* stack){
	assert(stack->size > 0);
	NODE* it = stack->top;
	char* val = (char*)malloc(stack->type_size);
	memcpy(val, it + 1, stack->type_size);
	stack->top = stack->top->prev;
	free(it);
	return val;
}