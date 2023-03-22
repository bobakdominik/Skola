#pragma once

#include "../test.h"
#include "../../structures/priority_queue/priority_queue.h"
#include "../../structures/priority_queue/priority_queue_list.h"

namespace tests
{
    /// <summary>
    /// Zavola vsetky metody z rozhrania prioritneho frontu avsak nekontroluje ich spravnost.
    /// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
    /// </summary>
    class PriorityQueueTestInterface
        : public SimpleTest
    {
    public:
        PriorityQueueTestInterface();
        void test() override;

    protected:
        virtual structures::PriorityQueue<int>* makePriorityQueue() = 0;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueUnsortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueSortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueLimitedSortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueLinkedListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueTwoListsTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class HeapTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueUnsortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueUnsortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueSortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueSortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueLimitedSortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueLimitedSortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueLinkedListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueLinkedListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueTwoListsTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueTwoListsTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class HeapTestOverall
        : public ComplexTest
    {
    public:
        HeapTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju prioritny front.
    /// </summary>
    class PriorityQueueTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueTestOverall();
    };

    //#################################
    // Test push() a pop()
    //#################################

    class PriorityQueueTestPushPop 
        : public SimpleTest
    {
    public:
        PriorityQueueTestPushPop();
        void test() override;

    protected:
        virtual structures::PriorityQueue<char>* makePriorityQueue() = 0;
    };

    class PriorityQueueUnsortedArrayListTestPushPop
        : public PriorityQueueTestPushPop
    {
    protected:
        structures::PriorityQueue<char>* makePriorityQueue() override;
    };

    
    class PriorityQueueSortedArrayListTestPushPop
        : public PriorityQueueTestPushPop
    {
    protected:
        structures::PriorityQueue<char>* makePriorityQueue() override;
    };

    class PriorityQueueLinkedListTestPushPop
        : public PriorityQueueTestPushPop
    {
    protected:
        structures::PriorityQueue<char>* makePriorityQueue() override;
    };

    class PriorityQueueLimitedSortedArrayListTestPushPop
        : public PriorityQueueTestPushPop
    {
    protected:
        structures::PriorityQueue<char>* makePriorityQueue() override;
    };

    class PriorityQueueTwoListsTestPushPop
        : public PriorityQueueTestPushPop
    {
    protected:
        structures::PriorityQueue<char>* makePriorityQueue() override;
    };

    class HeapTestPushPop
        : public PriorityQueueTestPushPop
    {
    protected:
        structures::PriorityQueue<char>* makePriorityQueue() override;
    };

    //#################################
    // Test assign()
    //#################################

    class PriorityQueueTestAssign
        : public SimpleTest
    {
    public:
        PriorityQueueTestAssign();
        void test() override;

    protected:
        virtual structures::PriorityQueue<int>* makePriorityQueue() = 0;
    };

    class PriorityQueueUnsortedArrayListTestAssign
        : public PriorityQueueTestAssign
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };


    class PriorityQueueSortedArrayListTestAssign
        : public PriorityQueueTestAssign
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    class PriorityQueueLinkedListTestAssign
        : public PriorityQueueTestAssign
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    class PriorityQueueLimitedSortedArrayListTestAssign
        : public PriorityQueueTestAssign
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    class PriorityQueueTwoListsTestAssign
        : public PriorityQueueTestAssign
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    class HeapTestAssign
        : public PriorityQueueTestAssign
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    //########################################################################################################
    // Uloha 2
    //########################################################################################################

    //################################################################
    // Priority queue test, overenie vykonu v scenari 
    //################################################################

    class PriorityQueueTestPerformance
        : public SimpleTest
    {
    public:
        PriorityQueueTestPerformance(int ratioPush, int ratioPop, int ratioPeek, std::string queueType, std::string scenario);
        void test() override;

    protected:
        virtual structures::PriorityQueue<int>* makePriorityQueue() const = 0;

    private:
        int ratioPush_;
        int ratioPop_;
        int ratioPeek_;
        std::string queueType_;
        std::string scenario_;

    };

    //################################################################
    // Priority queue test, scenar A-C
    //################################################################

    class PriorityQueueTestPerformanceA
        : public PriorityQueueTestPerformance
    {
    public:
        PriorityQueueTestPerformanceA(std::string priorityQueueType);
    };

    class PriorityQueueTestPerformanceB
        : public PriorityQueueTestPerformance
    {
    public:
        PriorityQueueTestPerformanceB(std::string priorityQueueType);
    };

    class PriorityQueueTestPerformanceC
        : public PriorityQueueTestPerformance
    {
    public:
        PriorityQueueTestPerformanceC(std::string priorityQueueType);
    };

    //################################################################
    // Heap test, scenar A-C
    //################################################################

    class HeapTestPerformanceA
        : public PriorityQueueTestPerformanceA
    {
    public:
        HeapTestPerformanceA();

    protected:
        structures::PriorityQueue<int>* makePriorityQueue() const override;
    };

    class HeapTestPerformanceB
        : public PriorityQueueTestPerformanceB
    {
    public:
        HeapTestPerformanceB();

    protected:
        structures::PriorityQueue<int>* makePriorityQueue() const override;
    };

    class HeapTestPerformanceC
        : public PriorityQueueTestPerformanceC
    {
    public:
        HeapTestPerformanceC();

    protected:
        structures::PriorityQueue<int>* makePriorityQueue() const override;
    };

    //################################################################
    // Priority queue two lists test, scenar A-C
    //################################################################

    class PriorityQueueTwoListsTestPerformanceA
        : public PriorityQueueTestPerformanceA
    {
    public:
        PriorityQueueTwoListsTestPerformanceA();

    protected:
        structures::PriorityQueue<int>* makePriorityQueue() const override;
    };

    class PriorityQueueTwoListsTestPerformanceB
        : public PriorityQueueTestPerformanceB
    {
    public:
        PriorityQueueTwoListsTestPerformanceB();

    protected:
        structures::PriorityQueue<int>* makePriorityQueue() const override;
    };

    class PriorityQueueTwoListsTestPerformanceC
        : public PriorityQueueTestPerformanceC
    {
    public:
        PriorityQueueTwoListsTestPerformanceC();

    protected:
        structures::PriorityQueue<int>* makePriorityQueue() const override;
    };

    //########################################################################################################
    // Uloha 3
    //########################################################################################################

    //################################################################
    //Casova analyza funkcii push(), pop() a peek()
    //################################################################

    class PriorityQueueTimeTest
        : public SimpleTest
    {
    public:
        PriorityQueueTimeTest(std::string queueType);
        void test() override;

    protected:
        virtual structures::PriorityQueue<int>* makePriorityQueue() const = 0;

    private:
        std::string queueType_;
    };

    class HeapTimeTest
        : public PriorityQueueTimeTest
    {
    public:
        HeapTimeTest();

    protected:
        structures::PriorityQueue<int>* makePriorityQueue() const override;
    };

    class PriorityQueueTwoListsTimeTest
        : public PriorityQueueTimeTest
    {
    public:
        PriorityQueueTwoListsTimeTest();

    protected:
        structures::PriorityQueue<int>* makePriorityQueue() const override;
    };

}