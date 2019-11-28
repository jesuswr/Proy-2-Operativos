
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "utilities.h"

/*
*  Function : get_txt
*  ----------------------
*  	Gets a directory name and extracts all files with the extention
*  	txt 
*  
*  	argv[1] : name of the directory
*	argc    : 2
*/
int main( int argc , char **argv ){

	char *dir_name;
	char **file_names;
	int size, i;	
	hash h;
	pair *p;

	p = malloc( sizeof(pair) );
	size = 128;
	ht_make( &h , HASH_SIZE );
	dir_name = argv[1];
	file_names = malloc( sizeof(char *) * size );

	*p = traverse_dir( dir_name , file_names , 0 , &size , &h );

	if ( p->f == NULL ){
		printf("Error moving through the given directory.\n");
		exit (-1);
	}

	/* Retornar algo en un pipe (fd 1) */
	/* p.s */
	write(1, &(p->s), 4);
	/*write(1, " ", 1);*/
	/* for(p.s) p.f */
	for( i = 0; i < p->s; ++i){
		size = strlen((p->f)[i]);

		write(1, &size, 4)
		write(1, (p->f)[i], size);
		write(1, "\0 ", 1);
	}

	return 0;
}