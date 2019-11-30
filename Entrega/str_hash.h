/*
*  File:       	str_hash.h
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the signature of the functions
*               used by the string hash
*  Date:      	23 / 11 / 19
*/


#include "str_ht_list.h"

#ifndef _STR_HASH_H
#define _STR_HASH_H

typedef struct {
	str_ht_list *hash_table;
	int size;
} str_hash;


/*
*  Function : str_ht_make
*  ----------------------
*  	Initializes the values of the hash table
*  
*  	h : pointer to a string hash table
*
*	returns 0 on success and -1 on failure
*/
int str_ht_make( str_hash *h );


/*
*  Function : str_ht_find
*  ----------------------
*  	Looks for the given key in the string hash
*  
*  	h : pointer to a string hash table
*	w : word to look for
*	reps : amount to add to the rep count of the word
*
*	returns the old amount of times that the word appears
*/
int str_ht_find( str_hash *h , char *w , int k );


/*
*  Function : str_ht_insert
*  ----------------------
*  	Inserts the given key in the hash
*  
*  	h : pointer to a hash table
*	k : integer to insert in the table
*	reps : number of reps of the word
*
*	returns 0 on success or -1 on failure
*/
int str_ht_insert( str_hash * h , char *w , int k );

#endif