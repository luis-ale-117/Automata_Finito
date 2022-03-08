#include "archaf.h"

int extrae_edos_arch(FILE* f, AF* a){
    if(f==NULL || a==NULL){
        return APU_INVAL;
    }
    char linea[MAX_TAM_LINEA]="";
    if(fgets(linea,MAX_TAM_LINEA,f)==NULL){
        return EOF;
    }
    char* edo_leido = strtok(linea,", \n");
    while (edo_leido!=NULL){
        printf("Estado: %s\n",edo_leido);
        agrega_estado_AF(a,edo_leido);
        /*PROCESA EL ESTADO (agregalo al AF)*/
        edo_leido = strtok(NULL,", \n");
    }
    return OK;
}