/*
*	File:			counter_thread.h
*	Author: 		Jesus Wahrman 15-11540 , Neil Villamizar 15-11523
*	Description:	file that contains the signature of some structures
*					used for a thread function that counts words
*	Date:			23 / 11 / 19
*/


#include "utilities.h"

#ifndef _COUNTER_THREAD_
#define _COUNTER_THREAD_

typedef struct {
	int n, MOD, begin;
	char ** file;
} input;

typedef struct {
	pair_2 * cnt;
	int size;
} ret;

#endif