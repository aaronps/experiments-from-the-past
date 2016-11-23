/* 
 * File:   gps_loc.h
 * Author: krom
 *
 * Created on October 8, 2014, 3:00 PM
 */

#ifndef GPS_LOC_H
#define	GPS_LOC_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    uint64_t timestamp;
    float x; // longitude
    float y; // latitude
} GPS_Loc;

#ifdef	__cplusplus
}
#endif

#endif	/* GPS_LOC_H */

