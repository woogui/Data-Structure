#include"BST.h"
#include<stdlib.h>

//Iterators
NODE* begin(TREE* tree){
	NODE* it = tree->root;
	while (it&&it->left)
		it = it->left;
	return it;
}
NODE* end(TREE* tree){
	return NULL;
}
NODE* rbegin(TREE* tree){
	NODE* it = tree->root;
	while (it&&it->right)
		it = it->right;
	return it;
}
NODE* rend(TREE* tree){
	return NULL;
}

//Capacity
int is_empty(TREE* tree){
	return tree->root ? 1 : 0;
}
int size(TREE* tree){
	return tree->size;
}
int max_size(TREE* tree){
	return 2000000000 / sizeof(NODE);
}

//Modifiers
void insert(TREE* tree, int key){
	NODE** c = &tree->root;
	NODE* parent = NULL;
	while (*c){
		parent = *c;
		if ((*c)->key == key) return;
		if ((*c)->key > key) c = &(**c).left;
		else c = &(**c).right;
	}
	*c = (NODE*)calloc(1, sizeof(NODE));
	(*c)->key = key;
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
NODE* find(TREE* tree, int key){
	NODE* it = tree->root;
	while (it){
		if (it->key == key) break;
		if (it->key > key)it = it->left;
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
NODE* to_prev(NODE* it){
	if (it->left)
		it = to_right(it->left);
	else if (it->parent){
		if (it->parent->right == it)
			it = it->parent;
		else{
			while (it->parent&&it->parent->left == it)
				it = it->parent;
			it = it->parent;
		}
	}
	return it;
}
NODE* to_next(NODE* it){
	if (it->right)
		it = to_left(it->right);
	else if (it->parent){
		if (it->parent->left == it)
			it = it->parent;
		else{
			while (it->parent&&it->parent->right == it)
				it = it->parent;
			it = it->parent;
		}
	}
	return it;
}