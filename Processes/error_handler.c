/*
*	Error Handler
*
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void error(int e, char * str){
	if(e<0){
		if( str == NULL ) perror("Error");
		else perror(str);
		exit(-1);
	}
}

void errorp(void * e, char * str){
	if( e == NULL ){
		if( str == NULL ) perror("Error");
		else perror(str);
		exit(-1);
	}
}