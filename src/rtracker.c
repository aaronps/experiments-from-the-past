/* 
 * File:   rtracker.c
 * Author: krom
 *
 * Created on October 8, 2014, 2:36 PM
 */

//#include <stdio.h>
#include <stdlib.h>

#include "slog/slog.h"

#define RTRACKER_VESION_H (0)
#define RTRACKER_VESION_L (1)

#include "TrackingDevice.h"


/*
 * 
 */
int main(int argc, char** argv)
{
    slog_log(SLOG_INFO, "rtracker %u.%u start", RTRACKER_VESION_H, RTRACKER_VESION_L);
    
    TrackingDevice_Init();
    
    TrackingDevice_Insert("aaron", 0);
    TrackingDevice_Insert("hudong", 0);
    TrackingDevice_Insert("hujingli", 0);
    
    const char * ptr = TrackingDevice_FindNameByID(2);
    if ( ptr )
    {
        slog_log(SLOG_INFO, "Name of id(2) is '%s'", ptr);
    }
    
    TrackingDeviceID did;
    if ( TrackingDevice_FindIDByName("aaron", &did) )
    {
        slog_log(SLOG_INFO, "aaron's id is %u", did);
    }
    if ( TrackingDevice_FindIDByName("hujingli", &did) )
    {
        slog_log(SLOG_INFO, "hujingli's id is %u", did);
    }
    if ( TrackingDevice_FindIDByName("hudong", &did) )
    {
        slog_log(SLOG_INFO, "hudong's id is %u", did);
    }
    
    
    
    
    return (EXIT_SUCCESS);
}

