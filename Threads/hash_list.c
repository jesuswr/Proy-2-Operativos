/*
*  File:       	hash_list.c
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the implementation of the functions
*               used by the hash list
*  Date:      	23 / 11 / 19
*/

#include <stdlib.h>
#include "hash_list.h"


/*
*  Function : hl_insert
*  ----------------------
*  	Inserts an int into a list, by inserting at the head of the list
*  
*  	l : pointer to a list
*	k : integer to insert
*
*	returns 0 on success and -1 on failure
*/
int hl_insert( hash_list *l , int k ){
	hl_node *aux = malloc( sizeof(hl_node) );
	if ( aux == NULL ) return -1;
	aux->key = k;
	aux->next = l->head;
	l->head = aux;
	return 0;
}


/*
*  Function : hl_make
*  ----------------------
*  	Initializes the values of the list
*  
*  	l : pointer to a list
*/
void hl_make( hash_list *l ){
	l->size = 0;
	l->head = NULL;
}


/*
*  Function : hl_find
*  ----------------------
*  	Looks for an element in the list, by moving through the list
*  
*  	l : pointer to a list
*	k : integer to find
*
*	returns 1 on success and 0 on failure
*/
int hl_find( hash_list *l , int k ){

	hl_node *aux = l->head;
	while ( aux != NULL ){
		if ( aux->key == k ) return 1;
		aux = aux->next;
	} 
	return 0;
}