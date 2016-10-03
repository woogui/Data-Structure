#ifndef DATA_STRUCTURE_LINKED_LIST_STACK_16_10_03_WC_INCLUDE
#define DATA_STRUCTURE_LINKED_LIST_STACK_16_10_03_WC_INCLUDE
typedef struct tagNODE NODE;
struct tagNODE{
	int data;
	NODE* prev;
};
typedef struct tagSTACK STACK;
struct tagSTACK{
	NODE* top;
	int size;
};

//Iterators
NODE* top(STACK* stack);

//Capacity
int is_empty(STACK* stack);
int size(STACK* stack);

//Modifiers
void push(STACK* stack, int val);
int pop(STACK* stack);

#endif