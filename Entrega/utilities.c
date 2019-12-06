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
    if ( ret == NULL ){
        return NULL;
    }
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
        if ( name == NULL ){
            ret.f = NULL;
            ret.s = -1;
            return ret;
        }
  		e = lstat( name , &sb );
  		if ( e < 0 ){
            ret.f = NULL;
            ret.s = -1;
            return ret;
        }

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
	closedir(dirp);
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


/*
*	Function : int_to_char
*	-----------------------------------------------------------
*		stores the first byte of the int to the first position of the
*		array, then right shifts the int bits by 8 and repeats the
*		process now with the second position of the array, then for
*		the third and finally for the fourth
*
*		x : int to store
*		ret : pointer to the array of chars
*/
void int_to_char(int x, char * ret){

	int i;

	for(i=0; i<4; i++){
		ret[i] = (char) (x)&255;
		x >>= 8;
	}

}

/*
*	Function : str_to_int
*	-----------------------------------------------------------
*		saves the bits from each character in the int, to do so
*		it saves the bits from the fourth char, then left shifts 8 bits
*		and saves the bits from the third, then left shifts 8 bits and
*		repeats for the second and first char
*
*		c : pointer to the array of chars
*
*		returns an int that has the bits of the array
*/
int str_to_int( char* c  ){
	int x, i;
	x = 0;
	for( i = 3 ; i >= 0 ; i-- ){
		x = x << 8;
		x = x | (unsigned char)(c[i]);
	}
	return x;
}

/*
*	Function : write_aux
*	-----------------------------------------------------------
*		makes calls to syscall read until all len is read or an 
*		error occurs
*
*		fd : file descriptor of the file to write
*		len : ammount of chars to write from buf
*		buf : array of chars to write from
*
*		returns 0 in case of success or -1 in case of failure		
*/
int write_aux(int fd, unsigned char * buf,  int len){
	int e , len2 = 0;
	while(len2 < len){
		e = write(fd, buf + len2, len-len2);
		if ( e <= 0 ) return -1;
		len2 += e;
	}
	return len;
}

/*
*	Function : read_aux
*	-----------------------------------------------------------
*		makes calls to syscall read untile l chars are read and 
*		stored in buf or an error occurs
*
*		fd : file descriptor of the file to read from
*		len : ammount of chars to read 
*		buf : array of chars to write 
*
*		returns 0 in case of success or -1 in case of failure		
*/
int read_aux( int fd , unsigned char * buf , int len ){
	int l2, e;
	l2 = 0;
	while ( l2 < len ){
		e = read( fd , buf + l2 , len - l2 );
		if ( e <= 0 ) return e;
		l2 = l2 + e;
	}
	return len;
}
