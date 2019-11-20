#include "hash.h"

#ifndef _UTILITIES_H
#define _UTILITIES_H

typedef struct{
	char **f;
	int s;
} pair;

char* make_path( char* path , char* name );

pair traverse_dir( char* dir_name , char** txt_names , int occupied , 
	int *size , hash *h );

#endif