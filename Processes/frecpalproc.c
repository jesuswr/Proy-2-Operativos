/*
*  File:       	frecpalproc.c
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the implementation of the frecpal with  
*               processes main
*  Date:      	23 / 11 / 19
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
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
#define HASH_SIZE 10007


int main( int argc , char **argv ){

	int n_proc, n_txt, e, i, j, aux, cnt, status,
	    cont, ind, n_words, fd[2], word_len, fd_fifo;

	char **txt_names;
	char *** txt_of_proc;
	char * word;
	sem_t *semaphore;
	str_hash h;
	str_list l;
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

	/* Create a non named pipe for reading the work of get_txt process */

	e = pipe(fd);

	error(e, "Error creating a non nominal pipe");


	/* This process will look for the txts and return them */
	e = fork();

	error(e, "Error creating get_txt process");

	if(e == 0){
		/* child */
		close(fd[0]);
		/*dup2(1, fd[1]);*/
		dup2(fd[1], 1);
		close(fd[1]);

		e = execl("get_txt", "get_txt", argv[2], NULL);

		error(e, "Error in execution of \"get_txt\"");

	}
	/* father continue */
	close(fd[1]);

	/* Wait the child process */
	e = wait(&e);

	error(e, "Error in child process get_txt");

	/* Get txt files names from child process via pipe */

	e = read_aux(fd[0], &n_txt, 4);

	error(e, NULL);

	txt_names = (char **) malloc(sizeof(char *) * n_txt);

	errorp(txt_names, NULL);

	for( i = 0; i < n_txt; ++i){

		e = read_aux(fd[0], &word_len, 4);
		error(e, NULL);

		txt_names[i] = (char *) malloc(sizeof(char) * (word_len + 1));
		errorp(txt_names[i], NULL);

		e = read_aux(fd[0], txt_names[i], word_len + 1);
		error(e, NULL);

	}

	close(fd[0]);

	/* Create named pipe for reading the work of the counter processes */
	unlink("myfifo");
	e = mkfifo("myfifo", 0666);
	error(e, NULL);

	/*fd_fifo = open("myfifo", O_RDONLY);*/

	/* Create named semaphore for counter processes coordination while writing in named pipe */
	sem_unlink("mySmph");
	semaphore = sem_open("mySmph", O_CREAT, 0666, 1);
	if (semaphore == SEM_FAILED) {
        perror("sem_open(3) failed");
        exit(-1);
    }

    e = sem_close(semaphore);
	error(e, NULL);

	/* If the number of processes given is greater than the number of txt files
	we will only use 1 thread for file, so the number of threads will become
	smaller */
	if ( n_proc > n_txt ) n_proc = n_txt;

	/* We store the files names of the txt's that every counter process in their corresponding array */
	
	txt_of_proc = (char ***) malloc(sizeof(char **) * n_proc);
	errorp(txt_of_proc, NULL);

	for( i = 0 ; i < n_proc ; ++i ){
		
		txt_of_proc[i] = (char **) malloc(sizeof(char *) * (n_txt / n_proc + ((n_txt % n_proc) > i + 1) + 1) );
		errorp(txt_of_proc[i], NULL);

		txt_of_proc[i][n_txt / n_proc + ((n_txt % n_proc) > i + 1)] = NULL;

	}

	for( i = 0 ; i < n_txt ; ++i ){

		txt_of_proc[i % n_proc][i / n_proc] = (char *) malloc(sizeof(char) * (strlen(txt_names[i]) + 1) );
		errorp(txt_of_proc[i % n_proc][i / n_proc], NULL);
		strcpy(txt_of_proc[i % n_proc][i / n_proc], txt_names[i]);

	}

	for( i = 0 ; i < n_proc ; ++i ){

		/* Here we create the counter processes and assing them the corresponding
		txts */

		e = fork();

		error(e, "Error creating count_words process");

		if( e == 0){
			/* child */
			e = execv("count_words", txt_of_proc[i]);

			error(e, "Error in execution of \"count_words\"");

		}
		
	}

	fd_fifo = open("myfifo", O_RDONLY);

	e = str_ht_make( &h );
	error(e, "Error allocating memory");
	
	make_str_list( &l );

	i = 0;

	/* In this loop we will take all the words given by the counter processes
	and store them in a hash table where we will update their frecuency and in 
	a list so we easily know how many and what words we have */
	while( i < n_proc ){

		read_aux(fd_fifo, &aux, 4);

		if(aux == -1){
			i++;
			continue;
		}

		word = (char *) malloc(sizeof(char) * (aux + 1));

		read_aux(fd_fifo, word, aux + 1);

		read_aux(fd_fifo, &cnt, 4);
		
		/* If the word already is in the hash, update its rep count */
		cont = str_ht_find( &h , word , cnt);
		
		/* Else insert it in the hash and in the list */
		if ( cont == 0 ){

			e = str_ht_insert( &h , word , cnt);
			error(e, "Error allocating memory");
			
			e = str_list_insert( &l , word  );
			error(e, "Error allocating memory");
		
		}
	}

	for( i = 0; i < n_proc; ++i ){
		e = wait(&status);
		error(e, NULL);
		if( WIFEXITED(status) ) error(WEXITSTATUS(status), NULL);
	}

	e = sem_unlink("mySmph");
	error(e, NULL);

	close(fd_fifo);
	unlink("myfifo");

	for( i = 0 ; i < n_txt ; ++i ){
		free( txt_names[i] );
	}
	free( txt_names );

	n_words = l.size;
	words = malloc( sizeof(pair_2)*n_words );
	errorp(words, "Error allocating memory");

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
		printf("%s %d\n", words[i].w, words[i].c );
	}

	return 0;
}
