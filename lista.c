#include "lista.h"

Lista crea_ls(){
    return NULL;
}
    
int push_ls(Lista* lis,void* nuevo){
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    if(n==NULL){
        return NO_MEM;
    }
    n->dat = nuevo;
    n->sig = *lis;
    *lis = n;
    return OK;
}

int push_end_ls(Lista* lis,void* nuevo){
    if(lis==NULL){
        return APU_INVAL;
    }
    Nodo* n = (Nodo*)malloc(sizeof(Nodo));
    Nodo* aux;
    if(n==NULL){
        return NO_MEM;
    }
    n->dat = nuevo;
    n->sig = NULL;
    if(*lis==NULL){//Si la lista esta vacia
        *lis = n;
        return OK;
    }
    aux = *lis;
    n->sig = *lis;
    while(n->sig!=NULL){
        aux = n->sig;
        n->sig = aux->sig;
    }
    aux->sig = n;
    return OK;
}

void print_ls(Lista lis,void (*func_print)(void* )){
    while (lis != NULL){
        (*func_print)(lis->dat);
        lis = lis->sig;
    }
}

void elim_ls(Lista* lis,void (*func_elim)(void* )){
    Nodo* aux = *lis;
    if(func_elim==NULL){
        while (aux != NULL){
            *lis = (*lis)->sig;
            free(aux);
            aux = *lis;
        }
    }
    else{
        while (aux != NULL){
            *lis = (*lis)->sig;
            (*func_elim)(aux->dat);
            free(aux);
            aux = *lis;
        }
    }
}