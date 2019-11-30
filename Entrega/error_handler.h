/*
* File:       error_handler.h
* Author:     Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
* Description:file that contains the signature of some useful functions
*			  to manage errors
* Date:       23 / 11 / 19
*/

#ifndef _ERROR_HANDLER_
#define _ERROR_HANDLER_

/*
* Function : error
* -----------------------------------------------------------
*   given an integer, print error information if the integer is negative,
*	the information printed can be given or by default.
*
*	e: error value
* 	str: error information
*/
void error(int e, char * str);


/*
* Function : errorp
* -----------------------------------------------------------
*   given a pointer, print error information if the pointer is NULL,
*	the information printed can be given or by default.
*
*	e: error value
* 	str: error information
*/
void errorp(void * e, char * str);

#endif