/*
*	File:			list.h
*	Description:	header file that contains the signatures of the functions
*					and structures of the linked list
*	Author:			Jesus Wahrman 15-11540
*	Date:			29 / 07 / 19
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
* Function: insert
* --------------------------
*	Inserts the given node in the given list
*
* 	l: pointer to a list
*	n: pointer to a node
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