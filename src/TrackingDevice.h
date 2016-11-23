/* 
 * File:   TrackingDeviceID.h
 * Author: krom
 *
 * Has all the functions to register, delete, find the 
 * tracking device id or name.
 * 
 * Created on October 8, 2014, 4:43 PM
 */

#ifndef TRACKINGDEVICE_H
#define	TRACKINGDEVICE_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

// td = Tracking Device

typedef uint32_t TrackingDeviceID;

int TrackingDevice_Init();

int TrackingDevice_FindIDByName(const char * name, TrackingDeviceID * out);
const char * TrackingDevice_FindNameByID(const TrackingDeviceID id);
int TrackingDevice_Insert(const char * name, TrackingDeviceID * out);

#ifdef	__cplusplus
}
#endif

#endif	/* TRACKINGDEVICE_H */

