/* 
 * File:   ObjArray.h
 * Author: krom
 *
 * Created on October 10, 2014, 10:39 AM
 */

#ifndef OBJARRAY_H
#define	OBJARRAY_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
    void * data;
    unsigned capacity;
    unsigned top;
    unsigned obj_size;
}
/** Object Array, each field is private, don't use them */
ObjArray;

/**
 * Initializes the passed ObjArray, allocating initial memory for
 * <b>capacity</b>.
 * 
 * The Idea(tm) is that this can be used for stack allocated ObjArrays (note:
 * the real array is still on the heap) and for heap allocated ObjArrays.
 * ObjArray_new uses this method.
 * 
 * @param a The ObjArray to initialize
 * @param capacity The initial capacity of the array
 * @param obj_size The size of each object in the array.
 * @return 1 if memory allocation was successfull, 0 otherwise.
 */
int ObjArray_Init(ObjArray * const a, const unsigned capacity, const unsigned obj_size);

/**
 * Releases the heap memory used by this ObjArray.
 * 
 * @param a The ObjArray to deinit
 */
void ObjArray_Deinit(ObjArray * a);

/**
 * Creates a new ObjArray on the heap and initializes it.
 * 
 * @param capacity The initial capacity of the array
 * @param obj_size The size of each object in the array.
 * @return The created ObjArray or NULL
 */
ObjArray * ObjArray_New(const unsigned capacity, const unsigned obj_size);

/**
 * Frees the ObjArray memory, this must be an ObjArray created with
 * ObjArray_new.
 * 
 * The passed pointer won't be valid after this call.
 * 
 * @param a The ObjArray to free.
 */
void ObjArray_Delete(ObjArray * a);

/**
 * Appends an element to the end of the array by copying its data. It is a
 * different name for ObjArray_append.
 * 
 * @param a The ObjArray to loop.
 * @param element The element to copy.
 */
#define ObjArray_Push ObjArray_Append

/**
 * Appends an element to the end of the array by copying its data.
 * 
 * @param a The ObjArray to loop.
 * @param element The element to copy.
 */
void ObjArray_Append(ObjArray * a, void * element);


// @todo BUG: foreach can only be used on heap allocated, forgot the . and -> difference.
/**
 * Makes a for loop for each element in the array, upwards until the last one
 * used.
 * 
 * The intended usage is:
 * <pre><code>
 * ObjArray * oa;<br/>
 * SomeStructOrType * myOwnPointer;<br/>
 * ObjArray_foreach(oa, theIndex, myOwnPointer)<br/>
 * {<br/>
 * &nbsp;&nbsp;// use myOwnPointer here<br/>
 * }<br/>
 * </code></pre>
 * 
 * @param a The ObjArray to loop.
 * @param idx The <b>index</b> variable name used in the loop.
 * @param ptr The typed pointer variable that will get each element in the loop.
 */
#define ObjArray_Foreach(a, idx, ptr) ptr = a->data; for ( unsigned idx = 0; idx < a->top;++idx, ++ptr )

/**
 * Works the same as ObjArray_foreach but backwards.
 * 
 * @param a The ObjArray to loop.
 * @param idx The <b>index</b> variable name used in the loop.
 * @param ptr The typed pointer variable that will get each element in the loop.
 */
#define ObjArray_Foreach_Down(a, idx, ptr) ptr = a->data; for ( unsigned idx = a->top; idx; --idx, ++ptr )


#ifdef	__cplusplus
}
#endif

#endif	/* OBJARRAY_H */

