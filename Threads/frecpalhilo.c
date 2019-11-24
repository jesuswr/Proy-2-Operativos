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

#define MAX_WORD_LEN 100
#define HASH_SIZE 10007


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

	if ( p->f == NULL ){
		return NULL;
	} 

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
	if ( e < 0 ){
		printf("Error allocating memory.\n");
		return NULL;
	}
	make_str_list( &l );

	for( i = begin; i < n ; i += mod ){

		fp = fopen( file_names[i] , "r" );
		if ( fp == NULL ){
			printf("Error opening file %s.\n", file_names[i]);
			continue;
		}

		while( fscanf( fp , "%s" , word ) != EOF ){

			aux = str_ht_find( &H , word , 1 );
			if ( aux == 0 ){
				aux_w = malloc( strlen(word) + 1);
				strcpy( aux_w , word );
				e = str_ht_insert( &H , aux_w , 1 );
				if ( e < 0 ){
					printf("Error allocating memory.\n");
					return NULL;
				}
				e = str_list_insert( &l , aux_w );
				if ( e < 0 ){
					printf("Error allocating memory.\n");
					return NULL;
				}
			}
		}

		fclose( fp );
	}

	cnt = malloc( sizeof(pair_2)*(l.size) );
	if ( cnt == NULL ){
		printf("Error allocating memory.\n");
		return NULL;
	}

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
	if ( retval == NULL ){
		printf("Error allocating memory.\n");
		return NULL;
	}

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

	pthread_exit( retval );
}


int main( int argc , char **argv ){

	int n_threads, n_txt, e, i, j, cont, ind, n_words;
	pthread_t *count_threads, txt_thread;
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

	e = pthread_create( &txt_thread , NULL , get_txt , argv[2] );

	if ( e < 0 ){
		printf("Error allocating memory.\n");
		return -1;
	}

	e = pthread_join( txt_thread , (void **)&p_aux );


	if ( e < 0 ){
		printf("Error joining get_txt thread.\n");
		return -1;
	}

	p_aux = (pair *)p_aux;
	if ( p_aux == NULL ){
		printf("Error in the given directory.\n");
		return -1;
	}
	n_txt = p_aux->s;
	txt_names = p_aux->f;
	free(p_aux);

	if ( n_threads > n_txt ) n_threads = n_txt;
	
	count_threads = malloc( sizeof(pthread_t) * n_threads );

	if ( count_threads == NULL ){
		printf("Error allocating memory.\n");
		return -1;
	}

	for( i = 0 ; i < n_threads ; i++ ){
		inp = malloc( sizeof(input) );
		if ( inp == NULL ){
			printf("Error allocating memory.\n");
			return -1;
		}
		inp->n = n_txt;
		inp->MOD = n_threads;
		inp->begin = i;
		inp->file = txt_names;

		e = pthread_create( &count_threads[i] , NULL , count_words , (void *)inp );
		if ( e < 0 ){
			printf("Error creating count_words thread.\n");
			return -1;
		}
	}

	count_rets = malloc( sizeof(ret*) * n_threads );
	if ( count_rets == NULL ){
		printf("Error allocating memory.\n");
		return -1;
	}

	for( i = 0 ; i < n_threads ; i++ ){
		e = pthread_join( count_threads[i] ,(void **)&count_rets[i] );
		if ( e < 0 ){
			printf("Error joining count_rets thread.\n");
			return -1;
		}
		count_rets[i] = (ret*)count_rets[i];
		if ( count_rets[i] == NULL ){
			printf("Error in the counting threads.\n");
			return -1;
		}
	}

	e = str_ht_make( &h );
	if ( e < 0 ){
		printf("Error allocating memory.\n");
		return -1;
	}
	make_str_list( &l );

	for( i = 0 ; i < n_threads ; i++ ){
		for( j = 0 ; j < count_rets[i]->size ; j++ ){
			
			cont = str_ht_find( &h , count_rets[i]->cnt[j].w , count_rets[i]->cnt[j].c);
			
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

	while( it != NULL ){
		words[ ind ].w = it->word;
		words[ ind ].c = str_ht_find( &h , it->word , 0 );

		ind++;
		it2 = it;
		it = it->next;
		free(it2);
	}

	for( i = 0 ; i < 10007 ; i++ ){
		np = (h.hash_table[i]).head;
		while( np != NULL ){
			np2 = np;
			np = np->next;
			free(np2);
		}
	}

	free( h.hash_table );

	qsort( words , n_words , sizeof( pair_2 ) , word_frec_comparator );

	for( i = 0 ; i < n_words ; i++ ){
		printf("%d %s\n", words[i].c , words[i].w );
	}

	return 0;
}
