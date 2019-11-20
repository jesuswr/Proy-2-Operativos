#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utilities.h"

int main( int argc , char **argv ){
	int a, i, b;
	pair p;
	char **space;
	a = 2;
	space = malloc( sizeof( char* ) * a );
	p = traverse_dir( argv[1] , space , 0 , &a );
	space = p.f;
	b = p.s;
	printf("%d %d\n",a , b );

	for( i = 0 ; i < b ; i++ ){
		printf("%d\n",i );
		printf("%s\n", space[i]);
	}
	
}