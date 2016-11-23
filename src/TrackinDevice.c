#include <string.h>

#include "TrackingDevice.h"
#include "ccollections/ObjArray.h"

#include "slog/slog.h"

#include <stdio.h>

#include "GPS_Loc.h"

typedef struct
{
    TrackingDeviceID id; 
    char name[16];
} TrackingDeviceID_Record;

#define INITIAL_SIZE 4

static TrackingDeviceID last_id = 0;
static ObjArray * tracking_devices = 0;
static ObjArray * device_locations = 0;

int TrackingDevice_Init()
{
    slog_log(SLOG_INFO, "size of TrackingDeviceID_Record: %u",
                        (unsigned)sizeof(TrackingDeviceID_Record));
    
    slog_log(SLOG_INFO, "size of GPS_Loc: %u",
                        (unsigned)sizeof(GPS_Loc));
    
    tracking_devices = ObjArray_New(INITIAL_SIZE, sizeof(TrackingDeviceID_Record));
    device_locations = ObjArray_New(INITIAL_SIZE, sizeof(GPS_Loc));
}

int TrackingDevice_Insert(const char* name, TrackingDeviceID* out)
{
    const size_t namelen = strlen(name);
    if ( namelen > 15 )
    {
        slog_log(SLOG_INFO, "Name is longer than 15 (%u): '%s'", namelen, name);
        return 0;
    }
    
    TrackingDeviceID_Record * r;
    ObjArray_Foreach(tracking_devices, idx, r)
    {
        if ( strcmp(name, r->name) == 0 )
        {
            slog_log(SLOG_INFO, "Name '%s' already exists, id=%u", name, r->id);
            return 0;
        }
    }
    
    TrackingDeviceID_Record new_record;
    new_record.id = ++last_id;
    memcpy(new_record.name, name, namelen+1);
    
    GPS_Loc new_location = { 0, 0.0f, 0.0f };
    
    ObjArray_Append(tracking_devices, &new_record);
    ObjArray_Append(device_locations, &new_location);
    
    if ( out )
    {
        *out = new_record.id;
//        memcpy(out, new_record, sizeof(new_record));
    }
    
    return 1;
}

int TrackingDevice_FindIDByName(const char* name, TrackingDeviceID* out)
{
    TrackingDeviceID_Record * r;
    ObjArray_Foreach(tracking_devices, idx, r)
    {
        if ( strcmp(name, r->name) == 0 )
        {
            *out = r->id;
            return 1;
        }
    }
    return 0;
}

const char * TrackingDevice_FindNameByID(const TrackingDeviceID id)
{
    TrackingDeviceID_Record * r;
    ObjArray_Foreach(tracking_devices, idx, r)
    {
        if ( id == r->id )
        {
            return r->name;
        }
    }
    return 0;
}


