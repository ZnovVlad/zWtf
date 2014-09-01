/*-------------------------------------------------------------------------*/
/*
   @file	zwtf.c
   @author	V. Znov
   @brief	The program shows you who took all the available space on your disk?
   @brief	Эта программа показывает, кто занял все свободное место на диске.
*/
/*--------------------------------------------------------------------------*/

#include "zwtf.h"

#define TMP_FILE "temp.tmp"
#define OUT_FILE "report.txt"
#define OPT_DIR "/A /-C /Q /S /T:C"
#define BUFFER_SMALL 10
#define NUM_BIG_FILES "10"
#define BUFFER_BIG 1000
#define CARRENT_DIR_ID ":\\"

 FILE *outFile, *tmpFile;
 

 struct globalArgs_t globalArgs;
 
/*--------------------------------------------------------------------------*/
/*   @func    main() 														*/
/*--------------------------------------------------------------------------*/
int main(int argc, char *argv[]){
 
	globalArgs.workPath 	= " ";
	globalArgs.outputFile 	= OUT_FILE;
	globalArgs.numBigFiles	= NUM_BIG_FILES;
/*-------------------------------------------------------------------------*/
/**
  @brief    Parser command-line arguments
  @param    argc
  @param    argv
  @param    optString
  @return   optarg
*/
/*--------------------------------------------------------------------------*/	
 static const char *optString = "p:f:n:h?";
 int	opt = 0;
 
 opt = getopt( argc, argv, optString );
	while( opt != -1 ) {
		switch( opt ) {
			case 'p':
				globalArgs.workPath = optarg;
				break;
			case 'f':
				globalArgs.outputFile = optarg;
				break;
			case 'n':
				globalArgs.numBigFiles = optarg;
				break;
			case 'h':	
			case '?':
				display_help();
				break;
			default:
				
				break;
		}

		opt = getopt( argc, argv, optString );
	}

/*-------------------------------------------------------------------------*/
/**
  @brief    string dir arguments generator
  @param    argc
  @param    argv
  @param    optString
  @return   char strSystem[]
*/
/*--------------------------------------------------------------------------*/	
 
 char	tempBuffer[BUFFER_SMALL];
 size_t strSystemSize = snprintf(tempBuffer, sizeof(tempBuffer), "dir %s "OPT_DIR" > "TMP_FILE, globalArgs.workPath);
// fprintf(stderr,"%d %d %d\n", __LINE__, sizeof(tempBuffer), strSystemSize);
 
 char	strSystem[strSystemSize+1];
 sprintf(strSystem, "dir %s "OPT_DIR" > "TMP_FILE, globalArgs.workPath);
// fprintf(stderr,"%d %d %d\n", __LINE__, sizeof(strSystem), strSystemSize);
 
/*-------------------------------------------------------------------------*/
/**
  @brief    system ()
  @param    strSystem[]
  @return   0/!0 - sucess/not sucess
*/
/*--------------------------------------------------------------------------*/	

 if (!system(strSystem)) {
	if((tmpFile=fopen(TMP_FILE, "r")) == NULL) { 				
		fprintf(stderr, "Cannot open " TMP_FILE " file!\n");
		return 1;
		}
}
 else {
	fprintf(stderr, "Cannot use %s command!\n", strSystem);
	return 1;
}
 if((outFile=fopen(globalArgs.outputFile, "w")) == NULL) { 				
	fprintf(stderr, "Cannot create output file!");
	return 1;
	}
/*-------------------------------------------------------------------------*/
/**
  @brief    search carrent dir, used tmpFile.
  @param	tmpFile
  @param	CARRENT_DIR_ID
  @param	globalArgs.workPath
  @return   0/!0 - sucess/not sucess
*/
/*--------------------------------------------------------------------------*/	
 char buffer_big[BUFFER_BIG];
// int i = 0;
 fgets(buffer_big, BUFFER_BIG -1, tmpFile);							
 while(!feof(tmpFile)) {	
//	i = i + 1;
//	fprintf(stdout, "%d %d %s \n", __LINE__, i, buffer_big);	
	if (!strncmp(buffer_big, CARRENT_DIR_ID, sizeof(CARRENT_DIR_ID))) {
		strncpy(globalArgs.workPath, buffer_big + sizeof(CARRENT_DIR_ID), sizeof(globalArgs.workPath)-1);
		break;
		}

	fgets(buffer_big, BUFFER_BIG -1, tmpFile);					
	}

// fprintf(stdout, "%d %d %d %d %s\n", __LINE__, i, sizeof(CARRENT_DIR_ID), sizeof(globalArgs.workPath), globalArgs.workPath);	
 
/* while(!feof(cfg_file)) {
	ptr_tmp = strchr(buffer_big, DELIMITER_CHARACTER);
	if (ptr_tmp == NULL) {
		fprintf(stderr, "No delimiter character %s\n",  buffer_big);
		return;
	}	
	else {
		delimiter_place =(ptr_tmp - buffer_big) + 1; 
	}
	
	if (!strncmp(buffer_big, ptr_string, delimiter_place - 1)) {
		strncpy(ptr_array, buffer_big + delimiter_place, size - 1); 
		ptr_array[size - 1] = '\0'; 
		return;
	}	
	else {
		fgets(buffer_big, BIG_BUFFER_SIZE - 1, cfg_file);
	}	
	
	}
*/	
/*-------------------------------------------------------------------------*/
/**
  @brief    Parcer OUT_FILE file.
  @param    strSystem[]
  @param	tmpFile
  @param	outFile
  @param	globalArgs.workPath
  @return   0/!0 - sucess/not sucess
*/
/*--------------------------------------------------------------------------*/	
/*	fgets(buffer_big, BUFFER_BIG -1, tmpFile);					
 while(!feof(tmpFile)) {											
	if (strncmp(buffer_big, CARRENT_DIR_ID, sizeof(CARRENT_DIR_ID))) {
		fputs(buffer_big, outFile);
	}
	else {															
		fputs(okato, outFile);									
		fputs("\n", outFile);
		fputs(buffer_big, outFile); 
	}
	fgets(buffer_big, BIG_BUFFER_SIZE -1, tmpFile);				
	}
*/	
 fclose(tmpFile);
// remove(TMP_FILE);
 return 0;
}

/*--------------------------------------------------------------------------*/
/*   @func    display_help() 												*/
/*--------------------------------------------------------------------------*/

void display_help(void) {
 fprintf(stdout, "zwtf supports the following command-line arguments:\n");
 fprintf(stdout, "zwtf [-p] [-f] [-h]\n");
 fprintf(stdout, "-p path, where you wonna make the scans\n");
 fprintf(stdout, "-f output file report\n");
 fprintf(stdout, "-n number biggest files in report\n");
 fprintf(stdout, "-h -? this help\n"); 
 fprintf(stdout, "Example: zwtf -pD:work -freport.txt\n");
 fprintf(stdout, "Default: zwtf scaning and create report file report.txt in current folder\n");
 fprintf(stdout, "         and output %s biggest files in report\n", globalArgs.numBigFiles );
 } 
 
/*--------------------------------------------------------------------------*/
/*   @func    () 												*/
/*--------------------------------------------------------------------------*/
