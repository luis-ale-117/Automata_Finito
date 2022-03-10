//#include <stdio.h>
#include "archaf.h"

#define MAX_NOM_ARCH (500)
#define MAX_TAM_CAD (1000)

int main(int argc, char** argv){
    char nom_arch[MAX_NOM_ARCH];
    char cadena[MAX_TAM_CAD];

    printf("INGRESE EL ARCHIVO DEL AF: ");
    scanf("%s",nom_arch);
    //printf("NOMBRE DEL ARCHIVO: %s\n",nom_arch);
    printf("INGRESE LA CADENA A VERFICAR: ");
    scanf("%s",cadena);
    //printf("CADENA: %s\n",cadena);

    FILE* f = fopen(nom_arch,"r");
    AF* a = crea_AF();
    //Lista estados_destino = crea_ls();
    if(f==NULL){
        printf("Error al abrir el archivo %s...\n",nom_arch);
        exit(1);
    }
    extrae_edos_arch(f,a);
    extrae_acept_arch(f,a);
    extrae_inicio_arch(f,a);
    extrae_alfa_arch(f,a);
    inicializa_funciones_AF(a);
    extrae_func_arch(f,a);
    fclose(f);
    printf("Lectura del archivo correcta...\n");

    config_estado_error_AF(a);
    print_AF(a);
    printf("====\n");
    printf("Resultados:\n");
    lee_cadena_recur_print_AF(a,cadena);
    
    elim_AF(a);
    printf("FIN DEL PROGRAMA...\n");
    return 0;
}