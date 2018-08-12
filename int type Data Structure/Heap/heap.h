#ifndef DATA_STURCTURE_HEAP_16_10_20_WC_INCLUDE
#define DATA_STURCTURE_HEAP_16_10_20_WC_INCLUDE
typedef struct tagHEAP HEAP;
struct tagHEAP{
	int* base;
	int size, capacity;
};

void insert(HEAP* h, int data);
void erase(HEAP* h);

#endif