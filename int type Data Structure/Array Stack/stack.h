#ifndef DATA_STRUCTURE_ARRAY_STACK_16_10_03_WC_INCLUDE
#define DATA_STRUCTURE_ARRAY_STACK_16_10_03_WC_INCLUDE
typedef struct tagSTACK STACK;
struct tagSTACK{
	int* base;
	int size, capacity;
};

//Iterators
int* top(STACK* stack);

//Capacity
int is_empty(STACK* stack);
int size(STACK* stack);

//Modifiers
void push(STACK* stack, int val);
int pop(STACK* stack);

#endif