#include <stdio.h>
#include <stdlib.h>
#include "CMemLeak.h"
#include "Vstup.h"

int NacitajCislo() {
	int cislo;
	while (!scanf("%d", &cislo))
	{
		printf("Nespravna hodnota\n");
		char cistic[50];
		scanf(" %s", cistic);// Pri zadani viac enterov je lepsie dat pred % medzeru
	}
	return cislo;
}

double NacitajDouble() {
	double cislo;
	while (!scanf("%lf", &cislo))
	{
		printf("Nespravna hodnota\n");
		char cistic[50];
		scanf("%s", cistic);// Pri zadani viac enterov je lepsie dat pred % medzeru
	}
	return cislo;
}


MATICA* NastavMaticu()
{
	int m, n;
	MATICA* vysledok;
	printf("Definuj rozmer matice (maximalne %dx%d)\n", MAX_ROZMER, MAX_ROZMER);
	do
	{
		m = NacitajCislo();
		n = NacitajCislo();
		if (m <= 0 || m > MAX_ROZMER || n <= 0 || n > MAX_ROZMER)
		{
			printf("Nespravny rozmer\n");
		}
	} while (m <= 0 || m > MAX_ROZMER || n <= 0 || n > MAX_ROZMER);
	vysledok = VytvorMaticu(m, n);
	printf("Zadaj prvky matice\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			*(*(vysledok->hodnoty + i) + j) = NacitajDouble();
		}
	}
	return vysledok;
}