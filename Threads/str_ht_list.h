/*
*  File:       	str_ht_list.h
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the signatures of the functions
*               used by the string hash list
*  Date:      	23 / 11 / 19
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
* Function: str_ht_list_insert
* --------------------------
*	Inserts the given word in the given list
*
* 	l: pointer to a list
*	n: pointer to a word
*
*	returns 0 on success and -1 on failure
*/
int str_ht_list_insert( str_ht_list *l , char *n , int k );


/*
* Function: str_ht_list_make_list
* --------------------------
* 	Gets the pointer to the address of a memory block allocated for a list
*	and initializes its values
*
* 	l: pointer to a list
*/
void str_ht_list_make_list( str_ht_list *l );

/*
* Function: str_ht_list_find
* --------------------------
* 	Looks for the given word in the given list, if it finds it, it updates
*	the number of repetitions of that word by k and returns the old number of 
*	repetitions for that word. If it doesnt find it, returns 0.
*
* 	l: pointer lo a list
*	c: pointer to an array of char
*	k: ammount to add to the rep count of the words
*
*	returns: 0 if the words is not in the list or an int that represents
*			 the number of times that word appeared before updating
*/
int str_ht_list_find( str_ht_list *l , char *c , int k );

#endif