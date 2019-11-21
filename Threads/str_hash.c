#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str_ht_list.h"
#include "str_hash.h"

#define MOD 10007
#define PRIME 33

int prime_pow[101];


void set_str_hash( ){
	int i;
	int cont;
	cont = 1;
	for( i = 0 ; i < 101 ; i++ ){
		prime_pow[i] = cont;
		cont = (cont*PRIME)%MOD;
	}
}

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

int str_ht_find( str_hash *h , char *w , int reps){
	return str_ht_list_find( &( h->hash_table[ str_hash_function(w) ] ) ,
						       w , reps );
}

int str_ht_insert( str_hash *h , char *w , int reps ){
	return str_ht_list_insert( &( h->hash_table[ str_hash_function(w) ] ) ,
							   w , reps );
}

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

void print_content( str_hash *h ){
	str_ht_list_node *n;
	int i;

	for( i = 0 ; i < MOD ; i++ ){
		n = h->hash_table[i].head;
		while( n != NULL ){
			printf("%s %d\n", n->word , n->reps );
			n = n->next;
		}
	}
}