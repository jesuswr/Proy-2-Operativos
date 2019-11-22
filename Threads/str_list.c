/*
*	File:			list.c
*	Description:	file that contains the implementation of the
*					linked list and its functions
*	Author:			Jesus Wahrman 15-11540
*	Date:			29 / 07 / 19
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str_list.h"

/*
* Function: insert
* --------------------
* 	Inserts the given node in the first position of the given list by
*	moving its pointers and updates the size of the list
*	
* 	l: pointer to a list
*	n: pointer to a node
*/
int str_list_insert( str_list *l , char* w )
{
	str_node *n;
	n = malloc( sizeof( str_node ) );
	if ( n == NULL ) return -1;
	n->word = w;
	l->size = l->size + 1;
	n->next = l->head;
	l->head = n;
}


/*
* Function: make_list
* --------------------------
* 	Gets the pointer to the address of a memory block allocated for a list
*	and initializes its values head to NULL and size to 0
*
* 	l: pointer to a list
*/
void make_str_list( str_list *l )
{
	l->size = 0;
	l->head = NULL;
}