#include <stdio.h>
//#include "lengreg.h"
#include "archaf.h"

void test_regla();
void test_funcion();
void test_af();
void test_lee_estado_AF();
void test_lee_conjunto_AF();
void test_lee_cad_AF();
void test_lee_estados_arch();

int main(int argc, char** argv){
    /*test_regla();
    test_funcion();
    test_af();
    test_lee_estado_AF();
    test_lee_conjunto_AF();
    test_lee_cad_AF();*/
    test_lee_estados_arch();
    return 0;
}

void test_regla(){
    printf(">>>>>>>>>>>>>>>>  TEST REGLA  <<<<<<<<<<<<<<<<<\n");
    Regla* r = crea_regla("Estado1",'K');
    if(r==NULL){
        printf("Error al crear la regla\n");
        exit(1);
    }
    printf("Estado prueba:\n");
    print_regla(r);
    printf("\n");
    elim_regla(r);
    printf("Eliminacion de regla correcta:\n");
}

void test_funcion(){
    printf(">>>>>>>>>>>>>>>> TEST FUNCION <<<<<<<<<<<<<<<<<\n");
    Funcion* f = crea_funcion("Estado1");
    if(f==NULL){
        printf("Error al crear la funcion\n");
        exit(1);
    }
    printf("Funcion prueba:\n");

    if(agrega_regla_funcion(f,"Edo2",'B')){printf("Error en regla\n");exit(1);}
    if(agrega_regla_funcion(f,"Edo3",'A')){printf("Error en regla\n");exit(1);}
    if(agrega_regla_funcion(f,"Edo4",'C')){printf("Error en regla\n");exit(1);}
    if(agrega_regla_funcion(f,"Edo2",'B')){printf("Error en regla\n");exit(1);}
    if(agrega_regla_funcion(f,"Edo2",'B')){printf("Error en regla\n");exit(1);}

    print_funcion(f);
    printf("\n");
    
    elim_funcion(f);
    printf("Eliminacion de funcion correcta:\n");
}

void test_af(){
    printf(">>>>>>>>>>>>>>>>>  TEST AF   <<<<<<<<<<<<<<<<<<\n");
    AF* a = crea_AF();
    if(a==NULL){
        printf("Error al crear el AF\n");
        exit(1);
    }
    agrega_estado_AF(a,"Estado1");
    agrega_estado_AF(a,"Estado2");
    agrega_estado_AF(a,"Estado3");
    agrega_estado_AF(a,"Estado4");
    agrega_estado_AF(a,"Estado5");

    agrega_aceptacion_AF(a,"Estado3");
    agrega_aceptacion_AF(a,"Estado5");

    pon_inicio_AF(a,"Estado1");

    pon_alfabeto_AF(a,"AFGV012*-!");

    agrega_funcion_AF(a,"Estado1","Estado2",'!');
    agrega_funcion_AF(a,"Estado1","Estado3",'*');
    agrega_funcion_AF(a,"Estado2","Estado5",'G');
    agrega_funcion_AF(a,"Estado2","Estado4",'2');
    agrega_funcion_AF(a,"Estado3","Estado5",'F');
    agrega_funcion_AF(a,"Estado4","Estado5",'0');
    //agrega_funcion_AF(a,"Estado5","Estado5",'2');

    print_AF(a);
    
    elim_AF(a);
    printf("Eliminacion de AFD correcta:\n");
}

void test_lee_estado_AF(){
    printf(">>>>>>>>>>>>>>>>> TEST LEE 1 <<<<<<<<<<<<<<<<<<\n");
    AF* a = crea_AF();
    Lista estados_destino = crea_ls();
    if(a==NULL){
        printf("Error al crear el AF\n");
        exit(1);
    }
    agrega_estado_AF(a,"Estado1");
    agrega_estado_AF(a,"Estado2");
    agrega_estado_AF(a,"Estado3");
    
    agrega_aceptacion_AF(a,"Estado3");

    pon_inicio_AF(a,"Estado1");

    pon_alfabeto_AF(a,"01");

    agrega_funcion_AF(a,"Estado1","Estado2",'0');
    agrega_funcion_AF(a,"Estado1","Estado3",'0');
    agrega_funcion_AF(a,"Estado1","Estado3",'1');
    agrega_funcion_AF(a,"Estado2","Estado3",'0');
    agrega_funcion_AF(a,"Estado2","Estado3",'1');
    agrega_funcion_AF(a,"Estado3","Estado3",'0');

    print_AF(a);
    char origen[] = "Estado1";
    char simb = '0';
    printf("--Lectura de un caracter dado un estado--\n");
    printf("%s -%c-> {",origen,simb);
    lee_simb_estado_AF(a,&estados_destino,origen,simb);
    print_ls(estados_destino,print_estado_ls);
    printf("}\n");

    elim_ls(&estados_destino,free);
    elim_AF(a);
    printf("Eliminacion de AFD correcta:\n");
}

void test_lee_conjunto_AF(){
    printf(">>>>>>>>>>>>>>>>> TEST LEE 2 <<<<<<<<<<<<<<<<<<\n");
    AF* a = crea_AF();
    Lista estados_destino = crea_ls();
    Lista estados_actuales = crea_ls();
    char actual1[] = "Estado1";
    char actual2[] = "Estado2";
    char actual3[] = "Estado3";
    push_ls(&estados_actuales,actual1);
    push_ls(&estados_actuales,actual2);
    push_ls(&estados_actuales,actual3);

    if(a==NULL){
        printf("Error al crear el AF\n");
        exit(1);
    }
    agrega_estado_AF(a,"Estado1");
    agrega_estado_AF(a,"Estado2");
    agrega_estado_AF(a,"Estado3");
    
    agrega_aceptacion_AF(a,"Estado3");

    pon_inicio_AF(a,"Estado1");

    pon_alfabeto_AF(a,"01");

    agrega_funcion_AF(a,"Estado1","Estado2",'0');
    agrega_funcion_AF(a,"Estado1","Estado3",'0');
    agrega_funcion_AF(a,"Estado1","Estado3",'0');
    agrega_funcion_AF(a,"Estado2","Estado3",'0');
    agrega_funcion_AF(a,"Estado2","Estado3",'0');
    agrega_funcion_AF(a,"Estado3","Estado3",'0');

    print_AF(a);
    char origen[] = "Estado1";
    char simb = '0';
    printf("--Lectura de un caracter dado un conjunto--\n");
    printf("{%s %s %s} -%c-> {",actual1,actual2,actual3,simb);
    lee_simb_conjunto_AF(a,&estados_destino,&estados_actuales,simb);
    
    print_ls(estados_destino,print_estado_ls);
    printf("}\n");
    //repetidos_elim(&estados_destino);
    //print_ls(estados_destino,print_estado_ls);
    elim_ls(&estados_destino,free);
    elim_AF(a);
    printf("Eliminacion de AFD correcta:\n");
}

void test_lee_cad_AF(){
    printf(">>>>>>>>>>>>>>>>> TEST LEE 3 <<<<<<<<<<<<<<<<<<\n");
    AF* a = crea_AF();
    Lista estados_destino = crea_ls();
    //Lista estados_aceptacion = crea_ls();

    if(a==NULL){
        printf("Error al crear el AF\n");
        exit(1);
    }
    agrega_estado_AF(a,"Estado1");
    agrega_estado_AF(a,"Estado2");
    agrega_estado_AF(a,"Estado3");
    
    agrega_aceptacion_AF(a,"Estado3");

    pon_inicio_AF(a,"Estado1");

    pon_alfabeto_AF(a,"01");

    agrega_funcion_AF(a,"Estado1","Estado2",'1');
    agrega_funcion_AF(a,"Estado1","Estado3",'0');
    agrega_funcion_AF(a,"Estado1","Estado3",'0');
    agrega_funcion_AF(a,"Estado2","Estado3",'1');
    agrega_funcion_AF(a,"Estado2","Estado3",'0');
    agrega_funcion_AF(a,"Estado3","Estado3",'0');

    print_AF(a);
    //char origen[] = "Estado1";
    //char simb = '2';
    char cad[] =  "00000000000000000000000001";
    printf("--Lectura de una cadena--\n");
    lee_cadena_AF(a,&estados_destino,cad);
    printf("Estado inicial: %s, Cadena: %s\n",a->inicio,cad);
    printf("Estados finales: {");
    print_ls(estados_destino,print_estado_ls);
    printf("}\n");
    
    if(cad_aceptada_AF(a,&estados_destino/*,&estados_aceptacion*/)==0){
        printf("Cadena \"%s\" aceptada por el automata\n",cad);
    }
    else{
        printf("Cadena \"%s\" NO aceptada por el automata\n",cad);
    }

    elim_ls(&estados_destino,free);
    elim_AF(a);
    printf("Eliminacion de AFD correcta:\n");
}

void test_lee_estados_arch(){
    printf(">>>>>>>>>>>>>>  TEST LINEA ARCH <<<<<<<<<<<<<<<\n");
    char nom_arch[] = "input.txt";
    FILE* f = fopen(nom_arch,"r");
    AF* a = crea_AF();
    if(f==NULL){
        printf("Error al abrir el archivo %s\n",nom_arch);
    }
    extrae_edos_arch(f,a);
    fclose(f);
    printf("Lectura de la primer linea correcta:\n");
    print_AF(a);
    elim_AF(a);
}