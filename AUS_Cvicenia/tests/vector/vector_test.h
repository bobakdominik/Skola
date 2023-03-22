#pragma once

#include "../test.h"

namespace tests
{
    /// <summary>
    /// Zavola vsetky metody z rozhrania vektora avsak nekontroluje ich spravnost.
    /// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
    /// </summary>
    class VectorTestInterface
        : public SimpleTest
    {
    public:
        VectorTestInterface();
        void test() override;
    };
    
    /// <summary>
    /// Otestuje spravnost metody size() a at().
    /// </summary>
    class VectorTestAt
        : public SimpleTest
    {
    public:
        VectorTestAt();
        void test() override;
    };

    /// <summary>
    /// Otestuje spravnost metody equals() a asign().
    /// </summary>
    class VectorTestCopyConstruct
        : public SimpleTest
    {
    public:
        VectorTestCopyConstruct();
        void test() override;
    };

    /// <summary>
    /// Otestuje rychlost vektora v danom scenari.
    /// </summary>
    class VectorTimeTest
        : public SimpleTest
    {
    public:
        VectorTimeTest();
        void test() override;
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju vektor.
    /// </summary>
    class VectorTestOverall
        : public ComplexTest
    {
    public:
        VectorTestOverall();
    };
}