#include"hash.h"
#include<malloc.h>
#include<stddef.h>
#include<assert.h>

byte bit_position(int num){
	byte n = 1;
	n <<= 7 - num % 8;
	return n;
}

//Iterators
int* begin(HASH* h){
	int i = 0;
	while (i < h->bucket && (*((byte*)h->key + i / 8)&bit_position(i)) != bit_position(i)){
		i++;
	}
	return (int*)((byte*)h->key + h->bucket / 8 + 1) + i;
}
int* end(HASH* h){
	return (int*)((byte*)h->key + h->bucket / 8 + 1) + h->bucket;
}

//Capacity
int is_empty(HASH* h){
	return h->size ? 1 : 0;
}
int size(HASH* h){
	return h->size;
}
int max_size(HASH* h){
	return 200000000 / sizeof(int);
}

//Element lookup
int find(HASH* h, int key){
	int idx = hash_fuc1(h, key);
	int cnt = 0;
	while (cnt < h->bucket){
		if (*((int*)((byte*)h->key + h->bucket / 8 + 1) + idx) == key)
			return idx;
		idx = hash_fuc2(h, cnt, key);
		cnt++;
	}
	return -1;
}

//Modifiers
int hash_fuc1(HASH* h, int key){
	return key % h->bucket;
}
int hash_fuc2(HASH*h, int M, int key){
	return (M + (h->bucket - hash_fuc1(h, key))) % h->bucket;
}
int is_prime(int n){
	if (!(n & 1) && n != 2){
		return 0;
	}
	if (!(n % 3) && n != 3){
		return 0;
	}
	for (int i = 5; i*i < n; i++){
		if (!(n%i) && n != i){
			return 0;
		}
	}
	return 1;
}
int close_prime(int n){
	while (!is_prime(n))
		n++;
	return n;
}
void insert(HASH* h, int key){
	if (h->bucket == 0 || (double)h->size / h->bucket * 100 > 70){
		rehash(h, h->bucket ? close_prime(h->bucket * 2) : 7);
	}
	int idx = hash_fuc1(h, key);
	int cnt = 0;
	while ((*((byte*)h->key + idx / 8)&bit_position(idx)) == bit_position(idx)){
		if (*((int*)((byte*)h->key + h->bucket / 8 + 1) + idx) == key)
			return;
		idx = hash_fuc2(h, cnt, key);
		cnt++;
	}
	*((int*)((byte*)h->key + h->bucket / 8 + 1) + idx) = key;
	*((byte*)h->key + idx / 8) |= bit_position(idx);
	h->size++;
}
void erase(HASH* h, int i){
	if ((*((byte*)h->key + i / 8)&bit_position(i)) != bit_position(i))
		return;
	*((byte*)h->key + i / 8) ^= bit_position(i);
	h->size--;
}
void clear(HASH* h){
	for (int i = 0; i<h->bucket / 8 + 1; i++){
		*((byte*)h->key + i) = NULL;
	}
	h->size = 0;
}

//Hash policy
void rehash(HASH* h, int n){
	while (n == 0 || (double)h->size / n * 100 > 70){
		n = n ? close_prime(n * 2) : 7;
	}
	byte* tmp = (byte*)calloc(n*sizeof(int)+n/8+1,sizeof(byte));
	int i = 0, t = h->bucket;
	h->bucket = n;
	while (h->key && i < t){
		if ((*((byte*)h->key + i / 8)&bit_position(i)) == bit_position(i)){
			int idx = hash_fuc1(h, *((int*)((byte*)h->key + t / 8 + 1) + i));
			int cnt = 0;
			while ((*(tmp + idx / 8)&bit_position(idx)) == bit_position(idx)){
				idx = hash_fuc2(h, cnt, *((int*)((byte*)h->key + t / 8 + 1) + i));
				cnt++;
			}
			*((int*)(tmp + h->bucket / 8 + 1) + idx) = *((int*)((byte*)h->key + t / 8 + 1) + i);
			*(tmp + idx / 8) |= bit_position(idx);
		}
		i++;
	}
	if (h->key){
		free(h->key);
	}
	h->key = tmp;
}

//traversing
int* to_next(HASH* h, int* it){
	int i = it - (int*)((byte*)h->key + h->bucket / 8 + 1);
	while (++i < h->bucket && (*((byte*)h->key + i / 8)&bit_position(i)) != bit_position(i));
	return (int*)((byte*)h->key + h->bucket / 8 + 1) + i;
}