#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_list.h"

int main( int argc , char **argv ){
	str_list *l;
	char *w;
	str_node *n;
	int a;
	l = malloc( sizeof( str_list ) );
	scanf("%d",&a);

	while( a-- ){
		w = malloc( 20 );
		scanf("%s",w);
		str_list_insert( l , w );		
	}

	n = l->head;

	while( n != NULL ){
		printf("%s\n", n->word);
		n = n->next;
	}


}