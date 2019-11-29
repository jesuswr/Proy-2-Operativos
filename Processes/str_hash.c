/*
*  File:       	str_hash.c
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the implementation of the functions
*               used by the string hash
*  Date:      	23 / 11 / 19
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str_ht_list.h"
#include "str_hash.h"

#define MOD 10007
#define PRIME 33

int prime_pow[101];


/*
*  Function : set_str_hash
*  ----------------------
*  	Initializes the values of an array of prime powers used 
*	in the hash function
*/
void set_str_hash( ){
	int i;
	int cont;
	cont = 1;
	for( i = 0 ; i < 101 ; i++ ){
		prime_pow[i] = cont;
		cont = (cont*PRIME)%MOD;
	}
}


/*
*  Function : str_ht_make
*  ----------------------
*  	Initializes the values of the hash table, allocates space for the lists
* 	and initializes the values of the lists
*  
*  	h : pointer to a string hash table
*
*	returns 0 on success and -1 on failure
*/
int str_ht_make( str_hash *h ){
	int i, e, size;
	size = MOD;
	set_str_hash();
	h->size = size;
	h->hash_table = malloc( sizeof(str_ht_list)*size );
	if ( h->hash_table == NULL ) return -1;
	for ( i = 0 ; i < size ; i++ ){
		str_ht_list_make_list( &(h->hash_table[i]) );
	}
	return 0;
}


/*
*  Function : str_ht_find
*  ----------------------
*  	Looks for the given key in the string hash by looking in the list indexed 
*	by the value of the hashing function, if found adds reps to the rep value
*	of that word
*  
*  	h : pointer to a string hash table
*	w : word to look for
*	reps : amount to add to the rep count of the word
*
*	returns the old amount of times that the word appears
*/
int str_ht_find( str_hash *h , char *w , int reps){
	return str_ht_list_find( &( h->hash_table[ str_hash_function(w) ] ) ,
						       w , reps );
}

/*
*  Function : str_ht_insert
*  ----------------------
*  	Inserts the given key in the hash by inserting in the list indexed by the
*	value of the hashing function with the given number of reps
*  
*  	h : pointer to a hash table
*	k : integer to insert in the table
*	reps : number of reps of the word
*
*	returns 0 on success or -1 on failure
*/
int str_ht_insert( str_hash *h , char *w , int reps ){
	return str_ht_list_insert( &( h->hash_table[ str_hash_function(w) ] ) ,
							   w , reps );
}


/*
*  Function : str_hash_function
*  ----------------------
*  	returns the value of the hash function of the given word, 
*	by using multiplying the i-th letter with a prime raised to the power of
*	i and adding those values, taking its module by another prime
*  
*  	w : word to get the hash function of
*
*	returns the value of the funcion
*/
int str_hash_function( char *w ){
	int key, i, len;
	key = 0;
	len = strlen( w );
	for( i = 0 ; i < len ; i++ ){
		key = ( key + ( w[i] - 'a' + 1 )* prime_pow[i] )% MOD;
	}
	if ( key < 0 ) key = -key;
	return key;
}