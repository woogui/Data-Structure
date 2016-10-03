#include"stack.h"
#include<stdlib.h>
#include<memory.h>
#include<assert.h>

STACK newSTACK(size_t type_size){
	STACK stack;
	stack.base = NULL;
	stack.capacity = stack.size = 0;
	stack.type_size = type_size;
	return stack;
}

//Iterators
void* top(STACK* stack){
	return stack->size ? (char*)stack->base + (stack->size - 1)*stack->type_size : NULL;
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
	if (stack->size == stack->capacity){
		stack->capacity = stack->capacity ? stack->capacity * 2 : 1;
		char* tmp = (char*)malloc(stack->capacity*stack->type_size);
		memcpy(tmp, stack->base, stack->size*stack->type_size);
		if (stack->base)
			free(stack->base);
		stack->base = tmp;
	}
	memcpy((char*)stack->base + stack->size*stack->type_size, val, stack->type_size);
	stack->size++;
}
void* pop(STACK* stack){
	assert(stack->size > 0);
	stack->size--;
	return (char*)stack->base + stack->size*stack->type_size;
}