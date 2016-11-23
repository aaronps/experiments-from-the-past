/* 
 * File:   main.c
 * Author: krom
 *
 * Created on October 7, 2014, 10:51 AM
 */

//#include <stdio.h>
#include <stdlib.h>

#include "slog.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    slog_log(SLOG_INFO, "hello %d", 45);
    slog_log(SLOG_INFO, "and another %s with %d", "thing", 33);

    return (EXIT_SUCCESS);
}

