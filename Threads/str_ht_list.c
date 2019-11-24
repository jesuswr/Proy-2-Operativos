/*
*  File:       	str_ht_list.c
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the implementation of the functions
*               used by the string hash list
*  Date:      	23 / 11 / 19
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_ht_list.h"

/*
* Function: str_ht_list_insert
* --------------------
* 	Inserts the given node in the first position of the given list by
*	moving its pointers and updates the size of the list
*	
* 	l: pointer to a list
*	n: pointer to a word
*
*	returns 0 on success and -1 on failure
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
	return 0;
}


/*
* Function: str_ht_list_make_list
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
* Function: str_ht_list_find
* --------------------------
*	Looks for the given word in the list by moving through its nodes,
*	if it founds it, it adds k to the repetition counter for that 
*	node and returns the old value. Otherwise if the word is not in the list
*	it returns 0
*
* 	l: pointer lo a list
*	c: pointer to an array of char
*	k: integer to add to the rep count
*
*	returns: 0 if the words is not in the list or an int that represents
*			 the number of times that word appeared in the list
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