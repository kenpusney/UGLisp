
#ifndef _MHASH_H
#define _MHASH_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "object.h"

/**
Hashtable callback for item allocation size. <br/>
**input**: item. <br/>
**output**: size in byte to allocate & store the object key. <br/>
*/
typedef unsigned int (*hsize_callback)(void *);

/**
Hashtable callback for compare keys. <br/>
**input**: keys to compare. <br/>
**output**: 0 if they are equal, non-zero if they are equal. <br/>
*/
typedef int (*hcmp_callback)(void *, void *);
typedef unsigned int hash_code;

/**
* Hashtable cell type.
*/
typedef struct hcell_t
{
    unsigned int hash; ///< hashcode of the key
    void *key;         ///< key of the object
    union {
        MObject obj;      ///< MObject type
        void *unit;       ///< Generic type
    } v;                  ///< value of the object
    struct hcell_t *next; ///< **next** link of the object.
} hcell_t;

typedef struct hcolunm_t
{
    hcell_t *cells;
} hcolunm_t;

typedef struct htable_t
{
    unsigned int size;
    hsize_callback sizefn;
    hcmp_callback cmpfn;
    hcolunm_t *columns;
} htable_t, *HashTable;

/**
Create and initialize a hashtable.
@param [in] size hashtable potential size.
@param [in] sizefn callback to calculate and allocate key's size.
@param [in] cmpfn callback to compare keys.
*/
htable_t *make_htable(unsigned int size, hsize_callback sizefn, hcmp_callback cmpfn);

/**
Create and initialize a hashtable with C String type key.
@param [in] size hashtable potential size.
*/
htable_t *make_shtable(unsigned int size);
/**
Hash method to calculate fixed length buffer.
@param [in] buf buffer to hash
@param [in] len length of the buf
@return the hash code
*/
unsigned int hash(unsigned char *buf, unsigned int len);
/**
Return a prime near but bigger than num.
@param [in] num the number
@return a prime
*/
unsigned int next_prime(unsigned int num);
/**
Alloc and copy the blob.
@param [in] buf buffer 
@param [in] size the size of buffer
@return duplicated blob
*/
void *copy_blob(void *buf, unsigned int size);
unsigned int hinsert(htable_t *tbl, char *key, void *obj);
void *hfind(htable_t *tbl, char *key);
void *hremove(htable_t *tbl, char *key);
void *hreset(htable_t *tbl, char *key);

unsigned int hput(htable_t *tbl, char *key, MObject obj);
MObject hget(htable_t *tbl, char *key);
MObject hdelete(htable_t *tbl, char *key);
MObject hupdate(htable_t *tbl, char *key);

/**
Destroy a hashtable, and free all memory allocated
include **keys**, **cells**, **columns** and **table**.
@param [in, out] tbl hashtable to destroy
*/
void hdestroy(htable_t *tbl);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //_MHASH_H
