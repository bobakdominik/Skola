#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include "CMemLeak.h"
#include "Citac.h"
#include "Vstup.h"

void NacitajZoSuboru(const char* nazovSuboru, MATICA** m1, MATICA** m2);
bool TestujSubor(const char* nazovSuboru);

void NacitajMatice(const char* nazovSuboru, MATICA** m1, MATICA** m2)
{
	if (TestujSubor(nazovSuboru))
	{
		NacitajZoSuboru(nazovSuboru, m1, m2);
	}
	else
	{
		double pom = 0;
		int m = 0, n = 0;
		printf("Nastavenie matice A\n");
		MATICA** aktualnaMatica = m1;
		for (int i = 0; i < 2; i++)
		{
			*aktualnaMatica = NastavMaticu();
			printf("Nastavenie matice B:\n");
			aktualnaMatica = m2;
		}
	}
}

void NacitajZoSuboru(const char* nazovSuboru, MATICA** m1, MATICA** m2) {
	double pom = 0;
	int m = 0, n = 0;
	FILE* f;
	MATICA** pomMat = m1;
	if (nazovSuboru && (f = fopen(nazovSuboru, "rt")))
	{
		for (int i = 0; i < 2; i++)
		{
			fscanf(f, "%d", &m);
			fscanf(f, "%d", &n);
			(*pomMat) = VytvorMaticu(m, n);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
				{
					fscanf(f, "%lf", &pom);
					*(*((*pomMat)->hodnoty + i) + j) = pom;
				}
			}
			pomMat = m2;
		}
		fclose(f);
	}
}

bool TestujSubor(const char* nazovSuboru) {
	FILE* f;
	if (nazovSuboru && (f = fopen(nazovSuboru, "rt")))
	{
		for (int i = 0; i < 2; i++)
		{
			int m, n;
			double pom;
			if (feof(f) || !fscanf(f,"%d", &m) || !fscanf(f, "%d", &n) || m < 0 ||
				m > MAX_ROZMER || n < 0 || n > MAX_ROZMER)
			{
				fclose(f);
				return false;
			}
			for (int j = 0; j < m * n; j++)
			{
				if (feof(f) || !fscanf(f, "%lf", &pom))
				{
					fclose(f);
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}
