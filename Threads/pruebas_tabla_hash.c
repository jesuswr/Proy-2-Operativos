#include <stdlib.h>
#include <stdio.h>
#include "hash_list.h"
#include "hash.h"

int main( int argc , char ** argv){

	hash h;
	int size, aux, i;
	hl_node *p;
	scanf( "%d" , &size );
	ht_make( &h , size );
	while ( 1 ){
		scanf("%d",&aux);
		if ( !aux ) break;
		ht_insert(&h,aux);
	}

	while ( 1 ){
		scanf("%d",&aux);
		if ( !aux ) break;
		if ( ht_find(&h,aux) )
			printf("ENCONTRADO\n");
		else
			printf("NO ENCONTRADO\n");
	}

	for( i = 0 ; i < size ; i++ ){
		p = h.hash_table[i].head;
		while ( p != NULL ){
			printf("%d ", p->key);
			p = p->next;
		}
		printf("\n");
	}

	return 0;
}