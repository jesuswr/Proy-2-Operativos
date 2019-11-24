/*
*  File:       	hash.h
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the signatures of the functions and 
*               structures used by the hash
*  Date:      	23 / 11 / 19
*/


#include "hash_list.h"

#ifndef _HASH_H
#define _HASH_H

typedef struct {
	hash_list *hash_table;
	int size;
} hash;


/*
*  Function : ht_make
*  ----------------------
*  	Initializes the values of the hash table
*  
*  	h : pointer to a hash table
*	size : size of the table
*
*	returns 0 on success and -1 on failure
*/
int ht_make( hash *h , int size);


/*
*  Function : ht_find
*  ----------------------
*  	Looks for the given key in the hash
*  
*  	h : pointer to a hash table
*	k : integer to look in the table
*
*	returns 1 if it was found or 0 if it wasnt found
*/
int ht_find( hash *h , int k );


/*
*  Function : ht_insert
*  ----------------------
*  	Inserts the given key in the hash
*  
*  	h : pointer to a hash table
*	k : integer to insert in the table
*
*	returns 0 on success or -1 on failure
*/
int ht_insert( hash * h , int k );

#endif