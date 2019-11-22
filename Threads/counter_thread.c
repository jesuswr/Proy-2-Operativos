#include <stdlib.h>
#include <stdio.h>
#include "str_hash.h"
#include "counter_thread.h"



void counter_thread(void * input){

	int n, MOD, begin;
	char ** file;

	FILE * fp;
	LIST L;
	str_hash H;
	pair_2 * cnt;
	char word[MAXSTRING];
	int id = 0;

	input = (INPUT *) input;

	n = input.n;
	MOD = input.mod;
	begin = input.begin;
	file = input.file;

	str_ht_make(&H);

	for(i = begin; i<n; i+=MOD){
		
		fp = fopen(file[i],"r");

		while(fscanf(fp,"%s",word)!=EOF){
			
			/* get key of string word in hash table and increase it by one*/
			int aux = str_ht_find( H, word, 1);

			if ( !aux ){
				str_ht_insert( H, word, 1);
				/* insert the string in the list */
				list_insert( L, word );			
			}
		}

		/* Close the file */
		fclose(fp);

	}


	cnt  =  (pair_2 *) malloc(sizeof(pair_2)*get_size_list(L));

	while(it != NULL){

		cnt[id].w = (char *) malloc(strlen(it->str)+1);
		strcpy(cnt[id].w, it->str);
		cnt[id++].c = str_ht_find( H, it->str, 0);
		
		it = it->next;

	}

	RET retval = malloc(sizeof(RET));

	retval.cnt = cnt;
	retval.size = id;

	pthread_exit( retval );

}