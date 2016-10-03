#ifndef DATA_STRUCTURE_GENERIC_BINARY_SEARCH_TREE_16_10_01_WC_INCLUDE
#define DATA_STRUCTURE_GENERIC_BINARY_SEARCH_TREE_16_10_01_WC_INCLUDE
#include <stddef.h>

typedef struct tagNODE NODE;
struct tagNODE{
	NODE *left, *right, *parent;
};

typedef struct tagTREE TREE;
struct tagTREE{
	NODE* root;
	size_t size, type_size;
};

TREE newTREE(size_t type_size);

//Iterators
void* begin(TREE* tree);
void* end(TREE* tree);
void* rbegin(TREE* tree);
void* rend(TREE* tree);

//Capacity
int is_empty(TREE* tree);
int size(TREE* tree);
int max_size(TREE* tree);

//Modifiers
void insert(TREE* tree, void* key);
void erase(TREE* tree, void* it);
void clear(TREE* tree);

//Operations
void* find(TREE* tree, void* key);

//Traversing
void* to_prev(void* it);
void* to_next(void* it);

#endif