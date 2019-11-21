#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str_ht_list.h"
#include "str_hash.h"


int main( int argc , char **argv ){
	str_hash *h;
	int a;
	char *w;
	h = malloc( sizeof(str_hash) );	
	str_ht_make( h );
	while( 1 ){
		scanf("%d",&a);
		if ( a == -1 ) break;
		w = malloc( sizeof(char)* 20);
		scanf("%s",w);
		str_ht_insert( h , w , a );
	}
	print_content(h);
	while( 1 ){
		scanf("%d",&a);
		if ( a == -1 ) break;
		w = malloc( sizeof(char)* 20);
		scanf("%s",w);
		a = str_ht_find( h , w , a );
		printf("ANTES HABIAN %d\n", a);
	}
	print_content(h);

}