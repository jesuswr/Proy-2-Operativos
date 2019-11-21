/*
*	File:			list.c
*	Description:	file that contains the implementation of the
*					linked list and its functions
*	Author:			Jesus Wahrman 15-11540
*	Date:			29 / 07 / 19
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_ht_list.h"

/*
* Function: insert
* --------------------
* 	Inserts the given node in the first position of the given list by
*	moving its pointers and updates the size of the list
*	
* 	l: pointer to a list
*	n: pointer to a node
*/
int str_ht_list_insert( str_ht_list *l , char *w , int k )
{
	str_ht_list_node *n;

	n = malloc( sizeof( str_ht_list_node ) );
	if ( n == NULL ) return -1;
	n->reps = k;
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
void str_ht_list_make_list( str_ht_list *l )
{
	l->size = 0;
	l->head = NULL;
}

/*
* Function: find
* --------------------------
*	Looks for the given word in the list by moving through its nodes,
*	if it founds it, it adds 1 to the repetition counter for that 
*	node and returns that value. Otherwise if the word is not in the list
*	it returns 0
*
* 	l: pointer lo a list
*	c: pointer to an array of char
*
*	returns: 0 if the words is not in the list or an int that represents
*			 the number of times that word appears in the list plus 1
*/
int str_ht_list_find( str_ht_list *l , char *c , int k )
{
	str_ht_list_node *np = l->head;
	while ( np != NULL ){
		/* If the word is in the list, it updates the repetition count and 
		   returns it */
		if ( strcmp( c , np->word ) == 0 ){
			np->reps = np->reps + k;
			return np->reps - k ;
		}

		np = np->next;
	}
	return 0;
}