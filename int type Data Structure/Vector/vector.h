#ifndef DATA_STRUCTURE_VECTOR_2016_09_24_WC_INCLUDE
#define DATA_STRUCTURE_VECTOR_2016_09_24_WC_INCLUDE
typedef struct tagVECTOR VECTOR;
struct tagVECTOR{
	int* base;
	int size;
	int capacity;
};
//Iterators
int* begin(VECTOR* v);
int* end(VECTOR* v);
int* rbegin(VECTOR* v);
int* rend(VECTOR* v);

//Capacity
int size(VECTOR* v);
int max_size(VECTOR* v);
void resize(VECTOR* v, int s);
int capacity(VECTOR* v);
int is_empty(VECTOR* v);
void reserve(VECTOR* v, int s);
void shrink_to_fit(VECTOR* v);

//Modifiers
void assign(VECTOR* v, int s, int val);
void push_back(VECTOR* v, int val);
void pop_back(VECTOR* v);
void insert(VECTOR* v, int* i, int val);
void erase(VECTOR* v, int* i);
void clear(VECTOR* v);

//Traversing
int* to_next(int* it);
int* to_prev(int* it);
#endif