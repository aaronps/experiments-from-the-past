#include "ccollections/PtrArray.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int PtrArray_init(PtrArray * const list, const unsigned capacity)
{
    list->data = calloc(capacity, sizeof(DataPtr));
    if ( list->data )
    {
        list->capacity = capacity;
        list->top = 0;
        return 1;
    }
    return 0;
}

void PtrArray_deinit(PtrArray * list)
{
    if ( list->data )
    {
        free(list->data);
        list->data = 0;
        list->capacity = 0;
        list->top = 0;
    }
}

PtrArray * PtrArray_new(const unsigned capacity)
{
    PtrArray * ptr = calloc(1,sizeof(PtrArray));
    if ( ptr )
    {
        if ( ! PtrArray_init(ptr, capacity) )
        {
            free(ptr);
            ptr = 0;
        }
    }
    return ptr;
}

void PtrArray_delete(PtrArray * list)
{
    PtrArray_deinit(list);
    free(list);
}

int PtrArray_grow(PtrArray * list, const unsigned ammount)
{
    void * newdata = realloc(list->data, (list->capacity + ammount) * sizeof(DataPtr));
    if ( newdata )
    {
        if ( newdata != list->data )
        {
            free(list->data);
            list->data = newdata;
        }
        list->capacity += ammount;
        return 1;
    }
    return 0;
}

#define PtrArray_push PtrArray_append
void PtrArray_append(PtrArray * list, void * element)
{
    if ( list->top == list->capacity && ! PtrArray_grow(list, list->capacity/2) )
    {
        // no more space and couldn't grow
        return;
    }
    
    list->data[list->top] = element;
    ++list->top;
}

void * PtrArray_pop(PtrArray * list)
{
    if ( list->top )
    {
        return list->data[--list->top];
    }
    return 0;
}

void PtrArray_removeAt(PtrArray * list, const unsigned index)
{
    if ( index < list->top )
    {
        const unsigned newtop = list->top - 1;
        if ( index < newtop )
        {
            list->data[index] = list->data[newtop];
        }
        list->top = newtop;
    }
}

void PtrArray_removeAt_stable(PtrArray * list, const unsigned index)
{
    if ( index < list->top )
    {
        const unsigned newtop = list->top - 1;
        if ( index < newtop )
        {
            memmove(&list->data[index], &list->data[index+1], sizeof(DataPtr) * (list->top-index) );
        }
        list->top = newtop;
    }
}
