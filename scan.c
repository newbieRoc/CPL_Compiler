/*
    File scan.c
    the scanner implementation for the CPL compiler
*/

#include "globals.h"
#include "scan.h"
#include "usefunc.h"

/*states in scanner DFA*/
typedef enum {
    START, INCOMMENT, INNUM, INID, INOR, DONE

}stateType;

/*lexeme of identifer or reserved word*/
char tokenString[MAXTOKENLEN+1];

/*BUFLEN = length of the input buffer 
for source code lines*/
#define BUFLEN 256

static char lineBuf[BUFLEN];/*holds the current line*/
static int linePos = 0; /*current position in lineBuf*/
static int bufSize = 0; /*current size of buf*/
static int EOF_flag = FALSE; /*corrects ungetNextChar behavior on EOF*/

/*get_next_char fetches the next non-blank char
from lineBuf, reading in a new line if lineBuf is
exhausted*/
static int get_next_char(void)
{
    if (!(linePos < bufSize)) {
        lineno++;
        if (fgets(lineBuf, BUFLEN-1, source)) {
            bufSize = strlen(lineBuf);
            linePos = 0;
            return lineBuf[linePos++];
        } else {
            EOF_flag = TRUE;
            return EOF;
        }
    } else {
        return lineBuf[linePos++];
    }
}

/*unget_next_char backtracks one char in lineBuf*/
static void unget_next_char(void)
{
    if (!EOF_flag)
        linePos--;
}

/*lookup table of resered words*/
static struct {
    char *str;
    tokenType tok;
} reservedWords[MAXRESERVED] = {
    {"if", IF}, {"else", ELSE}, {"while", WHILE},
    {"int", INT}, {"boolean", BOOLEAN}
};

/*lookup an identifier to see if it is a reserved word*/
static tokenType reserved_lookup(char *s)
{
    int i;
    for (i = 0; i < MAXRESERVED; i++) {
        if (!strcmp(s, reservedWords[i].str))
            return reservedWords[i].tok;
    }
    return ID;
}

/*primary function of the scanner*/
/*function get_token returns the next token in the file*/
tokenType get_token(void)
{
    int tokStrIndex = 0;

    tokenType currentTokenType;
    stateType state = START;
    /*flag to save to tokenString*/
    int save;

    while (state != DONE) {
        int c = get_next_char();
        save = TRUE;
        switch(state) {
        case START:
            if (isdigit(c)) {
                state = INNUM;
            } else if (isalpha(c)) {
                state = INID;
            } else if (c == '|') {
                state = INOR;
            } else if (c == ' ' || c == '\t' || c == '\n') {
                save = FALSE;
            } else if (c == '/') {
                save = FALSE;
                state = INCOMMENT;
            } else {
                state = DONE;
                switch(c) {
                case EOF:
                    save = FALSE;
                    currentTokenType = ENDFILE;
                    break;
                case '=':
                    currentTokenType = ASSIGN;
                    break;
                case '+':
                    currentTokenType = PLUS;
                    break;
                case '-':
                    currentTokenType = MINUS;
                    break;
                case '*':
                    currentTokenType = TIMES;
                    break;
                case '<':
                    currentTokenType = LT;
                    break;
                case '!':
                    currentTokenType = NON;
                    break;
                case '&':
                    currentTokenType = AND;
                    break;
                case ';':
                    currentTokenType = SEMI;
                    break;
                case '(':
                    currentTokenType = LPAREN;
                    break;
                case ')':
                    currentTokenType = RPAREN;
                    break;
                case '{':
                    currentTokenType = LBRACE;
                    break;
                case '}':
                    currentTokenType = RBRACE;
                    break;
                default:
                    currentTokenType = ERROR;
                    break;
				}
            }
            break;
        case INOR:
            state = DONE;
            if (c == '|')
                currentTokenType = OR;
            else {
                /*error! backup in the input*/
                unget_next_char();
                save = FALSE;
                currentTokenType = ERROR;
            }
            break;
        case INNUM:
            if (!isdigit(c)) {
                state = DONE;
                save = FALSE;
                unget_next_char();
                currentTokenType = NUM;
            }
            break;
        case INID:
            if (!isalpha(c)) {
                state = DONE;
                save = FALSE;
                unget_next_char();
                currentTokenType = ID;
            }
            break;
        case INCOMMENT:
            if (c != '*') {
                state = DONE;
                save = TRUE;
                unget_next_char();
                unget_next_char();
                c = get_next_char();
                currentTokenType = DIV;
            } else if (c == '*') {
                save = FALSE;
                while ((c = get_next_char()) && c != '/')
                    ;
                state = START;
            }
            break;
        case DONE:
        default:
            fprintf(listing, "scanner error: state = %d\n", state);
            state = DONE;
            currentTokenType = ERROR;
            break;
        }

        if (save && (tokStrIndex < MAXTOKENLEN)) {
            tokenString[tokStrIndex++] = (char) c;
        }
        
        if (state == DONE) {
            tokenString[tokStrIndex] = '\0';
            if (currentTokenType == ID) {
                currentTokenType = reserved_lookup(tokenString);
            }
        }
    }

    if (traceScan) {
        fprintf(listing, "\t%d", lineno);
        print_token(currentTokenType, tokenString);
    }

    return currentTokenType;
}