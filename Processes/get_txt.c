
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "utilities.h"
#include "hash.h"
#include "str_hash.h"
#include "str_list.h"
#include "hash_list.h"
#include "str_ht_list.h"
#include "error_handler.h"

#define HASH_SIZE 10007

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
	int size, i, e;	
	hash h;
	pair *p;

	p = (pair *) malloc( sizeof(pair) );
	errorp(p,NULL);

	size = 128;
	ht_make( &h , HASH_SIZE );
	dir_name = argv[1];

	file_names = (char **) malloc( sizeof(char *) * size );
	errorp(file_names, NULL);

	*p = traverse_dir( dir_name , file_names , 0 , &size , &h );
	errorp(p->f, "Error moving through the given directory");

	/* Return names of the found txt files using a pipe in file descriptor 1 */
	
	/* p->s : number of files to return  */
	e = write_aux(1, &(p->s), 4);
	error(e, NULL);

	/* (p->f)[i] : txt file name */
	for( i = 0; i < p->s; ++i){
		
		size = strlen((p->f)[i]);

		e = write_aux(1, &size, 4);
		error(e, NULL);

		e = write_aux(1, (p->f)[i], size);
		error(e, NULL);

		e = write_aux(1, "\0 ", 1);
		error(e, NULL);
	}

	return 0;
}