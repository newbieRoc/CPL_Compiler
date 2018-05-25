/*
    File: scan.h
    The scanner interface for CPL compiler
*/

#ifndef _SCAN_H
#define _SCAN_H
/*the maximum size of a token*/
#define MAXTOKENLEN 40

/*tokenString array stores the lexeme of each token*/
extern char tokenString[MAXTOKENLEN+1];

/*function getToken returns the next token in source file*/
tokenType get_token(void);


#endif