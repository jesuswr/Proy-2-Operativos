#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

int main( int argc , char **argv ){
	int s;
	pair_2 *ap;
	char* w;
	int c, i;
	
	scanf("%d",&s);
	ap = malloc( sizeof(pair_2)*s );

	for( i = 0 ; i < s ; i++ ){
		w = malloc( 30 );
		scanf("%d %s", &c , w );
		ap[i].w = w;
		ap[i].c = c;
	}

	qsort( ap , s , sizeof(pair_2) , word_frec_comparator);

	for( i = 0 ; i < s ; i++ ){
		printf("%d %s\n", ap[i].c , ap[i].w);
	}
}