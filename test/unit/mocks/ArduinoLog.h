#pragma once

#include <stdio.h>
#include <stdarg.h>
#define CR "\n"

class Logger {

public:
    void fatal(const char *format, ...) {
        va_list args;
        va_start( args, format );
        vprintf(format, args);
        va_end(args);
        // printLevel(LOG_LEVEL_FATAL, msg, args...);
    }
    void error(const char *format, ...){
        va_list args;
        va_start( args, format );
        vprintf(format, args);
        va_end(args);
        // printLevel(LOG_LEVEL_FATAL, msg, args...);
    }

    void warning(const char *format, ...){
        va_list args;
        va_start( args, format );
        vprintf(format, args);
        va_end(args);
        // printLevel(LOG_LEVEL_FATAL, msg, args...);
    }

    void notice(const char *format, ...){
        va_list args;
        va_start( args, format );
        vprintf(format, args);
        va_end(args);
        // printLevel(LOG_LEVEL_FATAL, msg, args...);
    }

    void trace(const char *format, ...){
        va_list args;
        va_start( args, format );
        vprintf(format, args);
        va_end(args);
        // printLevel(LOG_LEVEL_FATAL, msg, args...);
    }

    void verbose(const char *format, ...){
        va_list args;
        va_start( args, format );
        vprintf(format, args);
        va_end(args);
        // printLevel(LOG_LEVEL_FATAL, msg, args...);
    }
  

};

extern Logger Log;