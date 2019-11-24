/*
* File:       utilities.c
* Author:     Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
* Description:file that contains the implementation of some useful
*             functions used in frecpalhilos
* Date:       23 / 11 / 19
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include "utilities.h" 
#include "hash.h"


/*
* Function : make_path
* -----------------------------------------------------------
*   given two arrays of chars, uses string.h basic functions to
*   create a new string with the format "path/name"
*
*   path : pointer to the path name
*   name : pointer to the file name

*   returns an array of chars of the form path/name 
*/
char* make_path( char* path , char* name ){
	char *ret = 
		(char *)malloc( strlen(path) + strlen(name)  + 2 );
	if ( strlen(path) == 0 ){
		strcpy( ret , name );	
	}
	else{
		strcpy( ret , path );
		ret[strlen(path)] = '/';
		strcpy(ret + strlen(path)+1, name);
	}
	return ret;
}


/*
* Function : traverse_dir
* -----------------------------------------------------------
*   Moves through a directory and finds all the txt files, ignoring the 
*   duplicates inodes, using a hash table to do so
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
                   int *size , hash *h){
	DIR* dirp;
	struct stat sb;
  	struct dirent* de;
  	char* name;
  	int e;
  	pair get, ret;

  	dirp = opendir( dir_name );
    if ( dirp == NULL ){
        ret.f = NULL;
        ret.s = -1;
        return ret;
    }
  	while ( de = readdir(dirp) ){
  		if ( strcmp(de->d_name,".") == 0 || strcmp(de->d_name,"..") == 0 ) 
  			continue;
  	
  		name = make_path( dir_name , de->d_name );
  		e = lstat( name , &sb );
  		
  		if ( ( sb.st_mode & __S_IFDIR ) == __S_IFDIR ){
  			/* If a directory was found, we traverse it and update values */
  			get = traverse_dir( name, txt_names , occupied , size , h);
  			if ( get.f == NULL ){
  				return get;
  			}
  			txt_names = get.f;
  			occupied = get.s;
  		}
  		else if ( ( sb.st_mode & __S_IFREG ) == __S_IFREG ){
  			if ( strcmp( (de->d_name) + ( strlen( de->d_name ) - 4 ) , 
  				".txt" ) == 0 ){
  			
            /* If the inode is in the hash table, we ignore it */
            if ( ht_find( h , sb.st_ino ) ){
                continue;
            }

            ht_insert( h , sb.st_ino );

  			if ( occupied == *size ){
  				/* If the maximun size of the array was reached,
  				   we allocate a new array with double size */
  				*size = *size << 1;
  				txt_names = realloc( txt_names , sizeof(char*)*(*size) );
  				if ( txt_names == NULL ){
  					    ret.f = NULL;
  					    ret.s = -1;
  					    return ret;
  				    }
  			    }
  			    txt_names[occupied++] = name;
  		    }
  		}
  	}

  	ret.f = txt_names;
  	ret.s = occupied;
  	return ret;
}


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
int word_frec_comparator( const void *p , const void *q ){
	pair_2 *l , *r;
	l = ( pair_2 * )p;
	r = ( pair_2 * )q;
	if ( l->c > r->c ) return -1;
	else if ( l->c < r->c ) return 1;
	return ( strcmp( l->w , r->w ) );
}