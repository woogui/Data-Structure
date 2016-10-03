#include"list.h"
#include<stdlib.h>
#include<assert.h>

//Iterators
NODE* begin(LIST* list){
	return list->head;
}
NODE* end(LIST* list){
	return NULL;
}
NODE* rbegin(LIST* list){
	return list->tail;
}
NODE* rend(LIST* list){
	return NULL;
}

//Capacity
int is_empty(LIST* list){
	return list->head ? 1 : 0;
}
int size(LIST* list){
	return list->size;
}
int max_size(LIST* list){
	return 20000000 / sizeof(NODE);
}

//Modifiers
void assign(LIST* list, int s, int val){
	while (s--){
		NODE* n = (NODE*)malloc(sizeof(NODE));
		n->data = val;
		n->next = NULL;
		n->prev = list->tail;
		if (list->tail)
			list->tail = list->tail->next = n;
		else
			list->head = list->tail = n;
		list->size++;
	}
}
void push_front(LIST* list, int val){
	NODE* n = (NODE*)malloc(sizeof(NODE));
	n->data = val;
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
void push_back(LIST* list, int val){
	NODE* n = (NODE*)malloc(sizeof(NODE));
	n->data = val;
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
void insert(LIST* list, NODE* before, NODE* after, int val){
	NODE* n = (NODE*)malloc(sizeof(NODE));
	n->data = val;
	n->prev = before;
	n->next = after;
	if (before)
		before->next = n;
	else
		list->head = n;
	if (after)
		after->prev = n;
	else
		list->tail = n;
	list->size++;
}
void insert_before(LIST* list, NODE* it, int val){
	insert(list, it->prev, it, val);
}
void insert_after(LIST* list, NODE* it, int val){
	insert(list, it, it->next, val);
}
void erase(LIST* list, NODE* it){
	assert(list->head && it);
	if (it->prev)
		it->prev->next = it->next;
	else
		list->head = it->next;
	if (it->next)
		it->next->prev = it->prev;
	else
		list->tail = it->prev;
	free(it);
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
		if (ait->data > bit->data){
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
	LIST a = { NULL, }, b = { NULL, };
	NODE* it = list->head;
	int m = 1;
	while (list->size>m){
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
NODE* to_prev(NODE* it){
	return it->prev;
}
NODE* to_next(NODE* it){
	return it->next;
}