#include <stdio.h>
#include <stdlib.h>
#include "CMemLeak.h"
#include "Komunikator.h"
#include "Vstup.h"

int ZvolMaticu();
void Ukonci(MATICA** m1, MATICA** m2);
MATICA* UrobNasobokKonstantou(MATICA* m);
void UlozMaticu(MATICA* zdroj, MATICA** m1, MATICA** m2);
void VypisMenu(MATICA* m1, MATICA* m2);
void VypisMatice(MATICA* m1, MATICA* m2);
MATICA* VytvorJednotkovu();

bool Komunikuj(MATICA** m1, MATICA** m2)
{
	VypisMenu(*m1, *m2);
	printf("Zvol akciu:\n");
	int odpoved = NacitajCislo();
	printf("\n-------------------------\n");
	printf("-------------------------\n\n");
	MATICA* vypis = NULL;
	int indexMatice;
	switch (odpoved)
	{
	case 1: // scitanie
		vypis = Scitanie(*m1, *m2);
		printf("\nA + B:\n");
		break;
	case 2: // odcitanie
		vypis = Odcitanie(*m1, *m2);
		printf("\nA - B:\n");
		break;
	case 3: // nasobenie
		vypis = Sucin(*m1, *m2);
		printf("\nA * B:\n");
		break;
	case 4: // nasobenie konstantou
		indexMatice = ZvolMaticu();
		if (indexMatice == 1)
		{
			vypis = UrobNasobokKonstantou(*m1);
			printf("\nk * A:\n");
		}
		else {
			vypis = UrobNasobokKonstantou(*m2);
			printf("\nk * B:\n");
		}
		break;
	case 5: // determinant
		indexMatice = ZvolMaticu();
		if (indexMatice == 1)
		{
			if (ExistujeDeterminant(*m1))
			{
				printf("\nDeterminat matice A:\n%.2lf\n", Determinant(*m1));
			}
			else
			{
				printf("\nDeterminant sa neda urcit\n\n");
			}
		}
		else {
			if (ExistujeDeterminant(*m2))
			{
				printf("\nDeterminat matice B:\n%.2lf\n", Determinant(*m2));
			}
			else
			{
				printf("\nDeterminant sa neda urcit\n\n");
			}
		}
		break;
	case 6: // inverzia
		indexMatice = ZvolMaticu();
		if (indexMatice == 1)
		{
			printf("\nInverzna matica A:\n");
			vypis = Inverzia(*m1);
		}
		else {
			printf("\nInverzna matica B:\n");
			vypis = Inverzia(*m2);
		}
		break;
	case 7: // transponovanie
		indexMatice = ZvolMaticu();
		if (indexMatice == 1)
		{
			printf("\nTransponovana matica A:\n");
			vypis = Transponovanie(*m1);
		}
		else {
			printf("\nTransponovana matica B:\n");
			vypis = Transponovanie(*m2);
		}
		break;
	case 8: // vymen matice
		printf("Vymena matic\n");
		vypis = *m1;
		*m1 = *m2;
		*m2 = vypis;
		vypis = NULL;
		break;
	case 9: // vytvor maticu
		vypis = NastavMaticu();	
		printf("\nNova matica:\n");
		break;
	case 10: // vytvor jednotkovu maticu
		vypis = VytvorJednotkovu();
		printf("\nJednotkova matica:\n");
		break;
	case 0: // ukonci
		printf("Program ukonceny\n");
		Ukonci(m1, m2);
		return false;
	default: 
		printf("\nZvolena moznost nie je k dispozicii\n");
		break;
	}
	if (!vypis && odpoved != 8 && odpoved != 5 && odpoved != 0)
	{
		printf("Operaciu nie je mozne vykonat\n");
	}
	VypisMaticu(vypis);
	printf("\n-------------------------\n");
	printf("-------------------------\n\n");
	_sleep(SLEEPTIME);
	if (vypis)
	{
		UlozMaticu(vypis, m1, m2);
		ZrusMaticu(&vypis);
		printf("\n-------------------------\n");
		printf("-------------------------\n\n");
	}
	return true;
}

MATICA* VytvorJednotkovu() {
	int pocetPrvkov;
	MATICA* vysledok = NULL;
	printf("Zadaj pocet prvkov (max %d)\n", MAX_ROZMER);
	do
	{
		pocetPrvkov = NacitajCislo();
		if (pocetPrvkov <= 0 || pocetPrvkov > MAX_ROZMER)
		{
			printf("Nespravny pocet prvkov\n");
		}
	} while (pocetPrvkov <= 0 || pocetPrvkov > MAX_ROZMER);
	vysledok = Jednotkova(pocetPrvkov);
	return vysledok;
}

void VypisMenu(MATICA* m1, MATICA* m2)
{
	VypisMatice(m1, m2);
	printf("\n1:  Scitanie\n2:  Odcitanie\n3:  Nasobenie\n4:  Nasobenie konstantou\n5:  Determinant\n"
		"6:  Inverzna matica\n7:  Transponovana matica\n8:  Vymena matic\n9:  Vytvorit maticu\n10: Vytvorit jednotkovu maticu\n0:  Ukoncit\n\n");
}

void VypisMatice(MATICA* m1, MATICA* m2)
{
	if (m1)
	{
		printf("\nMatica A:\n");
		VypisMaticu(m1);
	}
	if (m2)
	{
		printf("\nMatica B:\n");
		VypisMaticu(m2);
	}
}

int ZvolMaticu()
{
	int odpoved;
	printf("Zvol maticu:\n1: matica A\n2: matica B\n");
	do
	{
		odpoved = NacitajCislo();
		if (odpoved != 1 && odpoved != 2)
		{
			printf("Nespravne zvolene cislo\n");
		}
	} while (odpoved != 1 && odpoved != 2);
	return odpoved;
}

MATICA* UrobNasobokKonstantou(MATICA* m)
{
	double konstanta;
	MATICA* vysledok;
	printf("Zvol konstantu: ");
	konstanta = NacitajDouble();
	vysledok = SkalarnySucin(m, konstanta);
	return vysledok;
}

void UlozMaticu(MATICA* zdroj, MATICA** m1, MATICA** m2)
{
	if (zdroj && m1 && m2)
	{
		int odpoved;
		printf("\nUlozit do\n1: A\n2: B\n0: Neulozit\n");
		do
		{
			odpoved = NacitajCislo();
			if (odpoved < 0 || odpoved > 2)
			{
				printf("Nespravne cislo\n");
			}
		} while (odpoved < 0 || odpoved > 2);
		if (odpoved == 1)
		{
			ZrusMaticu(m1);
			*m1 = Skopiruj(zdroj);
		}
		else if (odpoved == 2)
		{
			ZrusMaticu(m2);
			*m2 = Skopiruj(zdroj);
		}
	}
}


void Ukonci(MATICA** m1, MATICA** m2)
{
	ZrusMaticu(m1);
	ZrusMaticu(m2);
}
