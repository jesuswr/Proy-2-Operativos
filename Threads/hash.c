#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "hash_list.h"

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

int ht_find( hash *h , int k ){
	printf("busco k en %d\n",hash_function(k,h->size) );
	return hl_find( &( h->hash_table[ hash_function(k,h->size) ] ) , k );
}

int ht_insert( hash *h , int k ){
	int e;
	printf("Inserto k en %d\n",hash_function(k,h->size) );
	e = hl_insert( &( h->hash_table[ hash_function(k,h->size) ] ) , k );
	return e;
}

int hash_function( int k , int mod ){
	return k%mod;
}