/*
*  File:       	hash_list.h
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the signatures of the functions and 
*               structures used by the hash list
*  Date:      	23 / 11 / 19
*/

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


/*
*  Function : hl_insert
*  ----------------------
*  	Inserts an int into a list
*  
*  	l : pointer to a list
*	k : integer to insert
*
*	returns 0 on success and -1 on failure
*/
int hl_insert( hash_list *l , int key );


/*
*  Function : hl_make
*  ----------------------
*  	Initializes the values of the list
*  
*  	l : pointer to a list
*/
void hl_make( hash_list *l );


/*
*  Function : hl_find
*  ----------------------
*  	Looks for an element in the list
*  
*  	l : pointer to a list
*	k : integer to find
*
*	returns 1 on success and 0 on failure
*/
int hl_find( hash_list *l , int key );

#endif