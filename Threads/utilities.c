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

/* HAY QUE ANADIR QUE INCLUYA Y BUSQUE EN LA TABLA DE HASH */
pair traverse_dir( char* dir_name , char** txt_names , int occupied , 
                   int *size , hash *h){
	DIR* dirp;
	struct stat sb;
  	struct dirent* de;
  	char* name;
  	int e;
  	pair get, ret;

  	dirp = opendir( dir_name );
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