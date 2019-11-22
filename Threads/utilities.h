#include "hash.h"

#ifndef _UTILITIES_H
#define _UTILITIES_H

typedef struct{
	char **f;
	int s;
} pair;

typedef struct {
	char * w;
	int c;
} pair_2;

char* make_path( char* path , char* name );

pair traverse_dir( char* dir_name , char** txt_names , int occupied , 
	int *size , hash *h );

int word_frec_comparator( const void *p , const void *q );

#endif