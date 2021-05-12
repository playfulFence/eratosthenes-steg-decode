#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#define ERROR_OUTPUT "CHYBA: "


//Definition of "warning" function 
void warning_msg(const char *fmt, ...)
{
    va_list w_msg_args;
    va_start(w_msg_args, fmt);

    fprintf(stderr, ERROR_OUTPUT);

    vfprintf(stderr, fmt, w_msg_args);

    va_end(w_msg_args);
}

//Definition of "error" function, which ends program
void error_exit(const char *fmt, ...)
{
    va_list w_msg_args;
    va_start(w_msg_args, fmt);

    fprintf(stderr, ERROR_OUTPUT);

    vfprintf(stderr, fmt, w_msg_args);

    va_end(w_msg_args);

    exit(1);
}



