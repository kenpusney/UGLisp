
#ifndef _MHASH_H
#define _MHASH_H

#include "mobject.h"

typedef struct hcell_t{
    unsigned int hash;
    union {
       MObject obj;
       void* unit; 
    } v;
    struct hcell_t* next;
} hcell_t;

typedef struct hcolunm_t{
    hcell_t* cells;
} hcolunm_t;

typedef struct htable_t{
    unsigned int size;
    hcolunm_t* colunms;
} htable_t;

unsigned int hash(char* key);
unsigned int ihash(int key);

int hash_ghw(int ghw);

unsigned int hinsert  (htable_t* tbl,char* key,void* obj);
unsigned int hput     (htable_t* tbl,char* key,MObject obj);
void*        hfind    (htable_t* tbl,char* key);
MObject      hget     (htable_t* tbl,char* key);
void*        hremvoe  (htable_t* tbl,char* key);
MObject      hdelete  (htable_t* tbl,char* key);
void*        hreset   (htable_t* tbl,char* key);
MObject      hupdate  (htable_t* tbl,char* key);
#endif //_MHASH_H
