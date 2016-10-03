#ifndef DATA_STRUCTURE_GENERIC_LINKED_LIST_16_10_01_WC_INCLUDE
#define DATA_STRUCTURE_GENERIC_LINKED_LIST_16_10_01_WC_INCLUDE
#include <stddef.h>

typedef struct tagNODE NODE;
struct tagNODE{
	NODE* prev, *next;
};

typedef struct tagLIST LIST;
struct tagLIST{
	NODE *head, *tail;
	size_t size, type_size;
};

LIST newLIST(size_t type_size);

//Iterators
void* begin(LIST* list);
void* end(LIST* list);
void* rbegin(LIST* list);
void* rend(LIST* list);

//Capacity
int is_empty(LIST* list);
size_t size(LIST* list);
size_t max_size(LIST* list);

//Modifiers
void assign(LIST* list, size_t s, void* val);
void push_front(LIST* list, void* val);
void pop_front(LIST* list);
void push_back(LIST* list, void* val);
void pop_back(LIST* list);
void insert(LIST* list, void* before, void* after, void* val);
void insert_before(LIST* list, void* it, void* val);
void insert_after(LIST* list, void* it, void* val);
void erase(LIST* list, void* it);
void clear(LIST* list);

//Operations
void merge(LIST* a, LIST* b);
void sort(LIST* list);
void reverse(LIST* list);

//Traversing
void* to_prev(void* it);
void* to_next(void* it);

#endif