#include <stdio.h>
#include <stdlib.h>
#include "CMemLeak.h"
#include "Matica.h"
#include "Komunikator.h"
#include "Citac.h"

bool (*MainFun)(MATICA** m1, MATICA** m2) = &Komunikuj;

int main(int argc, char* argv[]) {
	MATICA* m1 = NULL, * m2 = NULL;
	char* nazovSuboru = NULL;
	bool pokracovat;
	if (argc > 1)
	{
		nazovSuboru = argv[1];
	}
	NacitajMatice(nazovSuboru, &m1, &m2);
	do
	{
		pokracovat = (*MainFun)(&m1, &m2);
	} while (pokracovat);
	return 0;
 }