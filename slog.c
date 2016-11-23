#include "slog.h"

#include <stdio.h>

#include <time.h>
#include <stdarg.h>

void slog_log(const LogLevel level, const char * format, ...)
{
    char buf[2048];
    time_t curtime = time(0);

// unsafe in multithreaded
//    struct tm* loctime = localtime(&curtime);

    struct tm loctime;
#ifdef _WIN32
    // WARNING: This _localtime64_s could be better...
    _localtime64_s(&loctime, &curtime);
#else
    localtime_r(&curtime, &loctime);
#endif

    int timelen = strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S ", &loctime);
    
    va_list varg;
    va_start(varg, format);
    
    vsnprintf(&buf[timelen], sizeof(buf)-timelen-1, format, varg);
    
    puts(buf); // prints it, appends newline.
}