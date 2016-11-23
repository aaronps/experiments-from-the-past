/* 
 * File:   slog.h
 * Author: krom
 *
 * Created on October 7, 2014, 10:48 AM
 */

#ifndef SLOG_H
#define	SLOG_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum 
{
    SLOG_DEBUG,
    SLOG_INFO,
    SLOG_WARNING
} LogLevel;

void slog_log(const LogLevel level, const char * format, ...);

#ifdef	__cplusplus
}
#endif

#endif	/* SLOG_H */

