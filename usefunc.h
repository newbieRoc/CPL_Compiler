/**************************************
    File: usefunc.h
    useful function 
***************************************/

#ifndef _usefunc_h
#define _usefunc_h

/****************************************
    print a token and its lexeme string
    into a listing file
*****************************************/
void print_token(tokenType , const char *);

/**********************************************
    create a new statement node for syntax
    parse tree construction and initialization.
***********************************************/
TreeNode *new_stmtNode(stmtKind );

/**********************************************  
    create a new expression node for syntax
    parse tree construction and initialization.
***********************************************/
TreeNode *new_expNode(expKind );


#endif