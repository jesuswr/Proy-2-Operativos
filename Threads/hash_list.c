#include <stdlib.h>
#include "hash_list.h"


int hl_insert( hash_list *l , int k ){
	hl_node *aux = malloc( sizeof(hl_node) );
	if ( aux == NULL ) return -1;
	aux->key = k;
	aux->next = l->head;
	l->head = aux;
}


void hl_make( hash_list *l ){
	l->size = 0;
	l->head = NULL;
}


int hl_find( hash_list *l , int k ){

	hl_node *aux = l->head;
	while ( aux != NULL ){
		if ( aux->key == k ) return 1;
		aux = aux->next;
	} 
	return 0;
}