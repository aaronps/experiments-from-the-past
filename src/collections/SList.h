/* 
 * File:   SList.h
 * Author: krom
 *
 * Created on October 8, 2014, 6:46 PM
 */

#ifndef SLIST_H
#define	SLIST_H

#ifdef	__cplusplus
extern "C" {
#endif


typedef SList;

SList * SList_New(const int element_size);
void SList_Nelete(SList * list);

void * SList_NewElement(SList * list);


#ifdef	__cplusplus
}
#endif

#endif	/* SLIST_H */

