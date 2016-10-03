#include"BST.h"
#include<stdlib.h>
#include<memory.h>

TREE newTREE(size_t type_size){
	TREE tree;
	tree.root = NULL;
	tree.size = 0;
	tree.type_size = type_size;
	return tree;
}

//Iterators
void* begin(TREE* tree){
	NODE* it = tree->root;
	while (it&&it->left)
		it = it->left;
	return it + 1;
}
void* end(TREE* tree){
	return sizeof(NODE);
}
void* rbegin(TREE* tree){
	NODE* it = tree->root;
	while (it&&it->right)
		it = it->right;
	return it + 1;
}
void* rend(TREE* tree){
	return sizeof(NODE);
}

//Capacity
int is_empty(TREE* tree){
	return tree->size ? 1 : 0;
}
int size(TREE* tree){
	return tree->size;
}
int max_size(TREE* tree){
	return 20000000 / (sizeof(NODE)+tree->type_size);
}

//Modifiers
void insert(TREE* tree, void* key){
	NODE** c = &tree->root;
	NODE* parent = NULL;
	while (*c){
		parent = *c;
		if (memcmp((*c) + 1, key, tree->type_size) == 0) return;
		if (memcmp((*c) + 1, key, tree->type_size) > 0) c = &(**c).left;
		else c = &(**c).right;
	}
	*c = (NODE*)calloc(1, sizeof(NODE)+tree->type_size);
	memcpy((*c) + 1, key, tree->type_size);
	(*c)->parent = parent;
	tree->size++;
}
NODE* to_left(NODE* it){
	while (it&&it->left)
		it = it->left;
	return it;
}
void transplant(TREE* tree, NODE* dst, NODE* src){
	if (dst->parent == NULL)
		tree->root = src;
	else if (dst->parent->left == dst)
		dst->parent->left = src;
	else
		dst->parent->right = src;
	if (src)
		src->parent = dst->parent;
}
void erase(TREE* tree, NODE* it){
	if (it == NULL) return;
	if (it->left == NULL)
		transplant(tree, it, it->right);
	else if (it->right == NULL)
		transplant(tree, it, it->left);
	else{
		NODE* succ = to_left(it->right);
		if (succ->parent != it){
			transplant(tree, succ, succ->right);
			succ->right = it->right;
			succ->right->parent = succ;
		}
		transplant(tree, it, succ);
		succ->left = it->left;
		succ->left->parent = succ;
	}
	free(it);
	tree->size--;

}
void clear(TREE* tree){
	while (tree->root){
		NODE* it = tree->root;
		if (it->left == NULL)
			transplant(tree, it, it->right);
		else if (it->right == NULL)
			transplant(tree, it, it->left);
		else{
			NODE* succ = to_left(it->right);
			if (succ->parent != it){
				transplant(tree, succ, succ->right);
				succ->right = it->right;
				succ->right->parent = succ;
			}
			transplant(tree, it, succ);
			succ->left = it->left;
			succ->left->parent = succ;
		}
		free(it);
	}
	tree->size = 0;
}

//Operations
void* find(TREE* tree, void* key){
	NODE* it = tree->root;
	while (it){
		if (memcmp(it + 1, key, tree->type_size) == 0) break;
		if (memcmp(it + 1, key, tree->type_size) > 0) it = it->left;
		else it = it->right;
	}
	return it;
}

//Traversing
NODE* to_right(NODE* it){
	while (it&&it->right)
		it = it->right;
	return it;
}
void* to_prev(void* it){
	NODE* c = (NODE*)it - 1;
	if (c->left)
		c = to_right(c->left);
	else if (c->parent){
		if (c->parent->right == c)
			c = c->parent;
		else{
			while (c->parent&&c->parent->left == c)
				c = c->parent;
			c = c->parent;
		}
	}
	return c + 1;
}
void* to_next(void* it){
	NODE* c = (NODE*)it - 1;
	if (c->right)
		c = to_left(c->right);
	else if (c->parent){
		if (c->parent->left == c)
			c = c->parent;
		else{
			while (c->parent&&c->parent->right == c)
				c = c->parent;
			c = c->parent;
		}
	}
	return c + 1;
}