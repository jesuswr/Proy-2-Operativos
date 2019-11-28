
/*
*  Function : main of count_words
*  ----------------------
*  	Gets some file names, and counts the words in them
*  
*  	arg : input type, contains file names, starting index, size of
*		  array of names and the offset to his files
*/
int main( int argc, char ** argv ){

	/* ************************************* HASTA AQUI LLEGUE, TENGO SUE;O *****************************************************/

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
		exit(-1);
	}

	free( inp );

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
					exit(-1);
				}
				e = str_list_insert( &l , aux_w );
				if ( e < 0 ){
					printf("Error allocating memory.\n");
					exit(-1);
				}
			}
		}

		fclose( fp );
	}

	cnt = malloc( sizeof(pair_2)*(l.size) );
	if ( cnt == NULL ){
		printf("Error allocating memory.\n");
		exit(-1);
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
		exit(-1);
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