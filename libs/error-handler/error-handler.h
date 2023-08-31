#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_
/**
 * error_handler.h
 * ==============
 * Library responsible for handling errors by printing to stderr and setting
 * errno correctly
 *
 * By Jacqueline W.
 * Licensed under the Mozilla MPLv2
 **/

enum ErrorLevel
{
        INFO,
        WARNING,
        FATAL
};

/*
 * err_report()
 * ============
 * Reports the current errno and strerror values to stderr along with any
 * specified message.
 */
void err_report( enum ErrorLevel, const char* msg );

#endif
