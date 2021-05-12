// ppm.h
// Řešení IJC-DU1, příklad b), 20.3.2021
// Autor: Kirill Mikhailov, FIT
// Přeloženo: Apple Clang version 12.0.0

#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>


// Declaration of struct ppm from ppm.c
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

// Declarations of functions from ppm.c
void moveCursor(FILE* fp);
struct ppm* ppm_read(const char * filename);
void ppm_free(struct ppm *p);
#endif
