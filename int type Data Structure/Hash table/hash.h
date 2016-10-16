#ifndef DATA_STRUCTURE_HASH_TABLE_16_10_05_WC_INCLUDE
#define DATA_STRUCTURE_HASH_TABLE_16_10_05_WC_INCLUDE
typedef unsigned char byte;
typedef struct tagHASH HASH;
struct tagHASH{
	int* key;
	byte* bloom;
	int size, bucket;
};

//Iterators
int* begin(HASH* h);
int* end(HASH* h);

//Capacity
int is_empty(HASH* h);
int size(HASH* h);
int max_size(HASH* h);

//Element lookup
int find(HASH* h, int key);

//Modifiers
void insert(HASH* h, int key);
void erase(HASH* h, int i);
void clear(HASH* h);

//Hash policy
void rehash(HASH* h, int n);
void reserve(HASH* h, int n);

//traversing
int* to_prev(int* it);
int* to_next(HASH* h, int* it);

#endif