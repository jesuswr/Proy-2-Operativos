/*
*  File:       	hash.c
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the implementation of the functions
*               used by the hash
*  Date:      	23 / 11 / 19
*/


#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "hash_list.h"


/*
*  Function : ht_make
*  ----------------------
*  	Initializes the values of the hash table, allocates space for the lists
* 	and initializes the values of the lists
*  
*  	h : pointer to a hash table
*	size : size of the table
*
*	returns 0 on success and -1 on failure
*/
int ht_make( hash *h , int size){
	int i, e;
	h->size = size;
	h->hash_table = malloc( sizeof(hash)*size );
	if ( h->hash_table == NULL ) return -1;
	for ( i = 0 ; i < size ; i++ ){
		hl_make( &(h->hash_table[i]) );
	}
	return 0;
}


/*
*  Function : ht_find
*  ----------------------
*  	Looks for the given key in the hash by looking in the list indexed by the
*	value of the hashing function
*  
*  	h : pointer to a hash table
*	k : integer to look in the table
*
*	returns 1 if it was found or 0 if it wasnt found
*/
int ht_find( hash *h , int k ){
	return hl_find( &( h->hash_table[ hash_function(k,h->size) ] ) , k );
}


/*
*  Function : ht_insert
*  ----------------------
*  	Inserts the given key in the hash by inserting in the list indexed by the
*	value of the hashing function
*  
*  	h : pointer to a hash table
*	k : integer to insert in the table
*
*	returns 0 on success or -1 on failure
*/
int ht_insert( hash *h , int k ){
	int e;
	e = hl_insert( &( h->hash_table[ hash_function(k,h->size) ] ) , k );
	return e;
}


/*
*  Function : hash_function
*  ----------------------
*  	returns the value of the hash function of the given integer, 
*	by using mod with a high prime number to increase effectiveness
*  
*  	k : integer to calculate the hash function of
*	mod : mod to use in the function
*
*	returns the value of the funcion
*/
int hash_function( int k , int mod ){
	return k%mod;
}