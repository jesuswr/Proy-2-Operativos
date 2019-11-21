/*
*	File:			list.h
*	Description:	header file that contains the signatures of the functions
*					and structures of the linked list
*	Author:			Jesus Wahrman 15-11540
*	Date:			29 / 07 / 19
*/


#ifndef _LIST_H
#define _LIST_H

typedef struct str_ht_list_node {
	struct str_ht_list_node *next;
	char *word;
	int reps;
} str_ht_list_node;

typedef struct {
	int size;
	str_ht_list_node *head;
} str_ht_list;

/*
* Function: insert
* --------------------------
*	Inserts the given node in the given list
*
* 	l: pointer to a list
*	n: pointer to a node
*/
int str_ht_list_insert( str_ht_list *l , char *n , int k );


/*
* Function: make_list
* --------------------------
* 	Gets the pointer to the address of a memory block allocated for a list
*	and initializes its values
*
* 	l: pointer to a list
*/
void str_ht_list_make_list( str_ht_list *l );

/*
* Function: find
* --------------------------
* 	Looks for the given word in the given list, if it finds it, it updates
*	the number of repetitions of that word by 1 and returns the new number of 
*	repetitions for that word. If it doesnt find it, returns 0.
*
* 	l: pointer lo a list
*	c: pointer to an array of char
*
*	returns: 0 if the words is not in the list or an int that represents
*			 the number of times that word appears in the list plus 1
*/
int str_ht_list_find( str_ht_list *l , char *c , int k );

#endif