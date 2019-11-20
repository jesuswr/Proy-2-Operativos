#ifndef _HASH_LIST_H
#define _HASH_LIST_H

typedef struct hl_node {
	struct hl_node *next;
	int key;
} hl_node;

typedef struct {
	int size;
	hl_node *head;
} hash_list;


int hl_insert( hash_list *l , int key );


void hl_make( hash_list *l );


int hl_find( hash_list *l , int key );

#endif