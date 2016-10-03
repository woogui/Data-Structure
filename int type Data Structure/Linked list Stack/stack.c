#include"stack.h"
#include<malloc.h>
#include<assert.h>

//Iterators
NODE* top(STACK* stack){
	return stack->top;
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
	NODE* n = (NODE*)malloc(sizeof(NODE));
	n->data = val;
	n->prev = stack->top;
	stack->top = n;
	stack->size++;
}
int pop(STACK* stack){
	assert(stack->top);
	NODE* it = stack->top;
	int val = it->data;
	stack->top = stack->top->prev;
	free(it);
	stack->size--;
	return val;
}