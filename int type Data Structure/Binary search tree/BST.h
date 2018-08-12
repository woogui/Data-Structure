#ifndef DATA_STRUCTURE_BINARY_SEARCH_TREE_16_09_25_WC_INCLUDE
#define DATA_STRUCTURE_BINARY_SEARCH_TREE_16_09_25_WC_INCLUDE
typedef struct tagNODE NODE;
struct tagNODE{
	int key;
	NODE *left, *right, *parent;
};

typedef struct tagTREE TREE;
struct tagTREE{
	NODE* root;
	int size;
};

//Iterators
NODE* begin(TREE* tree);
NODE* end(TREE* tree);
NODE* rbegin(TREE* tree);
NODE* rend(TREE* tree);

//Capacity
int is_empty(TREE* tree);
int size(TREE* tree);
int max_size(TREE* tree);

//Modifiers
void insert(TREE* tree, int key);
void erase(TREE* tree, NODE* it);
void clear(TREE* tree);

//Operations
NODE* find(TREE* tree, int key);

//Traversing
NODE* to_prev(NODE* it);
NODE* to_next(NODE* it);

#endif