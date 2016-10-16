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
	while (i < h->bucket && (*(h->bloom + i / 8)&bit_position(i)) != bit_position(i)){
		i++;
	}
	return h->key + i;
}
int* end(HASH* h){
	return h->key+h->bucket;
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
	while (cnt<h->bucket){
		if (*(h->key + idx) == key)
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
	while ((*(h->bloom + idx / 8)&bit_position(idx)) == bit_position(idx)){
		if (*(h->key + idx) == key)
			return;
		idx = hash_fuc2(h, cnt, key);
		cnt++;
	}
	*(h->key + idx) = key;
	*(h->bloom + idx / 8) |= bit_position(idx);
	h->size++;
}
void erase(HASH* h, int i){
	if ((*(h->bloom + i / 8)&bit_position(i)) != bit_position(i))
		return;
	*(h->bloom + i / 8) ^= bit_position(i);
	h->size--;
}
void clear(HASH* h){
	for (int i = 0; i<h->bucket / 8 + 1; i++){
		*(h->bloom + i) = NULL;
	}
}

//Hash policy
void rehash(HASH* h, int n){
	while (n == 0 || (double)h->size / n * 100 > 70){
		n = n ? close_prime(n * 2) : 7;
	}
	int* tmp = (int*)malloc(n*sizeof(int));
	byte* bloom = (byte*)calloc(n / 8 + 1, sizeof(byte));
	int i = 0, t = h->bucket;
	h->bucket = n;
	while (h->bloom && i < t){
		if ((*(h->bloom + i / 8)&bit_position(i)) == bit_position(i)){
			int idx = hash_fuc1(h, *(h->key + i));
			int cnt = 0;
			while ((*(bloom + idx / 8)&bit_position(idx)) == bit_position(idx)){
				idx = hash_fuc2(h, cnt, *(h->key + i));
				cnt++;
			}
			*(tmp + idx) = *(h->key + i);
			*(bloom + idx / 8) |= bit_position(idx);
		}
		i++;
	}
	if (h->key){
		free(h->key);
		free(h->bloom);
	}
	h->key = tmp;
	h->bloom = bloom;
}

//traversing
int* to_next(HASH* h, int* it){
	int i = it - h->key;
	while (++i < h->bucket && (*(h->bloom + i / 8)&bit_position(i)) != bit_position(i));
	return h->key + i;
}