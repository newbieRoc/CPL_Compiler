/*****************************************
	globals.h
	global types and vars for CPL compiler
******************************************/

#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAXRESERVED 5
#define MAXCHILDLEN 3

/*****************************************
	define token type including key words
	identifier special symbols
******************************************/
typedef enum {
	ERROR, ENDFILE,	
	/*reserved words*/
	IF, ELSE, WHILE, BOOLEAN, INT,
	/*mulchar identifier*/
	ID,NUM,
	/*special symbols*/
	ASSIGN, LT, PLUS, MINUS, TIMES, DIV, SEMI,
	NON, AND, OR,  
	LPAREN, RPAREN, LBRACE, RBRACE 
}tokenType; 

/*source code text file*/
extern FILE *source;
/*listing output text file*/
extern FILE *listing;
/*code */
extern FILE *code;

/*source line number for listing*/
extern int lineno;

/*********syntax parse tree*************
   nodeKind, stmtKind, 	expKind, expType
****************************************/
typedef enum {
	stmtK, expK
}nodeKind;
typedef enum {
	ifK, whileK, assignK
}stmtKind;
typedef enum {
	opK, idK, constK
}expKind;

typedef struct treeNode {
	struct treeNode *child[MAXCHILDLEN];
	struct treeNode *sibling;
	int lineno;
	nodeKind nodeK;
	union Kind{
		stmtKind stmt;
		expKind  exp;
	}kind;

	union Attr {
		tokenType op;
		int val;
		char *name;
	}attr;
}TreeNode;

//typedef struct treeNode TreeNode;

/*****************flags*****************/

extern int traceScan;

#endif
