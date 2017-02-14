
#ifndef _MHASH_H
#define _MHASH_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "mobject.h"

typedef unsigned int (*hsize_callback)(void *);
typedef int (*hcmp_callback)(void *, void *);
typedef unsigned int hash_code;

typedef struct hcell_t
{
    unsigned int hash;
    void *key;
    union {
        MObject obj;
        void *unit;
    } v;
    struct hcell_t *next;
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
} htable_t;

htable_t *make_htable(unsigned int size, hsize_callback sizefn, hcmp_callback cmpfn);
htable_t *make_shtable(unsigned int size);

unsigned int hash(unsigned char *buf, unsigned int len);
unsigned int next_prime(unsigned int num);
void *copy_blob(void *buf, unsigned int size);

unsigned int hinsert(htable_t *tbl, char *key, void *obj);
void *hfind(htable_t *tbl, char *key);
void *hremove(htable_t *tbl, char *key);
void *hreset(htable_t *tbl, char *key);

unsigned int hput(htable_t *tbl, char *key, MObject obj);
MObject hget(htable_t *tbl, char *key);
MObject hdelete(htable_t *tbl, char *key);
MObject hupdate(htable_t *tbl, char *key);

void hdestroy(htable_t *tbl);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //_MHASH_H
