/*
    File: main.c
*/

#include "globals.h"


#include "scan.h"

#include "usefunc.h"


int lineno = 0;
FILE *source;
FILE *listing;
FILE *code;

int traceScan = TRUE;


int main()
{
    char *pgm = "test.cpl";

    source = fopen(pgm, "r");
    if (source == NULL) {
        fprintf(stderr, "File %s not fount", pgm);
        exit(1);
    }
    listing = stdout;
    fprintf(listing, "\nCPL compilation: %s\n", pgm);
    while (get_token() != ENDFILE)
        ;

    return 0;
}