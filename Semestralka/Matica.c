#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "CMemLeak.h"
#include "Matica.h"

MATICA* VytvorMaticu(unsigned int m, unsigned int n)
{
    if (m && n)
    {
        MATICA* mPtr = (MATICA*)malloc(sizeof(MATICA));
        mPtr->riadky = (m > MAX_ROZMER)? MAX_ROZMER : m;
        mPtr->stlpce = (n > MAX_ROZMER) ? MAX_ROZMER : n;
        mPtr->hodnoty = (double**)calloc(mPtr->riadky, sizeof(double*));
        for (double** ptr = mPtr->hodnoty; ptr < mPtr->hodnoty + mPtr->riadky; ptr++)
        {
            *ptr = (double*)calloc(mPtr->stlpce, sizeof(double));
        }
        return mPtr;
    }
    return NULL;
}

MATICA* Scitanie(MATICA* m1, MATICA* m2)
{
    if (m1 && m2 && m1->riadky == m2->riadky && m1->stlpce == m2->stlpce)
    {
        MATICA* vysledok = VytvorMaticu(m1->riadky, m1->stlpce);
        for (int i = 0; i < vysledok->riadky; i++)
        {
            for (int j = 0; j < vysledok->stlpce; j++)
            {
                *(*(vysledok->hodnoty + i) + j) = *(*(m1->hodnoty + i) + j) + *(*(m2->hodnoty + i) + j);
            }
        }
        return vysledok;
    }
    return NULL;
}

MATICA* Odcitanie(MATICA* m1, MATICA* m2)
{
    if (m1 && m2 && m1->riadky == m2->riadky && m1->stlpce == m2->stlpce)
    {
        MATICA* vysledok = VytvorMaticu(m1->riadky, m1->stlpce);
        for (int i = 0; i < vysledok->riadky; i++)
        {
            for (int j = 0; j < vysledok->stlpce; j++)
            {
                *(*(vysledok->hodnoty + i) + j) = *(*(m1->hodnoty + i) + j) - *(*(m2->hodnoty + i) + j);
            }
        }
        return vysledok;
    }
    return NULL;
}

double NasobRiadokStlpec(MATICA* m1, MATICA* m2,unsigned int m, unsigned int n) {
    double vysledok = 0;
    if (m1 && m2 && m >= 0 && n >= 0 && m1->stlpce == m2->riadky && m1->riadky > m && m2->stlpce > n)
    {
        for (int i = 0; i < m1->stlpce; i++)
        {
            vysledok += *(*(m1->hodnoty + m) + i) * *(*(m2->hodnoty + i) + n);
        }
    }
    return vysledok;
}

MATICA* Sucin(MATICA* m1, MATICA* m2)
{
    if (m1 && m2 && m1->stlpce == m2->riadky)
    {
        MATICA* vysledok = VytvorMaticu(m1->riadky, m2->stlpce);
        int i = 0;
        for (double** ptr1 = vysledok->hodnoty; ptr1 < vysledok->hodnoty + vysledok->riadky; ptr1++)
        {
            int j = 0;
            for (double* ptr2 = *ptr1; ptr2 < *ptr1 + vysledok->stlpce; ptr2++)
            {
                *ptr2 = NasobRiadokStlpec(m1, m2, i, j);
                j++;
            }
            i++;
        }
        return vysledok;
    }
    return NULL;
}

MATICA* SkalarnySucin(MATICA* m, double cislo)
{
    if (m)
    {
        MATICA* vysledok = VytvorMaticu(m->riadky, m->stlpce);
        int i = 0;
        for (double** ptr1 = vysledok->hodnoty; ptr1 < vysledok->hodnoty + vysledok->riadky; ptr1++)
        {
            int j = 0;
            for (double* ptr2 = *ptr1; ptr2 < *ptr1 + vysledok->stlpce; ptr2++)
            {
                *ptr2 = *(*(m->hodnoty + i) + j) * cislo;
                j++;
            }
            i++;
        }
        return vysledok;
    }
    return NULL;
}

MATICA* Transponovanie(MATICA* m)
{
    if (m)
    {
        MATICA* vysledok = VytvorMaticu(m->stlpce, m->riadky);
        for (int i = 0; i < vysledok->riadky; i++)
        {
            for (int j = 0; j < vysledok->stlpce; j++)
            {
                *(*(vysledok->hodnoty + i) + j) = *(*(m->hodnoty + j) + i);
            }
        }
        return vysledok;
    }
    return NULL;
}

double PrvokInverzie(MATICA* mPtr, int m, int n) {

    double vysledok = 0;
    MATICA* pomMat;
    if (mPtr && mPtr->riadky == mPtr->stlpce)
    {
        pomMat = VytvorMaticu(mPtr->riadky - 1, mPtr->stlpce - 1);
        int riadok = 0;
        for (int i = 0; i < mPtr->riadky; i++)
        {
            if (i != m)
            {
                int stlpec = 0;
                for (int j = 0; j < mPtr->stlpce; j++)
                {
                    if (j != n)
                    {
                        *(*(pomMat->hodnoty + riadok) + stlpec) = *(*(mPtr->hodnoty + i) + j);
                        stlpec++;
                    }
                }
                riadok++;
            }            
        }
        vysledok = Determinant(pomMat);
        if ((m + n) % 2)
        {
            vysledok = vysledok * (-1);
        }
        ZrusMaticu(&pomMat);
    }
    return vysledok;
}

MATICA* Inverzia(MATICA* m)
{
    MATICA* vysledok = NULL,* pomMat;
    if (m && m->riadky == m->stlpce && m->riadky > 1 && Determinant(m))
    {
        double delitel = 1 / Determinant(m);
        vysledok = VytvorMaticu(m->riadky, m->stlpce);
        for (int i = 0; i < vysledok->riadky; i++)
        {
            for (int j = 0; j < vysledok->stlpce; j++)
            {
                *(*(vysledok->hodnoty + i) + j) = PrvokInverzie(m, i, j);
            }
        }
        pomMat = Transponovanie(vysledok);
        ZrusMaticu(&vysledok);
        vysledok = SkalarnySucin(pomMat, delitel);
        ZrusMaticu(&pomMat);
    }
    return vysledok;
}

MATICA* Jednotkova(unsigned int m)
{
    if (m)
    {
        MATICA* vysledok = VytvorMaticu(m, m);
        for (int i = 0; i < vysledok->riadky; i++)
        {
            *(*(vysledok->hodnoty + i) + i) = 1;
        }
        return vysledok;
    }
    return NULL;
}

MATICA* Skopiruj(MATICA* m)
{
    if (m)
    {
        MATICA* vysledok = VytvorMaticu(m->riadky, m->stlpce);
        for (int i = 0; i < vysledok->riadky; i++)
        {
            for (int j = 0; j < vysledok->stlpce; j++)
            {
                *(*(vysledok->hodnoty + i) + j) = *(*(m->hodnoty + i) + j);
            }
        }
        return vysledok;
    }
    return NULL;
}

void ZrusMaticu(MATICA** m)
{
    if (m && *m)
    {
        for (double** i = (*m)->hodnoty; i < (*m)->hodnoty + (*m)->riadky; i++)
        {
            free(*i);
        }
        free((*m)->hodnoty);
        free((*m));
        *m = NULL;
    }
}

void VypisMaticu(MATICA* m)
{
    if (m)
    {
        for (int i = 0; i < m->riadky; i++)
        {
            for (int j = 0; j < m->stlpce; j++)
            {
                printf("%8.2f", *(*(m->hodnoty + i) + j));
            }
            printf("\n");
        }
    }
}

void VymenPrvkyZoznamu(int* zoznam, int index1, int index2, int n) {
    if (index1 >= 0 && index2 >= 0 && index1 < n && index2 < n)
    {
        double pom = zoznam[index1];
        zoznam[index1] = zoznam[index2];
        zoznam[index2] = pom;
    }
}

void VypisZoznam(int* zoznam, int i, int n, int pocetVymen) {
    for (int j = i; j < n; j++)
    {
        int novyPocetVymen = pocetVymen;
        if (i != j)
        {
            novyPocetVymen++;
        }
        VymenPrvkyZoznamu(zoznam, i, j, n);
        VypisZoznam(zoznam, i + 1, n, novyPocetVymen);
        VymenPrvkyZoznamu(zoznam, i, j, n);
    }
    if (i == n)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%4d", zoznam[j]);
        }
        printf("\tPocet vymen: %d\n", pocetVymen);
    }
    
}

double HodnotaDeterminantu(MATICA* m, int* zoznam, int i, int n, int pocetVymen) {
    double vysledok = 0;
    for (int j = i; j < n; j++)
    {
        int novyPocetVymen = pocetVymen;
        if (i != j)
        {
            novyPocetVymen++;
        }
        VymenPrvkyZoznamu(zoznam, i, j, n);
        vysledok += HodnotaDeterminantu(m ,zoznam, i + 1, n, novyPocetVymen);
        VymenPrvkyZoznamu(zoznam, i, j, n);
    }
    if (i == n)
    {
        double pom = 1;
        for (int j = 0; j < n; j++)
        {
            pom = pom * m->hodnoty[j][zoznam[j]];
        }
        if (pocetVymen % 2)
        {
            pom = pom * (-1);
        }
        vysledok += pom;
    }
    return vysledok;
}

double Determinant(MATICA* m)
{
    double vysledok = 0;
    if (m && m->riadky == m->stlpce)
    {
        int pocetPrvkov = m->riadky;
        int* zoznam = (int*)malloc(pocetPrvkov * sizeof(int));
        for (int i = 0; i < pocetPrvkov; i++)
        {
            *(zoznam + i) = i;
        }
        //VypisZoznam(zoznam, 0, pocetPrvkov, 0);
        vysledok = HodnotaDeterminantu(m, zoznam, 0, pocetPrvkov, 0);
        free(zoznam);
    }
    return vysledok;
}

bool ExistujeDeterminant(MATICA* m)
{
    if (m && m->riadky == m->stlpce)
    {
        return true;
    }
    return false;
}
