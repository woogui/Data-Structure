#include"list.h"
#include<stdlib.h>
#include<memory.h>
#include<assert.h>

LIST newLIST(size_t type_size){
	LIST list;
	list.head = list.tail = NULL;
	list.size = 0;
	list.type_size = type_size;
	return list;
}

//Iterators
void* begin(LIST* list){
	return list->head + 1;
}
void* end(LIST* list){
	return sizeof(NODE);
}
void* rbegin(LIST* list){
	return list->tail + 1;
}
void* rend(LIST* list){
	return sizeof(NODE);
}

//Capacity
int is_empty(LIST* list){
	return list->size ? 1 : 0;
}
size_t size(LIST* list){
	return list->size;
}
size_t max_size(LIST* list){
	return 20000000 / (sizeof(NODE)+list->type_size);
}

//Modifiers
void assign(LIST* list, size_t s, void* val){
	while (s--){
		NODE* n = (NODE*)malloc(sizeof(NODE)+list->type_size);
		memcpy(n + 1, val, list->type_size);
		n->next = NULL;
		n->prev = list->tail;
		if (list->tail)
			list->tail = list->tail->next = n;
		else
			list->head = list->tail = n;
		list->size++;
	}
}
void push_front(LIST* list, void* val){
	NODE* n = (NODE*)malloc(sizeof(NODE)+list->type_size);
	memcpy(n + 1, val, list->type_size);
	n->prev = NULL;
	n->next = list->head;
	if (list->head)
		list->head = list->head->prev = n;
	else
		list->head = list->tail = n;
	list->size++;
}
void pop_front(LIST* list){
	assert(list->head);
	list->head = list->head->next;
	if (list->head){
		list->head->prev = NULL;
		free(list->head->prev);
	}
	else{
		list->tail = NULL;
		free(list->tail);
	}
	list->size--;
}
void push_back(LIST* list, void* val){
	NODE* n = (NODE*)malloc(sizeof(NODE)+list->type_size);
	memcpy(n + 1, val, list->type_size);
	n->next = NULL;
	n->prev = list->tail;
	if (list->tail)
		list->tail = list->tail->next = n;
	else
		list->head = list->tail = n;
	list->size++;
}
void pop_back(LIST* list){
	assert(list->head);
	list->tail = list->tail->prev;
	if (list->tail){
		list->tail->next = NULL;
		free(list->tail->next);
	}
	else{
		list->head = NULL;
		free(list->head);
	}
	list->size--;
}
void insert(LIST* list, void* before, void* after, void* val){
	NODE* n = (NODE*)malloc(sizeof(NODE)+1);
	memcpy(n + 1, val, list->type_size);
	n->prev = (NODE*)before - 1;
	n->next = (NODE*)after - 1;
	if ((NODE*)before - 1)
		((NODE*)before - 1)->next = n;
	else
		list->head = n;
	if ((NODE*)after - 1)
		((NODE*)after - 1)->prev = n;
	else
		list->tail = n;
	list->size++;
}
void insert_before(LIST* list, void* it, void* val){
	insert(list, ((NODE*)it - 1)->prev + 1, it, val);
}
void insert_after(LIST* list, void* it, void* val){
	insert(list, it, ((NODE*)it - 1)->next + 1, val);
}
void erase(LIST* list, void* it){
	assert(list->head && it);
	if (((NODE*)it - 1)->prev)
		((NODE*)it - 1)->prev->next = ((NODE*)it - 1)->next;
	else
		list->head = ((NODE*)it - 1)->next;
	if (((NODE*)it - 1)->next)
		((NODE*)it - 1)->next->prev = ((NODE*)it - 1)->prev;
	else
		list->tail = ((NODE*)it - 1)->prev;
	free((NODE*)it - 1);
	list->size--;
}
void clear(LIST* list){
	while (list->head){
		list->tail = list->tail->prev;
		if (list->tail){
			list->tail->next = NULL;
			free(list->tail->next);
		}
		else{
			list->head = NULL;
			free(list->head);
		}
	}
	list->size = 0;
}

//Operations
NODE* to_m_next(NODE* it, int m){
	while (--m){
		if (it->next)
			it = it->next;
	}
	return it;
}
void merge(LIST* a, LIST* b){
	NODE *before = a->head->prev, *after = b->tail->next;
	a->head->prev = a->tail->next = b->head->prev = b->tail->next = NULL;
	NODE *ait = a->head, *bit = b->head;
	while (ait && bit){
		if (memcmp(ait + 1, bit + 1, a->type_size) > 0){
			b->head = bit->next;
			if (b->head)
				b->head->prev = NULL;
			bit->prev = ait->prev;
			bit->next = ait;
			bit->next->prev = bit;
			if (bit->prev)
				bit->prev->next = bit;
			else
				a->head = bit;
			bit = b->head;
		}
		else
			ait = ait->next;
	}

	if (bit){
		bit->prev = a->tail;
		a->tail->next = bit;
		a->tail = b->tail;
	}
	b->head = b->tail = NULL;
	a->size = a->size + b->size;
	b->size = 0;
	if (before || after){
		a->head->prev = before;
		if (before)
			before->next = a->head;
		a->tail->next = after;
		if (after)
			after->prev = a->tail;
	}
}
void sort(LIST* list){
	LIST a = newLIST(list->type_size), b = newLIST(list->type_size);
	NODE* it = list->head;
	int m = 1;
	while (list->size > m){
		while (it){
			a.head = it;
			a.tail = it = to_m_next(it, m);
			b.head = it = it->next;
			if (it)
				b.tail = it = to_m_next(it, m);
			if (a.head&&b.head)
				merge(&a, &b);
			if (list->head->prev)
				list->head = a.head;
			it = a.tail->next;
		}
		it = list->head;
		m <<= 1;
	}
}
void reverse(LIST* list){
	LIST tmp = { NULL, };
	while (list->tail){
		list->tail = list->tail->prev;
		if (list->tail){
			if (tmp.head)
				tmp.tail = tmp.tail->next = list->tail->next;
			else
				tmp.head = tmp.tail = list->tail->next;
			list->tail->next = NULL;
		}
		else{
			if (tmp.head)
				tmp.tail->next = list->head;
			else
				tmp.head = tmp.tail = list->head;
			list->head = NULL;
		}
	}
	list->head = tmp.head;
	list->tail = tmp.tail;
}

//Traversing
void* to_prev(void* it){
	return ((NODE*)it - 1)->prev + 1;
}
void* to_next(void* it){
	return ((NODE*)it - 1)->next + 1;
}