#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str_ht_list.h"


int main( int argc , char **argv ){
	char *aux;
	int a;
	str_ht_list_node *n;
	str_ht_list *l;
	l = malloc( sizeof(str_ht_list) );
	str_ht_list_make_list( l );
	while ( 1 ){
		scanf("%d",&a);
		if ( a == 1010 ) break;
		aux = malloc( sizeof(char)*10 );
		scanf("%s",aux);
		str_ht_list_insert( l , aux , a);
	}

	while ( 1 ){
		scanf("%d",&a);
		if ( a == 1010 ) break;
		aux = malloc( sizeof(char)*10 );
		scanf("%s",aux);
		str_ht_list_find( l , aux , a);
	}

	n = l->head;

	while ( n != NULL ){
		printf("%s %d\n", n->word , n->reps);
		n = n->next;
	}
}