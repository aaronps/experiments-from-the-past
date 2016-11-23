#include "ccollections/ObjArray.h"
#include <stdlib.h>
#include <string.h>

static int ObjArray_Grow(ObjArray * a, const unsigned ammount)
{
    void * newdata = realloc(a->data, (a->capacity + ammount) * a->obj_size);
    if ( newdata )
    {
        if ( newdata != a->data )
        {
            free(a->data);
            a->data = newdata;
        }
        a->capacity += ammount;
        return 1;
    }
    return 0;
}

int ObjArray_Init(ObjArray * const a, const unsigned capacity, const unsigned obj_size)
{
    a->data = calloc(capacity, obj_size);
    if ( a->data )
    {
        a->capacity = capacity;
        a->top = 0;
        a->obj_size = obj_size;
        return 1;
    }
    return 0;
}

void ObjArray_Deinit(ObjArray * a)
{
    if ( a->data )
    {
        free(a->data);
        a->data = 0;
        a->capacity = 0;
        a->top = 0;
        a->obj_size = 0;
    }
}

ObjArray * ObjArray_New(const unsigned capacity, const unsigned obj_size)
{
    ObjArray * ptr = calloc(1, sizeof(ObjArray));
    if ( ptr )
    {
        if ( ! ObjArray_Init(ptr, capacity, obj_size) )
        {
            free(ptr);
            ptr = 0;
        }
    }
    return ptr;
}

void ObjArray_Delete(ObjArray * a)
{
    ObjArray_Deinit(a);
    free(a);
}

void ObjArray_Append(ObjArray * a, void * element)
{
    if ( a->top == a->capacity && ! ObjArray_Grow(a, a->capacity/2) )
    {
        // no more space and couldn't grow
        return;
    }
    
    memcpy(a->data + a->top * a->obj_size, element, a->obj_size);
    ++a->top;
}
