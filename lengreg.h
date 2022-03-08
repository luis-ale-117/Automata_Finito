#ifndef LENGREG_H
#define LENGREG_H

#include <stdio.h>
#include <string.h>
#include "lista.h"

#define ESTADO_INVAL -3

typedef char* Estado;
typedef char Simbolo;

typedef struct Regla{
    Estado edo;
    Simbolo simb;
}Regla;

typedef struct Funcion{
    Estado origen;
    Lista transiciones;
}Funcion;

typedef struct AF{
    Lista/*Estado*/ conjunto_edos;
    Lista/*Estado*/ aceptacion_edos;
    Estado inicio;
    Simbolo* alfabeto;
    Lista/*Funcion*/ func_transicion;
}AF;

void print_estado(Estado edo);
void print_estado_ls(void* edo);

Regla* crea_regla(Estado edo_dest, Simbolo simb);
void elim_regla(Regla* r);
void print_regla(Regla* r);

Funcion* crea_funcion(Estado edo);
void elim_funcion(Funcion* f);
int agrega_regla_funcion(Funcion* f, Estado edo_dest, Simbolo simb);
void print_funcion(Funcion* f);

AF* crea_AF();
void elim_AF(AF* a);
int agrega_estado_AF(AF* a,Estado edo);
int agrega_aceptacion_AF(AF* a, Estado edo);
int pon_inicio_AF(AF*, Estado edo);
int pon_alfabeto_AF(AF* a, Simbolo* alf);
int agrega_funcion_AF(AF* a, Estado edo_orig, Estado edo_dest, Simbolo simb);
void print_AF(AF* a);

int lee_simb_estado_AF(AF* a, Lista* edos_destino,Estado edo_actual, Simbolo simb);
int lee_simb_conjunto_AF(AF* a, Lista* edos_destino,Lista* edos_actuales, Simbolo simb);
int lee_cadena_AF(AF* a, Lista* edos_final,Simbolo* cad);
int cad_aceptada_AF(AF* a,Lista* edos_final/*,Lista* edos_acept*/);
//int repetidos_elim_aux(Lista* edos, Estado edo_elim);
//int repetidos_elim(Lista* edos);
#endif