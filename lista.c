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