#include "lengreg.h"

void print_estado(Estado edo){
    printf("%s ",edo);
}
void print_estado_ls(void* edo){
    print_estado((Estado) edo);
}

Regla* crea_regla(Estado edo_dest, Simbolo simb){
    if(edo_dest==NULL){
        return NULL;
    }
    Regla* r = (Regla*)malloc(sizeof(Regla));
    Estado edo_aux = (Estado)malloc((strlen(edo_dest)+1)*sizeof(char));
    if(r!=NULL && edo_aux!=NULL){
        strcpy(edo_aux,edo_dest);
        r->edo = edo_aux;
        r->simb = simb;
    }
    return r;
}
int igualdad_regla(Regla* r, Estado edo, Simbolo simb){
    if(edo==NULL || r==NULL){
        return APU_INVAL;
    }
    return strcmp(r->edo,edo)==0 && r->simb==simb? 0 : 1;
}
void elim_regla(Regla* r){
    if(r==NULL){
        return;
    }
    free(r->edo);
    free(r);
    return;
}
void elim_regla_ls(void* r){
    elim_regla((Regla*)r);
}
void print_regla(Regla* r){
    printf("(%c,'%s') ",r->simb,r->edo);
}
void print_regla_ls(void* r){
    print_regla((Regla*)r);
}

MError* crea_merror(Estado edo_dest, Simbolo simb){
    if(edo_dest==NULL){
        return NULL;
    }
    MError* mer = (MError*)malloc(sizeof(MError));
    Estado edo_aux = (Estado)malloc((strlen(edo_dest)+1)*sizeof(char));
    if(mer!=NULL && edo_aux!=NULL){
        strcpy(edo_aux,edo_dest);
        mer->edo = edo_aux;
        mer->simb = simb;
    }
    return mer;
}
void elim_merror(MError* mer){
    if(mer==NULL){
        return;
    }
    free(mer->edo);
    free(mer);
    return;
}
void elim_merror_ls(void* mer){
    elim_regla((MError*)mer);
}
void print_merror(MError* mer){
    printf("%s(%c) ",mer->edo,mer->simb);
}
void print_merror_ls(void* mer){
    print_merror((MError*)mer);
}

Funcion* crea_funcion(Estado edo){
    if(edo==NULL){
        return NULL;
    }
    Funcion* nueva = (Funcion*)malloc(sizeof(Funcion));
    Estado edo_aux = (Estado)malloc((strlen(edo)+1)*sizeof(char));
    if(nueva!=NULL && edo_aux!=NULL){
        strcpy(edo_aux,edo);
        nueva->origen = edo_aux;
        nueva->transiciones = crea_ls();
    }
    return nueva;
}
int agrega_regla_funcion(Funcion* f, Estado edo_dest, Simbolo simb){
    if(f==NULL || edo_dest==NULL){
        return APU_INVAL;
    }
    Nodo* aux = f->transiciones;
    int ig = 1;//No exite a priori
    while (aux != NULL){
        ig = igualdad_regla((Regla*)aux->dat,edo_dest,simb);
        aux = aux->sig;
        if(ig==0){
            break;
        }
    }
    if(ig==0){//Ya exite la regla
        return OK;
    }
    Regla* r = crea_regla(edo_dest,simb);
    if(r==NULL){
        return NO_MEM;
    }
    return push_end_ls(&f->transiciones,r);
}
void elim_funcion(Funcion* f){
    if(f==NULL){
        return;
    }
    elim_ls(&f->transiciones,elim_regla_ls);
    free(f->origen);
    free(f);
    return;
}
void elim_funcion_ls(void* f){
    elim_funcion((Funcion*)f);
}
void print_funcion(Funcion* f){
    printf("%s -> ",f->origen);
    print_ls(f->transiciones,print_regla_ls);
    printf("\n");
}
void print_funcion_ls(void* f){
    print_funcion((Funcion*)f);
}

AF* crea_AF(){
    AF* a = (AF*)malloc(sizeof(AF));
    if(a!=NULL){
        a->conjunto_edos = crea_ls();
        a->aceptacion_edos = crea_ls();
        a->inicio = NULL;
        a->alfabeto = NULL;
        a->func_transicion = crea_ls();
    }
    return a;
}
void elim_AF(AF* a){
    if(a==NULL){
        return;
    }
    elim_ls(&a->conjunto_edos,free);
    elim_ls(&a->aceptacion_edos,free);
    free(a->inicio);
    free(a->alfabeto);
    elim_ls(&a->func_transicion,elim_funcion_ls);
}
int agrega_estado_AF(AF* a,Estado edo){
    if(a==NULL || edo==NULL){
        return APU_INVAL;
    }
    Nodo* aux = a->conjunto_edos;
    int ig = 1;//No exite a priori
    while (aux != NULL){
        ig = strcmp((Estado)aux->dat,edo);
        aux = aux->sig;
        if(ig==0){
            break;
        }
    }
    if(ig==0){//Ya exite el estado
        return OK;
    }
    Estado nuevo = (Estado)malloc((strlen(edo)+1)*sizeof(char));
    if(nuevo==NULL){
        return NO_MEM;
    }
    strcpy(nuevo,edo);
    return push_end_ls(&a->conjunto_edos,nuevo);
}
int existe_estado_AF(AF* a, Estado edo){
    if(a==NULL || edo==NULL){
        return APU_INVAL;
    }
    Nodo* aux = a->conjunto_edos;
    int ig = 1;//No exite a priori
    while(aux != NULL){
        ig = strcmp((Estado)aux->dat,edo);
        aux = aux->sig;
        if(ig==0){
            break;
        }
    }
    ig = ig!=0?ESTADO_INVAL:ig;
    return ig;
}
int agrega_aceptacion_AF(AF* a, Estado edo){
    if(a==NULL || edo==NULL){
        return APU_INVAL;
    }
    int ig = existe_estado_AF(a,edo);
    if(ig!=0){
        return ig;
    }
    Nodo* aux = a->aceptacion_edos;
    ig = 1;//A priori no existe el estado
    while (aux != NULL){
        ig = strcmp((Estado)aux->dat,edo);
        aux = aux->sig;
        if(ig==0){
            break;
        }
    }
    if(ig==0){//Ya el estado de aceptacion
        return OK;
    }
    Estado nuevo = (Estado)malloc((strlen(edo)+1)*sizeof(char));
    if(nuevo==NULL){
        return NO_MEM;
    }
    strcpy(nuevo,edo);
    return push_end_ls(&a->aceptacion_edos,nuevo);
}
int pon_inicio_AF(AF* a, Estado edo){
    if(a==NULL || edo==NULL){
        return APU_INVAL;
    }
    int ig = existe_estado_AF(a,edo);
    if(ig!=0){
        return ig;
    }
    if(a->inicio!=NULL){
        free(a->inicio);
    }
    
    Estado nuevo = (Estado)malloc((strlen(edo)+1)*sizeof(char));
    if(nuevo==NULL){
        return NO_MEM;
    }
    strcpy(nuevo,edo);
    a->inicio = nuevo;
    return OK;
}
int pon_alfabeto_AF(AF* a, Simbolo* alf){
    if(a==NULL || alf==NULL){
        return APU_INVAL;
    }
    Simbolo* nuevo = (Simbolo*)malloc((strlen(alf)+1)*sizeof(char));
    if(nuevo==NULL){
        return NO_MEM;
    }
    else if(a->alfabeto!=NULL){
        free(a->alfabeto);
    }
    strcpy(nuevo,alf);
    a->alfabeto = nuevo;
    return OK;
}
int inicializa_funciones_AF(AF* a){
    if(a==NULL){
        return APU_INVAL;
    }
    Nodo* aux_edo = a->conjunto_edos;
    Funcion* f_aux=NULL;
    Estado edo=NULL;
    while(aux_edo!=NULL){
        edo = (Estado)aux_edo->dat;
        f_aux = crea_funcion(edo);
        if(f_aux==NULL){
            return NO_MEM;
        }
        else if(push_end_ls(&a->func_transicion,f_aux) != OK){
            return NO_MEM;
        }
        aux_edo=aux_edo->sig;
    }
    return OK;
}
int agrega_funcion_AF(AF* a, Estado edo_orig, Estado edo_dest, Simbolo simb){
    if(a==NULL || edo_orig==NULL || edo_dest==NULL){
        return APU_INVAL;
    }
    int ig1=existe_estado_AF(a,edo_orig);
    int ig2=existe_estado_AF(a,edo_dest);
    if(ig1!=0){
        return ig1;
    }
    else if(ig2!=0){
        return ig2;
    }
    /*Busca si la funcion ya existe*/
    Nodo* aux = a->func_transicion;
    Funcion* f_aux=NULL;
    int exis_func = 1;//No exite a priori
    while(aux != NULL){
        f_aux = (Funcion*)aux->dat;
        aux = aux->sig;
        exis_func = strcmp(f_aux->origen,edo_orig);
        if(exis_func==0){
            break;
        }
    }
    if(exis_func!=0){//No existe la funcion
        f_aux = crea_funcion(edo_orig);
        if(f_aux==NULL){
            return NO_MEM;
        }
        else if(push_end_ls(&a->func_transicion,f_aux) != OK){
            return NO_MEM;
        }
    }
    return agrega_regla_funcion(f_aux,edo_dest,simb);
}
int config_estado_error_AF(AF* a){
    if(a==NULL){
        return APU_INVAL;
    }
    agrega_estado_AF(a,EDO_ERROR);
    /*Transicion desde Error hacia Error con cada simbolo del alfabeto*/
    for(int i=0; i<strlen(a->alfabeto);i++){
        agrega_funcion_AF(a,EDO_ERROR,EDO_ERROR,(a->alfabeto)[i]);
    }
    Nodo* aux_trans = a->func_transicion;
    Nodo* aux_regla = NULL;
    Funcion* f_aux = NULL;
    Regla* r_aux = NULL;
    int ig=1;//No es igual a priori
    //Recorre cada funcion
    while(aux_trans != NULL){
        f_aux = (Funcion*)aux_trans->dat;
        aux_trans = aux_trans->sig;
        aux_regla = f_aux->transiciones;
        //Recorre cada regla de la funcion
        if(aux_regla==NULL){
            for(int i=0; i<strlen(a->alfabeto);i++){
                agrega_funcion_AF(a,f_aux->origen,EDO_ERROR,(a->alfabeto)[i]);
            }
        }
        else{
            for(int i=0; i<strlen(a->alfabeto);i++){
                ig=1;
                aux_regla = f_aux->transiciones;
                while (aux_regla!=NULL){
                    r_aux = (Regla*)aux_regla->dat;
                    ig = r_aux->simb==(a->alfabeto)[i]?0:ig;
                    aux_regla = aux_regla->sig;
                }
                if(ig!=0){//No existe esa transicion
                    agrega_funcion_AF(a,f_aux->origen,EDO_ERROR,(a->alfabeto)[i]);
                }
            }
        }
    }
    return OK;
}
void print_AF(AF* a){
    if(a==NULL){
        return;
    }
    printf("= AF =\n");
    printf("Conjunto de estados: ");
    print_ls(a->conjunto_edos,print_estado_ls);
    printf("\nEstados de aceptacion: ");
    print_ls(a->aceptacion_edos,print_estado_ls);
    printf("\nInicio: %s\n",a->inicio);
    printf("Alfabeto: %s\n",a->alfabeto);
    printf("Funcion de transicion:\n");
    print_ls(a->func_transicion,print_funcion_ls);
}
int repetidos_elim_aux(Lista* edos, Estado edo_elim){
    if(edos==NULL || edo_elim==NULL){
        return APU_INVAL;
    }
    int solo_uno = 0;
    int igual = 1;
    Nodo* aux = *edos;
    if(aux==NULL){
        return OK;
    }
    Nodo* aux_s = aux;
    Estado edo;
    while(aux_s != NULL){
        edo = (Estado)aux_s->dat;
        igual = strcmp(edo,edo_elim);

        /*SI SON IGUALES PERO ES EL PRIMERO
        AUMENTA SOLO_UNO Y AVANZA NORMAL*/
        if(igual==0 && solo_uno==0){
            solo_uno = 1;
            aux = aux_s;
            aux_s = aux->sig;
        }
        /*SIN SON IGUALES Y SE REPITE
        BORRALO Y AVANZA*/
        else if(igual==0 && solo_uno!=0){
            aux->sig = aux_s->sig;
            //aux = aux;
            free(aux_s);
            aux_s = aux->sig;
        }
        /*NO SON IGUALES   AVANZA NORMAL*/
        else{
            aux = aux_s;
            aux_s = aux->sig;
        }
    }
    return OK;
}
int repetidos_elim(Lista* edos){
    if(edos==NULL){
        return APU_INVAL;
    }
    int err=OK;
    Nodo* aux = *edos;
    Estado edo_aux = NULL;
    while(aux != NULL){
        //printf("\njsjsjs\n");
        edo_aux = (Estado)aux->dat;
        repetidos_elim_aux(edos,edo_aux);
        aux = aux->sig;
    }
}

int lee_simb_funcion_AF(Funcion *f, Lista* edos_destino, Simbolo simb){
    if(f==NULL){
        return APU_INVAL;
    }
    Nodo* aux = f->transiciones;
    Regla* r_aux = NULL;
    Estado destino = NULL;
    int err;

    while(aux != NULL){
        r_aux = (Regla*)aux->dat;
        aux = aux->sig;
        if(r_aux->simb==simb){
            destino = (Estado)malloc((strlen(r_aux->edo)+1)*sizeof(char));
            if(destino==NULL){
                return NO_MEM;
            }
            strcpy(destino,r_aux->edo);
            err = push_ls(edos_destino,destino);
            if (err != OK){
                return err;
            }
        }
    }
    return OK;
}
int lee_simb_estado_AF(AF *a, Lista* edos_destino,Estado edo_actual, Simbolo simb){
    if(a==NULL || edos_destino==NULL || edo_actual==NULL){
        return APU_INVAL;
    }
    /*Busca si la funcion ya existe*/
    Nodo* aux = a->func_transicion;
    Funcion* f_aux = NULL;
    int exis_func = 1;//No exite a priori
    while(aux != NULL){
        f_aux = (Funcion*)aux->dat;
        aux = aux->sig;
        exis_func = strcmp(f_aux->origen,edo_actual);
        if(exis_func==0){
            break;
        }
    }
    if(exis_func!=0){
        /*NO HAY TRANSICIONES EN EL ESTADO ACTUAL, AGREGAR EL ESTADO DE ERROR
        EN LA LISTA*/
        return OK;
    }
    int err = lee_simb_funcion_AF(f_aux, edos_destino,simb);
    return err;
}
int lee_simb_conjunto_AF(AF *a, Lista* edos_destino,Lista* edos_actuales, Simbolo simb){
    if(a==NULL || edos_destino==NULL || edos_actuales==NULL){
        return APU_INVAL;
    }
    /*Busca si la funcion ya existe*/
    int err=OK;
    Nodo* aux = *edos_actuales;
    Estado edo_aux = NULL;
    while(aux != NULL){
        edo_aux = (Estado)aux->dat;
        aux = aux->sig;
        err = lee_simb_estado_AF(a,edos_destino,edo_aux,simb);
        if(err != OK){
            break;
        }
    }
    repetidos_elim(edos_destino);
    return err;
}
int lee_cadena_AF(AF* a, Lista* edos_final,Simbolo* cad){
    if(a==NULL || edos_final==NULL || cad==NULL){
        return APU_INVAL;
    }
    Lista edos_origen = crea_ls();
    Lista aux;
    Estado ini = (Estado)malloc((strlen(a->inicio)+1)*sizeof(char));
    if(ini==NULL){
        return NO_MEM;
    }
    strcpy(ini,a->inicio);
    if(push_ls(&edos_origen,ini)!=OK){
        return NO_MEM;
    }
    int long_cad = strlen(cad);
    for(int i=0; i<long_cad; i++){
        lee_simb_conjunto_AF(a,edos_final,&edos_origen,cad[i]);
        elim_ls(&edos_origen,free);//Estados de origen son lista vacia
        aux = edos_origen;
        edos_origen = *edos_final;
        *edos_final = aux;
        //*edos_final = edos_origen;
        //edos_origen = aux;
    }
    *edos_final = edos_origen;
    return OK;
}
int cad_aceptada_AF(AF* a,Lista* edos_final/*,Lista* edos_acept*/){
    if(a==NULL || edos_final==NULL /*|| edos_acept==NULL*/){
        return APU_INVAL;
    }
    Nodo* aux_acep = a->aceptacion_edos;
    Nodo* aux_ed = *edos_final;
    Estado acept;
    int aux_ig = 1,ig=1;//No exite a priori
    while(aux_ed != NULL){
        while(aux_acep != NULL){
            aux_ig = strcmp((Estado)aux_acep->dat,(Estado)aux_ed->dat);
            if(aux_ig==0){
                /*acept = (Estado)malloc((strlen(aux_ed->dat)+1)*sizeof(char));
                if(acept==NULL){
                    return NO_MEM;
                }
                strcpy(acept,(Estado)aux_ed->dat);
                push_ls(edos_acept,acept);*/
                break;
            }
            aux_acep = aux_acep->sig;
        }
        ig = aux_ig==0?0:ig;
        aux_ed = aux_ed->sig;
        aux_acep = a->aceptacion_edos;
    }
    return ig;
}
int cad_recur_print_AF(AF* a, Estado edo_actual, Simbolo* cad, int indice_cad,Lista errores,Lista camino){
    if(a==NULL || cad==NULL || edo_actual==NULL || indice_cad<0){
        return APU_INVAL;
    }
    //if()
    return OK;
}
int lee_cadena_recur_print_AF(AF* a, Simbolo* cad){
    if(a==NULL || cad==NULL){
        return APU_INVAL;
    }
    return OK;
}