#include "hash_list.h"

#ifndef _STR_HASH_H
#define _STR_HASH_H

typedef struct {
	str_ht_list *hash_table;
	int size;
} str_hash;

int str_ht_make( str_hash *h );

int str_ht_find( str_hash *h , char *w , int k );

int str_ht_insert( str_hash * h , char *w , int k );

void print_content( str_hash *h );

#endif