#include <stdlib.h>
#include <stdio.h>
#include "str_hash.h"
#include "local_merge.h"

/*  el main la llama varias veces
	los argumentos deben estar inicializados
*/

int  local_merge(pthread_t thread, str_hash * H, LIST * L){

	RET * retval;

	if(pthread_join( counter_thread, (void **) & retval)!=0){
		printf("erroooooooooooor \n");
		return -1;
	}
	retval = (RET *) retval
	n = retval->size;
	pairs = retval->cnt;
	for(i=0; i<n; i++){
		f = str_ht_find( H, pairs[i].w, pairs[i].c);
		if( !f ){
			str_ht_insert(H, pairs[i].w, pairs[i].c);
			list_insert(L, pairs[i].w);
		}
	}

	return 0;
}
