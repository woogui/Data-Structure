#ifndef DATA_STRUCTURE_LINKED_LIST_2016_09_24_WC_INCLUDE
#define DATA_STRUCTURE_LINKED_LIST_2016_09_24_WC_INCLUDE
typedef struct tagNODE NODE;
struct tagNODE{
	NODE* prev, *next;
	int data;
};
typedef struct tagLIST LIST;
struct tagLIST{
	NODE *head, *tail;
	int size;
};

//Iterators
NODE* begin(LIST* list);
NODE* end(LIST* list);
NODE* rbegin(LIST* list);
NODE* rend(LIST* list);

//Capacity
int is_empty(LIST* list);
int size(LIST* list);
int max_size(LIST* list);

//Modifiers
void assign(LIST* list, int s, int val);
void push_front(LIST* list, int val);
void pop_front(LIST* list);
void push_back(LIST* list, int val);
void pop_back(LIST* list);
void insert(LIST* list, NODE* before, NODE* after, int val);
void insert_before(LIST* list, NODE* it, int val);
void insert_after(LIST* list, NODE* it, int val);
void erase(LIST* list, NODE* it);
void clear(LIST* list);

//Operations
void merge(LIST* a, LIST* b);
void sort(LIST* list);
void reverse(LIST* list);

//Traversing
NODE* to_prev(NODE* it);
NODE* to_next(NODE* it);
#endif