#include"stack.h"
#include<assert.h>
#include<malloc.h>
#include<stdlib.h>

//Iterators
int* top(STACK* stack){
	return stack->size ? stack->base + stack->size - 1 : NULL;
}

//Capacity
int is_empty(STACK* stack){
	return stack->size ? 1 : 0;
}
int size(STACK* stack){
	return stack->size;
}

//Modifiers
void push(STACK* stack, int val){
	if (stack->size == stack->capacity){
		stack->capacity = stack->capacity ? stack->capacity * 2 : 1;
		int* tmp = (int*)malloc(stack->capacity*sizeof(int));
		memcpy(tmp, stack->base, stack->size*sizeof(int));
		if (stack->base)
			free(stack->base);
		stack->base = tmp;
	}
	*(stack->base + stack->size) = val;
	stack->size++;
}
int pop(STACK* stack){
	assert(stack->size > 0);
	stack->size--;
	return *(stack->base + stack->size);
}