/* 
 * File:   PtrArray.h
 * Author: krom
 *
 * Created on October 9, 2014, 8:05 PM
 */

#ifndef PTRARRAY_H
#define	PTRARRAY_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void ** DataPtr;

typedef struct
{
    DataPtr  data;   
    unsigned capacity;
    unsigned top;
} PtrArray;

#define PtrArray_filter(list,ptype,condition, code ) { \
    ptype * item; \
    for ( unsigned i = 0, e = list->top; i < e; i++ ) \
        if ( (item = list->data[i]) && condition ) code \
}

#define PtrArray_foreach_item(list, idx, item) \
    for ( unsigned idx = 0; idx < list->top; idx++ ) \
        if ( (item = list->data[idx]) )

#define PtrArray_foreach_item_down(list, idx, item) \
    for ( unsigned idx = list->top; idx && (item = list->data[--idx]); )

#define PtrArray_foreach(list, idx) for ( unsigned idx = 0; idx < list->top; idx++ )

#define PtrArray_getItem(list, idx) list->data[idx]

int PtrArray_init(PtrArray * const list, const unsigned capacity);

void PtrArray_deinit(PtrArray * list);

PtrArray * PtrArray_new(const unsigned capacity);

void PtrArray_delete(PtrArray * list);

int PtrArray_grow(PtrArray * list, const unsigned ammount);

#define PtrArray_push PtrArray_append
void PtrArray_append(PtrArray * list, void * element);

void * PtrArray_pop(PtrArray * list);

void PtrArray_removeAt(PtrArray * list, const unsigned index);

void PtrArray_removeAt_stable(PtrArray * list, const unsigned index);


#ifdef	__cplusplus
}
#endif

#endif	/* PTRARRAY_H */

