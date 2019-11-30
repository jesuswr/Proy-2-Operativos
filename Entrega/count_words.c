
/*
*  Function : main of count_words
*  ----------------------
*  	Gets some file names, and counts the words in them
*  
*  	argc : number of txt files 
*	argv : txt files names
*/

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

#define MAX_WORD_LEN 100

int main( int argc, char ** argv ){

	int i, n, aux, e, fd, size_word, cnt_word;
	FILE *fp;
	str_list l;
	str_hash H;
	char word[MAX_WORD_LEN];
	int id = 0;
	char **file_names;
	char *aux_w;
	str_node *it, *it2;
	str_ht_list_node *np, *np2;
	sem_t *semaphore;

	n = argc;
	file_names = argv;

	e = str_ht_make( &H );
	error(e, "Error allocating memory");

	make_str_list( &l );

	for( i = 0; i < n ; ++i ){

		fp = fopen( file_names[i] , "r" );
		if ( fp == NULL ){
			printf("Error opening file %s.\n", file_names[i]);
			continue;
		}

		while( fscanf( fp , "%s" , word ) != EOF ){

			aux = str_ht_find( &H , word , 1 );

			if ( aux == 0 ){

				aux_w = malloc( strlen(word) + 1);
				errorp(aux_w, NULL);
				strcpy( aux_w , word );
				e = str_ht_insert( &H , aux_w , 1 );
				error(e, "Error allocating memory");
				
				e = str_list_insert( &l , aux_w );
				error(e, "Error allocating memory");

			}

		}

		fclose( fp );
	}

	
	it = l.head;

	fd = open("myfifo", O_WRONLY);

	semaphore = sem_open("mySmph", O_RDWR);
	if (semaphore == SEM_FAILED) {
        perror("sem_open(3) failed");
        exit(-1);
    }

	while( it != NULL ){

		size_word = strlen(it->word);
		cnt_word = str_ht_find( &H , it->word , 0 );

		/* In section */
		e = sem_wait(semaphore);
		error(e, NULL);

		/* Critical Section */
		write_aux(fd, &size_word, 4);
		write_aux(fd, it->word, size_word);
		write_aux(fd, "\0", 1);
		write_aux(fd, &cnt_word, 4);
		/* end CS */

		/* out section */
		e = sem_post(semaphore);
		error(e, NULL);

		it2 = it;
		it = it->next;
		free( it2 );
	}

	/* In section */
	e = sem_wait(semaphore);
	error(e, NULL);
	/* CS */
	e = -1;
	write_aux(fd, &e, 4);
	/* end CS */
	/* out section */
	e = sem_post(semaphore);
	error(e, NULL);

	close(fd);
	e = sem_close(semaphore);
	error(e, NULL);

	/* free the hash table */
	for( i = 0 ; i < 10007 ; ++i ){
		np = (H.hash_table[i]).head;
		while( np != NULL ){
			np2 = np;
			np = np->next;
			free(np2);
		}
	}

	free( H.hash_table );

}