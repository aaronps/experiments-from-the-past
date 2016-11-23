/* 
 * File:   main.c
 * Author: krom
 *
 * Created on October 8, 2014, 7:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "ccollections/PtrArray.h"
#include "ccollections/ObjArray.h"

typedef struct
{
    int id;
    char name[16];
    char phone[12];
} Person;

void dump_objarray(ObjArray * oa)
{
    printf("idx\tid\tname\tphone\n");
    Person * p;
    ObjArray_Foreach(oa, index, p)
    {
        printf("%u\t%u\t%s\t%s\n", index, p->id, p->name, p->phone);
    }
}

void test_objarray()
{
    Person person1 = { 1, "aaron",   "18618318118" };
    Person person2 = { 2, "mapanke", "12222333335" };
    Person person3 = { 3, "hudong",  "13333344444" };
    Person person4 = { 4, "nobody",  "55558444413" };
    Person person5 = { 5, "thextra", "66666666666" };
    
    printf("Size of person: %u\n", (unsigned)sizeof(Person));
    
    ObjArray * oa = ObjArray_New(4, sizeof(Person));
    
    ObjArray_Append(oa, &person1);
    ObjArray_Append(oa, &person2);
    ObjArray_Append(oa, &person3);
    ObjArray_Append(oa, &person4);
    ObjArray_Append(oa, &person5);
    
    dump_objarray(oa);
    
    ObjArray_Delete(oa);
}

void dump_ptrarray(PtrArray * pa)
{
    puts("dump start--");
    
    PtrArray_foreach(pa, idx)
    {
        printf("Element %u is '%s'\n", idx, (char*)PtrArray_getItem(pa, idx));
    }

    puts("--dump end");
}

void test_ptrarray()
{
    char * s1 = "S1";
    char * s2 = "S22";
    char * s3 = "S333";
    char * s4 = "S4444";
    char * s5 = "S55555";
    
    PtrArray * pa = PtrArray_new(4);
    PtrArray_append(pa, s1);
    PtrArray_append(pa, s2);
    PtrArray_append(pa, s3);
    PtrArray_append(pa, s4);
    PtrArray_append(pa, s5);
    
    dump_ptrarray(pa);
    
    PtrArray_foreach(pa, idx)
    {
        const char * p = PtrArray_getItem(pa, idx);
        if ( strlen(p) <= 3 )
        {
            printf("(b)At %d is <= 3: %s\n", idx, p);
        }
    }
    
    PtrArray_removeAt_stable(pa, 2);
    
    dump_ptrarray(pa);
    
    PtrArray_delete(pa);
}


/*
 * 
 */
int main(int argc, char** argv)
{
//    test_ptrarray();
    test_objarray();
    
    return (EXIT_SUCCESS);
}
