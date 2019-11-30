/*
* File:       error_handler.c
* Author:     Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
* Description:file that contains the implementation of some useful functions
*			  to manage errors
* Date:       23 / 11 / 19
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Function : error
* -----------------------------------------------------------
*   given an integer, print error information if the integer is negative,
*	the information printed can be given or by default.
*
*	e: error value
* 	str: error information
*/
void error(int e, char * str){
	if(e<0){
		if( str == NULL ) perror("Error");
		else perror(str);
		exit(-1);
	}
}

/*
* Function : errorp
* -----------------------------------------------------------
*   given a pointer, print error information if the pointer is NULL,
*	the information printed can be given or by default.
*
*	e: error value
* 	str: error information
*/
void errorp(void * e, char * str){
	if( e == NULL ){
		if( str == NULL ) perror("Error");
		else perror(str);
		exit(-1);
	}
}