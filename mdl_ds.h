/* 
 * data structures
 *
 * List - doubly linked list
 * todo: unrolled linked list
 * DynArr - dynamic array, like vectors in C++
 * todo: HashMap
 * todo: BinTree - self balancing binary tree */
#ifndef MDL_DS_H
#define MDL_DS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char      uc;
typedef unsigned short int us;
typedef unsigned int       ui;
typedef unsigned long int  ul;

typedef struct MdlDsListNode {
	void* val;
	struct MdlDsListNode* prev;
	struct MdlDsListNode* next;
} MdlDsListNode;

MdlDsListNode*  mdlDsListNodeNew(void* val, MdlDsListNode* prev, MdlDsListNode* next);
MdlDsListNode*  mdlDsListNodeLoopNext(MdlDsListNode* node, int(*fP_cond)(MdlDsListNode*) );
MdlDsListNode*  mdlDsListNodeLoopPrev(MdlDsListNode* node, int(*fP_cond)(MdlDsListNode*) );
void  mdlDsListNodePutNode(MdlDsListNode* prev, MdlDsListNode* node, MdlDsListNode* next);
MdlDsListNode*  mdlDsListNodePut(void* val, MdlDsListNode* prev,  MdlDsListNode* next);
void  mdlDsListNodeDel(MdlDsListNode* node);

typedef struct {
	MdlDsListNode* first;
	MdlDsListNode* last;
	ul l;
} MdlDsList; 

MdlDsList*  mdlDsListNew();
MdlDsListNode*  mdlDsListPut(MdlDsList* ll, void* val, MdlDsListNode* prev, MdlDsListNode* next);
MdlDsListNode*  mdlDsListAdd(MdlDsList* ll, void* val);
MdlDsListNode*  mdlDsListPrepend(MdlDsList* ll, void* val);
MdlDsListNode*  mdlDsListLoopNext(MdlDsList* ll, int(*fP_cond)(MdlDsListNode*) );
MdlDsListNode*  mdlDsListLoopPrev(MdlDsList* ll, int(*fP_cond)(MdlDsListNode*) );
void  mdlDsListRemoveNode(MdlDsList* ll, MdlDsListNode* node);
void  mdlDsListDel(MdlDsList* ll);

typedef struct {
	uc* a;
	ul e_l;
	ul l;
	ul byte_size; /* in bytes */
	us mult;
} MdlDsDynArr;

MdlDsDynArr* mdlDsDynArrNew(ul e_l);
MdlDsDynArr* mdlDsDynArrNewCustom(ul e_l, ul size, ul mult);
void*  mdlDsDynArrAdd(MdlDsDynArr* da, void* val);
void*  mdlDsDynArrResize(MdlDsDynArr* da, ul new_byte_size);
void*  mdlDsDynArrTrim(MdlDsDynArr* da);
void  mdlDsDynArrDel(MdlDsDynArr* da);
#endif /* MDL_DS_H */

#ifdef MDL_DS_IMPL
/* 
 * MdlDsList - doubly linked list 
 *
 * operations:
 * init - mdlDsListNew 
 * adding elements - mdlDsPut, mdlDsListAdd, mdlDsListPrepend
 * removing elements - mdlDsListRemoveNode
 * loop through the list - mdlDsListLoopNext/Prev 
 * free - mdlDsListDel 
 *
 * MdlDsListNode - node struct used by MdlDsList */
MdlDsListNode* 
mdlDsListNodeNew(void* val, MdlDsListNode* prev, MdlDsListNode* next) 
{
	MdlDsListNode* node = malloc(sizeof(MdlDsListNode));
	node->val = val;
	node->prev = prev;
	node->next = next;
	return node;
}

MdlDsListNode* 
mdlDsListNodeLoopNext(MdlDsListNode* node, int(*fP_cond)(MdlDsListNode*) ) 
{
	while( node != 0 ) {
		if ( fP_cond(node) ) return node;
		node = node->next;
	}
}
MdlDsListNode* 
mdlDsListNodeLoopPrev(MdlDsListNode* node, int(*fP_cond)(MdlDsListNode*) ) 
{
	while( node != 0 ) {
		if ( fP_cond(node) ) return node;
		node = node->prev;
	}
}

void 
mdlDsListNodePutNode(MdlDsListNode* prev, MdlDsListNode* node, MdlDsListNode* next) 
{
	if (prev != 0) prev->next = node;
	if (next != 0) next->prev = node;
}

MdlDsListNode* 
mdlDsListNodePut(void* val, MdlDsListNode* prev,  MdlDsListNode* next) 
{
	MdlDsListNode* node = mdlDsListNodeNew(val, prev, next); 
	mdlDsListNodePutNode(prev, node, next);
	return node;
}

void 
mdlDsListNodeDel(MdlDsListNode* node) 
{
	free(node->val);
	free(node);
}

MdlDsList* 
mdlDsListNew() 
{
	return calloc(1, sizeof(MdlDsList));
}

MdlDsListNode* 
mdlDsListPut(MdlDsList* ll, void* val, MdlDsListNode* prev, MdlDsListNode* next) 
{
	MdlDsListNode* node = mdlDsListNodePut(val, prev, next); 
	ll->l++;
	if ( ll->first == 0 ) ll->first = ll->last = node;
	else if ( ll->first == next ) ll->first = node;
	else if ( ll->last == prev ) ll->last = node;
	return node;
}

MdlDsListNode* 
mdlDsListAdd(MdlDsList* ll, void* val) 
{
	return mdlDsListPut(ll, val, ll->last, 0);
}

MdlDsListNode* 
mdlDsListPrepend(MdlDsList* ll, void* val) 
{
	return mdlDsListPut(ll, val, 0, ll->first);
}

MdlDsListNode* 
mdlDsListLoopNext(MdlDsList* ll, int(*fP_cond)(MdlDsListNode*) ) 
{
	return mdlDsListNodeLoopNext(ll->first, fP_cond);
}

MdlDsListNode* 
mdlDsListLoopPrev(MdlDsList* ll, int(*fP_cond)(MdlDsListNode*) ) 
{
	return mdlDsListNodeLoopPrev(ll->last, fP_cond);
}

void 
mdlDsListRemoveNode(MdlDsList* ll, MdlDsListNode* node) 
{
	if ( node->prev != 0 ) node->prev->next = node->next;
	if ( node->next != 0 ) node->next->prev = node->prev;

	ll->first = ll->first == node ? node->next : ll->first;
	ll->last = ll->last == node ? node->prev : ll->last;
	ll->l--;

	mdlDsListNodeDel(node);
}

void 
mdlDsListDel(MdlDsList* ll) 
{
	MdlDsListNode* node = ll->first;
	MdlDsListNode* next;
	while(node != 0) {
		next = node->next;
		mdlDsListNodeDel(node);
		node = next;
	}
	ll->l = 0;
	free(ll);
}

/* 
 * MdlDsDynArr - dynamic array 
 *
 * operations:
 * init - mdlDsDynArrNew 
 * adding elements - mdlDsDynArrAdd
 * resize - mdlDsDynArrResize, mdlDsDynArrTrim
 * free - mdlDsListDel */

#define MDL_DS_DYN_ARR_SIZE 1000
#define MDL_DS_DYN_ARR_MULT 2

MdlDsDynArr*
mdlDsDynArrNew(ul e_l)
{
    return mdlDsDynArrNewCustom(e_l, MDL_DS_DYN_ARR_SIZE, MDL_DS_DYN_ARR_MULT);
}

MdlDsDynArr*
mdlDsDynArrNewCustom(ul e_l, ul size, ul mult) {
    MdlDsDynArr* da = malloc(sizeof(MdlDsDynArr));
    da->byte_size = e_l * size;
    da->a = malloc( da->byte_size );
    da->e_l = e_l;
    da->l = 0;
    da->mult = mult;
    return da;
}

void* 
mdlDsDynArrAdd(MdlDsDynArr* da, void* val) 
{
	if ( da->byte_size < ((da->l+1) * da->e_l) ) {
		da->byte_size *= da->mult;
		da->a = realloc(da->a, da->byte_size);
	}
	memcpy(da->a + (da->l * da->e_l), val, da->e_l);
	da->l++;
	return da->a;
}

/* resizes only if new_size would fit all exisitng elements
 * else returns null */
void* 
mdlDsDynArrResize(MdlDsDynArr* da, ul new_byte_size)
{
	if ( new_byte_size > 0 && new_byte_size >= ((da->l) * da->e_l) ) {
		da->byte_size = new_byte_size;
		da->a = realloc(da->a, da->byte_size);
		return da->a;
	} else {
		return 0;	
	}
}

void* 
mdlDsDynArrTrim(MdlDsDynArr* da) 
{
	return mdlDsDynArrResize(da, da->l * da->e_l);
}

void 
mdlDsDynArrDel(MdlDsDynArr* da) 
{
	free(da->a);
	free(da);
}
#endif /* MDL_DS_IMPLEMENTATION */
