/*
*	File:			str_list.h
*	Author: 		Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*	Description:	file that contains the signature of some functions 
*					and structures of a string list
*	Date:			23 / 11 / 19
*/


#ifndef _STR_LIST_H
#define _STR_LIST_H

typedef struct str_node {
	struct str_node *next;
	char *word;
	int reps;
} str_node;

typedef struct {
	int size;
	str_node *head;
} str_list;

/*
* Function: str_list_insert
* --------------------------
*	Inserts the given wotd in the given list
*
* 	l: pointer to a list
*	n: pointer to a word
*/
int str_list_insert( str_list *l , char* w );


/*
* Function: make_list
* --------------------------
* 	Gets the pointer to the address of a memory block allocated for a list
*	and initializes its values
*
* 	l: pointer to a list
*/
void make_str_list( str_list *l );


#endif