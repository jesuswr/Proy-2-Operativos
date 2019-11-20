#include "hash_list.h"

#ifndef _HASH_H
#define _HASH_H

typedef struct {
	hash_list *hash_table;
	int size;
} hash;

int ht_make( hash *h , int size);

int ht_find( hash *h , int k );

int ht_insert( hash * h , int k );

#endif