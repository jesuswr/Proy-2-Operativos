#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utilities.h"
#include "hash.h"

int main( int argc , char **argv ){
	int a, i, b, num_hilos;
	pair p;
	hash h;
	char **space;
	a = 1;
	scanf("%d",&num_hilos);

	ht_make(&h,num_hilos);
	space = malloc( sizeof( char* ) * a );
	p = traverse_dir( argv[1] , space , 0 , &a , &h );
	space = p.f;
	b = p.s;

	printf("%d %d\n",a , b );

	for( i = 0 ; i < b ; i++ ){
		printf("%d\n",i );
		printf("%s\n", space[i]);
	}
	
}