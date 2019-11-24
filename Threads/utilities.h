/*
*	File:			utilities.h
*	Author: 		Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*	Description:	file that contains the signature of some useful
*					functions used in frecpalhilos
*	Date:			23 / 11 / 19
*/


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

/*
*	Function : make_path
*	-----------------------------------------------------------
*		given two arrays of chars, creates a path of the form "path/name"
*
*		path : pointer to the path name
*		name : pointer to the file name

*		returns an array of chars of the form path/name	
*/
char* make_path( char* path , char* name );


/*
* Function : traverse_dir
* -----------------------------------------------------------
*   Moves through a directory and finds all the txt files, ignoring the 
*   duplicates inodes
*
*   dir_name: name of the directory
*   txt_names: array to save the names of the txts
*   occupied: number of occupied positions in the array
*   size: size of the array
*   h: hash table of ints
*
*   returns the address of the array and the amount of names in it
*/
pair traverse_dir( char* dir_name , char** txt_names , int occupied , 
	int *size , hash *h );


/*
* Function : word_frec_comparator
* -----------------------------------------------------------
*   Function to compare two pair_2 elements, that contain word and rep count
*   for that word
*
*   p : pair_2 number 1 to compare
*   q : pair_2 number 2 to compare
*
*   returns > 0 if q is greater than p, < 0 if p is greater than q and 0 if 
*   they are the same
*/
int word_frec_comparator( const void *p , const void *q );

#endif