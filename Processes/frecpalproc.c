/*
*  File:       	frecpalproc.c
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the implementation of the frecpal with  
*               threads main
*  Date:      	23 / 11 / 19
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "utilities.h"
#include "hash.h"
#include "str_hash.h"
#include "str_list.h"
#include "hash_list.h"
#include "str_ht_list.h"
#include "counter_thread.h"

#define MAX_WORD_LEN 100
#define HASH_SIZE 10007


int main( int argc , char **argv ){

	int n_proc, n_txt, e, i, j,
	    cont, ind, n_words, fd[2], word_len;

	char **txt_names;
	char *** txt_of_proc;
	pair *p_aux;
	str_hash h;
	input *inp;
	str_list l;
	ret **count_rets;
	str_node *it, *it2;
	str_ht_list_node *np, *np2;
	pair_2 *words;

	if ( argc != 3 ){
		printf("Error in the given input.\n");
		return -1;
	}

	n_proc = atoi( argv[1] );

	if ( n_proc == 0 ){
		printf("Unvalid number of processes.\n");
		return -1;
	}

	e = pipe(fd);

	if(e < 0){
		printf("Error creating a no nominal pipe\n");
		return -1;
	}

	/* This process will look for the txts and return them */
	e = fork();

	if ( e < 0 ){
		printf("Error creating get_txt process.\n");
		return -1;
	}

	if(e == 0){
		/* child */
		close(fd[0]);
		dup2(1, fd[1]);
		close(fd[1]);

		execl("get_txt", "get_txt", argv[2], NULL);
	}
	/* father continue */
	close(fd[1]);

	/* Wait the child process */
	e = wait(&e);

	if(e < 0){
		printf("Error in child process get_txt.\n");
		return -1;
	}

	/* Get txt files names from child process via pipe */

	e = read(fd[0], &n_txt, 4);

	txt_names = (char **) malloc(sizeof(char *) * n_txt);

	for( i = 0; i < n_txt; ++i){

		read(fd[0], &word_len, 4);
		txt_names[i] = (char *) malloc(sizeof(char) * (word_len + 1));
		read(fd[0], txt_names[i], word_len + 1);

	}

	close(fd[0]);


	/* If the number of processes given is greater than the number of txt files
	we will only use 1 thread for file, so the number of threads will become
	smaller */
	if ( n_proc > n_txt ) n_proc = n_txt;

	/* We store the files names of the txt's that every counter process in their corresponding array */
	
	txt_of_proc = (char ***) malloc(sizeof(char **) * n_proc);

	for( i = 0 ; i < n_proc ; ++i ){
		txt_of_proc[i] = (char **) malloc(sizeof(char *) * (n_txt / n_proc + ((n_txt % n_proc) > i + 1) + 2) );
		txt_of_proc[i][0] = int_to_str(n_txt / n_proc + ((n_txt % n_proc) > i + 1) + 1);
		txt_of_proc[i][n_txt / n_proc + ((n_txt % n_proc) > i + 1)] = NULL;
	}

	for( i = 0 ; i < n_txt ; ++i ){
		txt_of_proc[i % n_proc][i / n_proc + 1] = (char *) malloc(sizeof(char) * (strlen(txt_names[i]) + 1) );
		strcpy(txt_of_proc[i % n_proc][i / n_proc + 1], txt_names[i]);
	}

	for( i = 0 ; i < n_proc ; ++i ){

		/* Here we create the counter processes and assing them the corresponding
		txts */

		e = fork();

		if ( e < 0 ){
			printf("Error creating count_words process.\n");
			return -1;
		}

		if( e == 0){
			/* child */
			e = execv("count_words", txt_of_proc[i]);

			if( e < 0 ){
				printf("Error in execution of \"count_words\".\n");
				return -1;
			}

		}
		
	}

	/* DON'T FORGET TO WAIT THE CHILDS */
	/* DON'T FORGET TO CODE "int_to_str" SOMEWHERE */
	/* ****************************************** HASTA AQUI LLEGUE, TENGO SUE;O ********************************************************* */

	/* Here we allocate space for the counter threads output */
	count_rets = malloc( sizeof(ret*) * n_proc );
	if ( count_rets == NULL ){
		printf("Error allocating memory.\n");
		return -1;
	}

	for( i = 0 ; i < n_proc ; i++ ){
		e = pthread_join( count_threads[i] ,(void **)&count_rets[i] );
		if ( e < 0 ){
			printf("Error joining count_rets thread.\n");
			return -1;
		}
		count_rets[i] = (ret*)count_rets[i];
	}

	e = str_ht_make( &h );
	if ( e < 0 ){
		printf("Error allocating memory.\n");
		return -1;
	}
	make_str_list( &l );

	/* In this loop we will take all the words given by the counter threads
	and store them in a hash table where we will update their frecuency and in 
	a list so we easily know how many and what words we have */
	for( i = 0 ; i < n_proc ; i++ ){
		for( j = 0 ; j < count_rets[i]->size ; j++ ){
			/* If the word already is in the hash, update its rep count */
			cont = str_ht_find( &h , count_rets[i]->cnt[j].w , count_rets[i]->cnt[j].c);
			
			/* Else insert it in the hash and in the list */
			if ( cont == 0 ){
				e = str_ht_insert( &h , count_rets[i]->cnt[j].w , count_rets[i]->cnt[j].c);
				if ( e < 0 ){
					printf("Error allocating memory.\n");
					return -1;
				}
				
				e = str_list_insert( &l , count_rets[i]->cnt[j].w  );
				if ( e < 0 ){
					printf("Error allocating memory.\n");
					return -1;
				}
			}
		}
	}

	free( count_threads );
	for( i = 0 ; i < n_txt ; i++ ){
		free( txt_names[i] );
	}
	free( txt_names );

	n_words = l.size;
	words = malloc( sizeof(pair_2)*n_words );
	if ( words == NULL ){
		printf("Error allocating memory.\n");
		return -1;
	}

	ind = 0;
	it = l.head;
	/* Here we pass the words with their rep count from the hash and list, 
	to an array so we can sort it using c qsort, and free the list nodes */
	while( it != NULL ){
		words[ ind ].w = it->word;
		words[ ind ].c = str_ht_find( &h , it->word , 0 );
		ind++;
		it2 = it;
		it = it->next;
		free(it2);
	}

	/* Free the hash table space */
	for( i = 0 ; i < 10007 ; i++ ){
		np = (h.hash_table[i]).head;
		while( np != NULL ){
			np2 = np;
			np = np->next;
			free(np2);
		}
	}
	free( h.hash_table );

	/* Sort the words with a custom comparator, so we get the expected order */
	qsort( words , n_words , sizeof( pair_2 ) , word_frec_comparator );

	for( i = 0 ; i < n_words ; i++ ){
		printf("%d %s\n", words[i].c , words[i].w );
	}

	return 0;
}
