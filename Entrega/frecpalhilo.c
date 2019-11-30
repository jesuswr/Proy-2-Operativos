/*
*  File:       	frecpalhilo.c
*  Author:     	Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*  Description: file that contains the implementation of the frecpal with  
*               threads main
*  Date:      	23 / 11 / 19
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "utilities.h"
#include "hash.h"
#include "str_hash.h"
#include "str_list.h"
#include "hash_list.h"
#include "str_ht_list.h"
#include "counter_thread.h"
#include "error_handler.h"

#define MAX_WORD_LEN 100
#define HASH_SIZE 10007

pthread_mutex_t mtx;
pthread_t end = 0;

/*
*  Function : get_txt
*  ----------------------
*  	Gets a directory name and extracts all files with the extention
*  	txt 
*  
*  	arg : name of the directory
*/
void* get_txt( void *arg ){
	char *dir_name;
	char **file_names;
	int size, i;	
	hash h;
	pair *p;

	p = malloc( sizeof(pair) );
	size = 128;
	ht_make( &h , HASH_SIZE );
	dir_name = (char *)arg;
	file_names = malloc( sizeof(char *) * size );

	*p = traverse_dir( dir_name , file_names , 0 , &size , &h );
	errorp( p->f , "Error moving through the given directory.\n");

	pthread_exit( p );
}


/*
*  Function : count_words
*  ----------------------
*  	Gets some file names, and counts the words in them
*  
*  	arg : input type, contains file names, starting index, size of
*		  array of names and the offset to his files
*/
void* count_words( void *arg ){
	input *inp;
	int i, begin , n , mod, aux, e;
	FILE *fp;
	str_list l;
	str_hash H;
	pair_2 * cnt;
	char word[MAX_WORD_LEN];
	int id = 0;
	char **file_names;
	char *aux_w;
	str_node *it, *it2;
	int ind;
	ret *retval;
	str_ht_list_node *np, *np2;

	inp = ( input * )arg;
	mod = inp->MOD;
	begin = inp->begin;
	n = inp->n;
	file_names = inp->file;
	e = str_ht_make( &H );
	error( e , "Error allocating memory.\n");

	free( inp );

	make_str_list( &l );

	for( i = begin; i < n ; i += mod ){

		fp = fopen( file_names[i] , "r" );
		errorp( fp , "Error opening a file.\n");

		while( fscanf( fp , "%s" , word ) != EOF ){

			aux = str_ht_find( &H , word , 1 );
			if ( aux == 0 ){
				aux_w = malloc( strlen(word) + 1);
				strcpy( aux_w , word );
				e = str_ht_insert( &H , aux_w , 1 );
				error( e , "Error allocating memory.\n");

				e = str_list_insert( &l , aux_w );
				error( e , "Error allocating memory.\n");
			}
		}

		fclose( fp );
	}

	cnt = malloc( sizeof(pair_2)*(l.size) );
	errorp( cnt , "Error allocating memory.\n");
	

	ind = 0;
	it = l.head;

	while( it != NULL ){
		cnt[id].w = it->word;
		cnt[id].c = str_ht_find( &H , it->word , 0 );
		id++;
		it2 = it;
		it = it->next;
		free( it2 );
	}

	retval = malloc( sizeof(ret) );
	errorp( retval , "Error allocating memory.\n");
	

	retval->cnt = cnt;
	retval->size = l.size;


	for( i = 0 ; i < 10007 ; i++ ){
		np = (H.hash_table[i]).head;
		while( np != NULL ){
			np2 = np;
			np = np->next;
			free(np2);
		}
	}

	free( H.hash_table );

	pthread_mutex_lock(&mtx);

	end = pthread_self();

	pthread_exit( retval );
}


int main( int argc , char **argv ){

	int n_threads, n_txt, e, i, j, cont, ind, n_words;
	pthread_t *count_threads, txt_thread, thr_id;
	char **txt_names;
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

	n_threads = atoi( argv[1] );

	if ( n_threads == 0 ){
		printf("Unvalid number of threads.\n");
		return -1;
	}

	/* This thread will look for the txts and return them */
	e = pthread_create( &txt_thread , NULL , get_txt , argv[2] );
	error( e , "Error creating txt_thread.\n");


	e = pthread_join( txt_thread , (void **)&p_aux );
	error( e , "Error joining txt_thread.\n");

	p_aux = (pair *)p_aux;
	n_txt = p_aux->s;
	txt_names = p_aux->f;
	free(p_aux);

	pthread_mutex_init(&mtx, NULL);

	/* If the number of threads given is greater than the number of txt files
	we will only use 1 thread for file, so the number of threads will become
	smaller */
	if ( n_threads > n_txt ) n_threads = n_txt;
	
	count_threads = malloc( sizeof(pthread_t) * n_threads );
	errorp( count_threads , "Error allocating memory.\n");


	for( i = 0 ; i < n_threads ; i++ ){
		inp = malloc( sizeof(input) );
		errorp( inp , "Error allocating memory.\n");
		
		inp->n = n_txt;
		inp->MOD = n_threads;
		inp->begin = i;
		inp->file = txt_names;

		/* Here we create the counter threads and assing them the corresponding
		txts */
		e = pthread_create( &count_threads[i] , NULL , count_words , (void *)inp );
		error( e , "Error creating count_words thread.\n");
	}

	/* Here we allocate space for the counter threads output */
	count_rets = malloc( sizeof(ret*) * n_threads );
	errorp( count_rets , "Error allocating memory.\n");
	

	i = 0;

	while(i < n_threads){
		while(!end);
		thr_id = end;
		end = 0;
		e = pthread_join( thr_id ,(void **)&count_rets[i] );
		error( e , "Error joining count_words thread.\n");
		
		count_rets[i] = (ret*)count_rets[i];
		i++;
		pthread_mutex_unlock(&mtx);
	}


	e = str_ht_make( &h );
	error( e , "Error allocating memory.\n");
	
	make_str_list( &l );

	/* In this loop we will take all the words given by the counter threads
	and store them in a hash table where we will update their frecuency and in 
	a list so we easily know how many and what words we have */
	for( i = 0 ; i < n_threads ; i++ ){
		for( j = 0 ; j < count_rets[i]->size ; j++ ){
			/* If the word already is in the hash, update its rep count */
			cont = str_ht_find( &h , count_rets[i]->cnt[j].w , count_rets[i]->cnt[j].c);
			
			/* Else insert it in the hash and in the list */
			if ( cont == 0 ){
				e = str_ht_insert( &h , count_rets[i]->cnt[j].w , count_rets[i]->cnt[j].c);
				error( e , "Error allocating memory.\n");
				
				
				e = str_list_insert( &l , count_rets[i]->cnt[j].w  );
				error( e , "Error allocating memory.\n");
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
	errorp( words , "Error allocating memory.\n");
	

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
		printf("%s %d\n", words[i].w , words[i].c );
	}

	return 0;
}
