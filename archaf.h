#ifndef ARCHAF_H
#define ARCHAF_H

#include "lengreg.h"

#define MAX_TAM_LINEA (1000)

int extrae_edos_arch(FILE* f, AF* a);
int extrae_acept_arch(FILE* f, AF* a);
int extrae_inicio_arch(FILE* f, AF* a);
int extrae_alfa_arch(FILE* f, AF* a);
int extrae_func_arch(FILE* f, AF* a);

#endif