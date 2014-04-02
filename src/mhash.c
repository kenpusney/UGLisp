
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mhash.h"

static hcell_t* make_hcell(unsigned int hashcode,void* address,void* obj,unsigned size){
    hcell_t* cell = malloc(sizeof(hcell_t));
    cell->hash = hashcode;
    cell->v.unit = obj;
    cell->next = NULL;
    cell->key = copy_blob(address,size);
    return cell;
}

static unsigned int __primes[] = {
    13, 23, 31, 53, 61, 97, 193, 389, 769,
    1543, 3079, 6151, 12289, 24593, 
    49157, 98317
};

unsigned int next_prime(unsigned int num){
    int i = 0;
    while(__primes[i] < num) i++;
    if(i >= sizeof(__primes)/sizeof(unsigned int)) return num;
    return __primes[i];
}


unsigned int hash(unsigned char* buf, unsigned int len){
    unsigned int h = len;
    unsigned int step = (len>>5)+1;
    unsigned int i;
    for(i = len; i >= step; i-=step)
        h = (h ^ ((h<<5)+(h>>2))) + buf[i-1];
    if(h == 0) return 1;
    else return h;
}

void* copy_blob(void* buf,unsigned int size){
    unsigned int count = 0;
    unsigned char* begin = buf;
    unsigned char* dest = malloc(size+1);
    while((size--)+1){
        dest[count] = begin[count];
        count++;
    } 
    return dest;
}

htable_t* make_htable(unsigned int size, hsize_callback sizefn, hcmp_callback cmpfn){
    int i;
    htable_t* tbl = malloc(sizeof(htable_t));
    tbl->size = next_prime(size);
    tbl->cmpfn = cmpfn;
    tbl->sizefn = sizefn;
    tbl->colunms = malloc(sizeof(hcolunm_t)*(tbl->size));
    for(i = 0; i < tbl->size; ++i){
        tbl->colunms[i].cells = NULL;
    }
    return tbl;
}

static
unsigned int __str_size_fn(void* buf){
    return strlen((char*)buf);
}

static
int __str_cmp_fn(void* buf1, void* buf2){
    return strcmp((char*)buf1,(char*)buf2) == 0;
}

htable_t* make_shtable(unsigned int size){
    return make_htable(size,__str_size_fn,__str_cmp_fn);
}

unsigned int hinsert(htable_t* tbl,char* key,void* obj){
//    hcmp_callback cmp = tbl->cmpfn;
    unsigned int code = hash((unsigned char*)key,tbl->sizefn(key));
    hcolunm_t* clm = &tbl->colunms[code%tbl->size];
    hcell_t* cell;
    if(clm->cells){
        cell = clm->cells;
        while(cell->next)cell = cell->next;
        cell->next = make_hcell(code,key,obj,tbl->sizefn(key));
    }else{
        clm->cells = make_hcell(code,key,obj,tbl->sizefn(key));
    }
    return code;
}

unsigned int hput(htable_t* tbl,char* key,MObject obj){
    return hinsert(tbl,key,(void*) obj);
}

void* hfind(htable_t* tbl,char* key){
    unsigned int code = hash((unsigned char*)key,tbl->sizefn(key));
    hcolunm_t* clm = &tbl->colunms[code%tbl->size];
    hcell_t* cell = clm->cells;
    while(cell){
        if(cell->hash == code && (tbl->cmpfn(cell->key,key))) return cell->v.unit;
        cell = cell->next;
    }
    return NULL;
}

MObject hget(htable_t* tbl,char* key){
    return (MObject)(hfind(tbl,key));
}

void* hremove(htable_t* tbl,char* key){
    unsigned int code = hash((unsigned char*)key,tbl->sizefn(key));
//    hcmp_callback cmp = tbl->cmpfn;
    hcolunm_t* clm = &tbl->colunms[code%tbl->size];
    hcell_t* cell = clm->cells;
    hcell_t* before = cell;
    void* data;
    if(cell && (cell->hash == code) && (tbl->cmpfn(cell->key,key))){
        if(cell->next) clm->cells = cell->next;
        data = cell->v.unit;
        free(cell->key);
        free(cell);
    }
    while(before &&(cell = before->next)){
        if(cell->hash == code && (tbl->cmpfn(cell->key,key))){
            before->next = cell->next;
            data = cell->v.unit;
            free(cell->key);
            free(cell);
            break;
        }
        before = before->next;
    }
    return data;
}

MObject hdelete(htable_t* tbl,char* key){
    return (MObject)(hremove(tbl,key));
}
