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
        //printf("Estado: %s\n",edo_leido);
        agrega_estado_AF(a,edo_leido);
        /*PROCESA EL ESTADO (agregalo al AF)*/
        edo_leido = strtok(NULL,", \n");
    }
    return OK;
}

int extrae_acept_arch(FILE* f, AF* a){
    if(f==NULL || a==NULL){
        return APU_INVAL;
    }
    char linea[MAX_TAM_LINEA]="";
    if(fgets(linea,MAX_TAM_LINEA,f)==NULL){
        return EOF;
    }
    char* edo_leido = strtok(linea,", \n");
    while (edo_leido!=NULL){
        //printf("Aceptacion: %s\n",edo_leido);
        agrega_aceptacion_AF(a,edo_leido);
        /*PROCESA EL ESTADO (agregalo al AF)*/
        edo_leido = strtok(NULL,", \n");
    }
    return OK;
}

int extrae_inicio_arch(FILE* f, AF* a){
    if(f==NULL || a==NULL){
        return APU_INVAL;
    }
    char linea[MAX_TAM_LINEA]="";
    if(fgets(linea,MAX_TAM_LINEA,f)==NULL){
        return EOF;
    }
    char* edo_leido = strtok(linea,", \n");
    while (edo_leido!=NULL){
        //printf("Inicio: %s\n",edo_leido);
        pon_inicio_AF(a,edo_leido);
        /*PROCESA EL ESTADO (agregalo al AF)*/
        edo_leido = strtok(NULL,", \n");
    }
    return OK;
}

int extrae_alfa_arch(FILE* f, AF* a){
    if(f==NULL || a==NULL){
        return APU_INVAL;
    }
    char linea[MAX_TAM_LINEA]="";
    char alfabeto[MAX_TAM_LINEA]="";
    if(fgets(linea,MAX_TAM_LINEA,f)==NULL){
        return EOF;
    }
    char* alfa_aux = strtok(linea,", \n");
    while (alfa_aux!=NULL){
        strcat(alfabeto,alfa_aux);
        /*PROCESA EL ESTADO (agregalo al AF)*/
        alfa_aux = strtok(NULL,", \n");
    }
    pon_alfabeto_AF(a,alfabeto);
    return OK;
}

int extrae_func_arch(FILE* f, AF* a){
    if(f==NULL || a==NULL){
        return APU_INVAL;
    }
    char linea[MAX_TAM_LINEA]="";
    char* edo_origen;
    char* simb;
    char* edo_destino;
    while(feof(f)!=EOF){
        if(fgets(linea,MAX_TAM_LINEA,f)==NULL){
            break;
        }
        edo_origen = strtok(linea,", \n");
        simb = strtok(NULL,", \n");
        edo_destino = strtok(NULL,", \n");
        if(edo_origen==NULL || simb==NULL || edo_destino==NULL){
            break;
        }
        agrega_funcion_AF(a,edo_origen,edo_destino,*simb);
    }
    return OK;
}