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
    Nodo* aux,*aux_sig;
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
    aux_sig = *lis;
    while(aux_sig!=NULL){
        aux = aux_sig;
        aux_sig = aux->sig;
    }
    aux->sig = n;
    n->sig = aux_sig;
    return OK;
}
int pop_ls(Lista* lis,void** nuevo){
    if(lis==NULL || nuevo==NULL){
        return APU_INVAL;
    }
    if(*lis==NULL){
        *nuevo=NULL;
        return OK;
    }
    Nodo* aux = *lis;
    *nuevo = (*lis)->dat;
    *lis = (*lis)->sig;
    free(aux);
    return OK;
}
int pop_end_ls(Lista* lis,void** nuevo){
    if(lis==NULL || nuevo==NULL){
        return APU_INVAL;
    }
    if(*lis==NULL){
        *nuevo=NULL;
        return OK;
    }
    Nodo* aux = *lis;
    Nodo* aux_s = *lis;
    if(aux_s->sig==NULL){
        *nuevo = aux_s->dat;
        *lis = aux_s->sig;
        free(aux_s);
        return OK;
    }
    while (aux_s->sig != NULL){
        aux = aux_s;
        aux_s = aux->sig;
    }
    *nuevo = aux_s->dat;
    aux->sig = aux_s->sig;
    free(aux_s);
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