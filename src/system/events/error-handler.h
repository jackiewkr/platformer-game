#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

enum ErrorLevel
{
        INFO,
        WARNING,
        FATAL
};

//TODO: add callback func for FATAL reporting that allows the exit as
//      cleanly as possible

/* err_report()
 * ============
 * Prints a message to stderr. If the ErrorLevel is WARNING or FATAL,
 * strerror() of the current errno value is printed as well. If
 * the ErrorLevel is FATAL, the program will end abruptly after printing
 * the message.
 */
void err_report( enum ErrorLevel, const char* msg );

#endif
