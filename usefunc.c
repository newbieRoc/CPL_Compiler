/*
    File: usefunc.c
    useful function implemention in CPL compiler
*/

#include "globals.h"
#include "usefunc.h"

void print_token(tokenType token, const char *tokenString)
{
    switch(token) {
    case IF:
    case ELSE:
    case WHILE:
    case INT:
    case BOOLEAN:
        fprintf(listing, "reserved word: %s\n",tokenString);
        break;
    case ASSIGN:
        fprintf(listing, "=\n");
        break;
    case LT:
        fprintf(listing, "<\n");
        break;
    case PLUS:
        fprintf(listing, "+\n");
        break;
    case MINUS:
        fprintf(listing, "-\n");
        break;
    case TIMES:
        fprintf(listing, "*\n");
        break;
    case DIV:
        fprintf(listing, "/\n");
        break;
    case SEMI:
        fprintf(listing, ";\n");
        break;
    case NON:
        fprintf(listing, "!\n");
        break;
    case AND:
        fprintf(listing, "&\n");
        break;
    case OR:
        fprintf(listing, "||\n");
        break;
    case LPAREN:
        fprintf(listing, "(\n");
        break;
    case RPAREN:
        fprintf(listing, ")\n");
        break;
    case LBRACE:
        fprintf(listing, "{\n");
        break;
    case RBRACE:
        fprintf(listing, "}\n");
        break;
    case ENDFILE:
        fprintf(listing, "EOF\n");
        break;
    case ID:
        fprintf(listing, "ID, name = %s\n", tokenString);
        break;
    case NUM:
        fprintf(listing, "NUM, val = %s\n", tokenString);
        break;
    case ERROR:
        fprintf(listing, "ERROR: %s\n", tokenString);
        break;
    default:
        fprintf(listing, "unknow token", token);
    }
}

TreeNode *new_stmtNode(stmtKind stkind)
{
    int i;
    TreeNode *t;
    t = (TreeNode *)malloc(sizeof(TreeNode));
    if (t == NULL) {
        fprintf(listing, "out of memory at line %d", lineno);
    } else {
        for (i = 0; i < MAXCHILDLEN; i++) {
            t.child[i] = NULL;
        }
        t.sibling = NUll;
        t.nodeK = stmtK;
        t.kind.stmt = stkind;
        t.lineno = lineno;
    }
    return t;
}

TreeNode *new_expNode(expKind expkind)
{
    int i;
    TreeNode *t;
    t = (TreeNode *)malloc(sizeof(TreeNode));
    if (t == NULL) {
        fprinf(listing, "out of memory at line %d", lineno);
    } else {
        for (i = 0; i < MAXCHILDLEN; i++) {
            t.child[i] = NULL;
        }
        t.sibling = NULL;
        t.nodeK = expK;
        t.kind.exp = expkind;
        t.lineno = lineno;
    }
    
    return t;
}