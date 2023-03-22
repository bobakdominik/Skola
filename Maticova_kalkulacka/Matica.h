#pragma once
#include <stdbool.h>

#define MAX_ROZMER 10
typedef struct matica {
	unsigned int riadky;
	unsigned int stlpce;
	double** hodnoty;
}MATICA;

MATICA* VytvorMaticu(unsigned int m, unsigned int n);
MATICA* Scitanie(MATICA* m1, MATICA* m2);
MATICA* Odcitanie(MATICA* m1, MATICA* m2);
MATICA* Sucin(MATICA* m1, MATICA* m2);
MATICA* SkalarnySucin(MATICA* m, double cislo);
MATICA* Transponovanie(MATICA* m);
MATICA* Inverzia(MATICA* m);
MATICA* Jednotkova(unsigned int m);
MATICA* Skopiruj(MATICA* m);
void ZrusMaticu(MATICA** m);
void VypisMaticu(MATICA* m);
double Determinant(MATICA* m);
bool ExistujeDeterminant(MATICA* m);