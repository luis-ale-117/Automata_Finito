#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>

#define OK (0)
#define APU_INVAL (-1)
#define NO_MEM (-2)

typedef struct Nodo
{
    void * dat;
    struct Nodo* sig;
}Nodo;

typedef Nodo* Lista;

Lista crea_ls();
int push_ls(Lista* ls,void* nuevo);
int push_end_ls(Lista* ls,void* nuevo);
int pop_ls(Lista* ls,void** nuevo);
int pop_end_ls(Lista* ls,void** nuevo);
void print_ls(Lista, void (*print_node)(void* ));
void elim_ls(Lista* lis,void (*func_elim)(void* ));


#endif