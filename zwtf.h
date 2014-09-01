/*-------------------------------------------------------------------------*/
/*
   @file	zwtf.c
   @author	V. Znov
   @brief	The program shows you who took all the available space on your disk?
   @brief	Эта программа показывает, кто занял все свободное место на диске.
*/
/*--------------------------------------------------------------------------*/

#ifndef _ZWTF_H_
#define _ZWTF_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 


/*-------------------------------------------------------------------------*/
/**
  @brief    Arguments object

  This object contains a list of string/string associations. Each
  association is identified by a unique string key.
 */
/*-------------------------------------------------------------------------*/
 struct globalArgs_t {
	char *	workPath;				/* -p work path option */
	char *	outputFile;				/* -f output file option*/
	char *	numBigFiles;			/* -n number biggest files in report*/
 };
 
 /*-------------------------------------------------------------------------*/
/**
  @brief    Display command-line arguments help.

 */
/*-------------------------------------------------------------------------*/

void display_help(void);

#endif
