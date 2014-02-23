
#include <stdlib.h>
#include "mhash.h"

static int __ghw = 31;
static hcell_t* make_hcell(unsigned int hashcode,void* address){
    hcell_t* cell = malloc(sizeof(hcell_t));
    cell->hash = hashcode;
    cell->v.unit = address;
    cell->next = NULL;
    return cell;
}


unsigned int hash(char* key){
    unsigned int code = 1;
    while(*key){
        code = code*__ghw + *key;
        key++;
    }
    return code;
}

unsigned int ihash(int key){
    unsigned int code = 1;
    while(key){
        code = code*__ghw + (key%10);
        key /= 10;
    }
    return code;
}

htable_t* make_htable(unsigned int size){
    int i;
    htable_t* tbl = malloc(sizeof(htable_t));
    tbl->size = size;
    tbl->colunms = malloc(sizeof(hcolunm_t)*size);
    for(i = 0; i < size; ++i){
        tbl->colunms[i].cells = NULL;
    }
    return tbl;
}

int hash_ghw(int ghw){
    if(ghw){
        return __ghw = ghw;
    }else{
        return __ghw;
    }
}

unsigned int hinsert(htable_t* tbl,char* key,void* obj){
    unsigned int code = hash(key);
    hcolunm_t* clm = &tbl->colunms[code%tbl->size];
    if(clm->cells){
        hcell_t* cell = clm->cells;
        while(cell->next)cell = cell->next;
        cell->next = make_hcell(code,obj);
        
    }else{
        clm->cells = make_hcell(code,obj);
    }
    return code;
}

unsigned int hput(htable_t* tbl,char* key,MObject obj){
    return hinsert(tbl,key,(void*) obj);
}

void* hfind(htable_t* tbl,char* key){
    unsigned int code = hash(key);
    hcolunm_t* clm = &tbl->colunms[code%tbl->size];
    hcell_t* cell = clm->cells;
    while(cell){
        if(cell->hash == code) return cell->v.unit;
        cell = cell->next;
    }
    return NULL;
}

MObject hget(htable_t* tbl,char* key){
    return (MObject)(hfind(tbl,key));
}

void* hremove(htable_t* tbl,char* key){
    unsigned int code = hash(key);
    hcolunm_t* clm = &tbl->colunms[code%tbl->size];
    hcell_t* cell = clm->cells;
    hcell_t* before = cell;
    void* data;
    if(cell && (cell->hash == code)){
        if(cell->next) clm->cells = cell->next;
        data = cell->v.unit;
        free(cell);
    }
    while(before &&(cell = before->next)){
        if(cell->hash == code){
            before->next = cell->next;
            data = cell->v.unit;
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
