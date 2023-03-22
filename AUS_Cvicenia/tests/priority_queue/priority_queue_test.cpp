#include "priority_queue_test.h"
#include "../../structures/priority_queue/heap.h"
#include "../../structures/priority_queue/priority_queue_limited_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_linked_list.h"
#include "../../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_two_lists.h"
#include "../../structures/priority_queue/priority_queue_unsorted_array_list.h"

namespace tests
{
    PriorityQueueTestInterface::PriorityQueueTestInterface() :
        SimpleTest("Interface")
    {
    }

    void PriorityQueueTestInterface::test()
    {
        int x = 0;
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        queue->push(0, x);
        queue->peek();
        queue->peekPriority();
        queue->pop();
        queue->assign(*queue);
        delete queue;
        this->logPass("Compiled.");
    }

    structures::PriorityQueue<int>* PriorityQueueUnsortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueUnsortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLimitedSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLimitedSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLinkedListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLinkedList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    structures::PriorityQueue<int>* HeapTestInterface::makePriorityQueue()
    {
        return new structures::Heap<int>();
    }

    PriorityQueueUnsortedArrayListTestOverall::PriorityQueueUnsortedArrayListTestOverall() :
        ComplexTest("PriorityQueueUnsortedArray")
    {
        addTest(new PriorityQueueUnsortedArrayListTestInterface());
        addTest(new PriorityQueueUnsortedArrayListTestPushPop());
        addTest(new PriorityQueueUnsortedArrayListTestAssign());
    }

    PriorityQueueSortedArrayListTestOverall::PriorityQueueSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueSortedArrayList")
    {
        addTest(new PriorityQueueSortedArrayListTestInterface());
        addTest(new PriorityQueueSortedArrayListTestPushPop());
        addTest(new PriorityQueueSortedArrayListTestAssign());
    }

    PriorityQueueLimitedSortedArrayListTestOverall::PriorityQueueLimitedSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueLimitedSortedArrayList")
    {
        addTest(new PriorityQueueLimitedSortedArrayListTestInterface());
        addTest(new PriorityQueueLimitedSortedArrayListTestPushPop());
        addTest(new PriorityQueueLimitedSortedArrayListTestAssign());
    }

    PriorityQueueLinkedListTestOverall::PriorityQueueLinkedListTestOverall() :
        ComplexTest("PriorityQueueLinkedList")
    {
        addTest(new PriorityQueueLinkedListTestInterface());
        addTest(new PriorityQueueLinkedListTestPushPop());
        addTest(new PriorityQueueLinkedListTestAssign());
    }

    PriorityQueueTwoListsTestOverall::PriorityQueueTwoListsTestOverall() :
        ComplexTest("PriorityQueueTwoLists")
    {
        addTest(new PriorityQueueTwoListsTestInterface());
        addTest(new PriorityQueueTwoListsTestPushPop());
        addTest(new PriorityQueueTwoListsTestAssign());
        addTest(new PriorityQueueTwoListsTestPerformanceA());
        addTest(new PriorityQueueTwoListsTestPerformanceB());
        addTest(new PriorityQueueTwoListsTestPerformanceC());
        addTest(new PriorityQueueTwoListsTimeTest);
    }

    HeapTestOverall::HeapTestOverall() :
        ComplexTest("Heap")
    {
        addTest(new HeapTestInterface());
        addTest(new HeapTestPushPop());
        addTest(new HeapTestAssign());
        addTest(new HeapTestPerformanceA());
        addTest(new HeapTestPerformanceB());
        addTest(new HeapTestPerformanceC());
        addTest(new HeapTimeTest());
    }

    PriorityQueueTestOverall::PriorityQueueTestOverall() :
        ComplexTest("PriorityQueue")
    {
        addTest(new PriorityQueueUnsortedArrayListTestOverall());
        addTest(new PriorityQueueSortedArrayListTestOverall());
        addTest(new PriorityQueueLimitedSortedArrayListTestOverall());
        addTest(new PriorityQueueLinkedListTestOverall());
        addTest(new PriorityQueueTwoListsTestOverall());
        addTest(new HeapTestOverall());
    }

    PriorityQueueTestPushPop::PriorityQueueTestPushPop() :
        SimpleTest("Push/Pop")
    {
    }

    void PriorityQueueTestPushPop::test()
    {
        structures::PriorityQueue<char>* queue = this->makePriorityQueue();
        queue->push(3, 'A');
        this->logInfo("queue->push(3, 'A')");
        queue->push(6, 'B');
        this->logInfo("queue->push(6, 'B')");
        queue->push(0, 'C');
        this->logInfo("queue->push(0, 'C')");
        queue->push(4, 'D');
        this->logInfo("queue->push(4, 'D')");
        this->assertTrue(queue->peek() == 'C', "queue->peek() == C");
        char data = queue->pop();
        this->assertTrue(data == 'C', "queue->pop() == C");

        queue->push(7, 'E');
        this->logInfo("queue->push(7, 'E')");
        queue->push(5, 'F');
        this->logInfo("queue->push(5, 'F')");
        queue->push(9, 'G');
        this->logInfo("queue->push(9, 'G')");
        this->assertTrue(queue->peek() == 'A', "queue->peek() == A");
        data = queue->pop();
        this->assertTrue(data == 'A', "queue->pop() == A");

        queue->push(0, 'H');
        this->logInfo("queue->push(0, 'H')");
        queue->push(2, 'I');
        this->logInfo("queue->push(2, 'I')");
        this->assertTrue(queue->peek() == 'H', "queue->peek() == H");
        data = queue->pop();
        this->assertTrue(data == 'H', "queue->pop() == H");

        this->assertTrue(queue->peek() == 'I', "queue->peek() == I");
        data = queue->pop();
        this->assertTrue(data == 'I', "queue->pop() == I");

        this->assertTrue(queue->peek() == 'D', "queue->peek() == D");
        data = queue->pop();
        this->assertTrue(data == 'D', "queue->pop() == D");

        this->assertTrue(queue->peek() == 'F', "queue->peek() == F");
        data = queue->pop();
        this->assertTrue(data == 'F', "queue->pop() == F");

        this->assertTrue(queue->peek() == 'B', "queue->peek() == B");
        data = queue->pop();
        this->assertTrue(data == 'B', "queue->pop() == B");

        this->assertTrue(queue->peek() == 'E', "queue->peek() == E");
        data = queue->pop();
        this->assertTrue(data == 'E', "queue->pop() == E");

        this->assertTrue(queue->peek() == 'G', "queue->peek() == G");
        data = queue->pop();
        this->assertTrue(data == 'G', "queue->pop() == G");
        delete queue;
    }

    structures::PriorityQueue<char>* PriorityQueueUnsortedArrayListTestPushPop::makePriorityQueue()
    {
        return new structures::PriorityQueueUnsortedArrayList<char>();
    }

    structures::PriorityQueue<char>* PriorityQueueSortedArrayListTestPushPop::makePriorityQueue()
    {
        return new structures::PriorityQueueSortedArrayList<char>();
    }


    structures::PriorityQueue<char>* PriorityQueueLimitedSortedArrayListTestPushPop::makePriorityQueue()
    {
        structures::PriorityQueueLimitedSortedArrayList<char>* priorityQueue = new structures::PriorityQueueLimitedSortedArrayList<char>();
        priorityQueue->trySetCapacity(10);
        return priorityQueue;
    }

    structures::PriorityQueue<char>* PriorityQueueLinkedListTestPushPop::makePriorityQueue()
    {
        return new structures::PriorityQueueLinkedList<char>();
    }

    structures::PriorityQueue<char>* PriorityQueueTwoListsTestPushPop::makePriorityQueue()
    {
        return new structures::PriorityQueueTwoLists<char>();
    }

    structures::PriorityQueue<char>* HeapTestPushPop::makePriorityQueue()
    {
        return new structures::Heap<char>();
    }



    PriorityQueueTestAssign::PriorityQueueTestAssign() :
        SimpleTest("Assign")
    {
        srand(static_cast<unsigned int>(time(0)));
    }

    void PriorityQueueTestAssign::test()
    {
        structures::PriorityQueue<int>* queue = makePriorityQueue();
        const int maxSize = 20;
        for (int i = 0; i < maxSize; i++)
        {
            int priority = rand() % maxSize;
            int data = rand();
            queue->push(priority, data);
        }
        structures::PriorityQueue<int>* queueCopy = makePriorityQueue();
        queueCopy->assign(*queue);
        this->logInfo("queueCopy->assign(*queue);");
        this->assertTrue(queue->size() == queueCopy->size(), "queue->size() == queueCopy->size()");
        for (int i = 0; i < maxSize; i++)
        {
            this->assertTrue(queue->pop() == queueCopy->pop(), "queue->pop() == queueCopy->pop()");
        }
        delete queue;
        delete queueCopy;
    }

    structures::PriorityQueue<int>* PriorityQueueUnsortedArrayListTestAssign::makePriorityQueue()
    {
        return new structures::PriorityQueueUnsortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueSortedArrayListTestAssign::makePriorityQueue()
    {
        return new structures::PriorityQueueSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLinkedListTestAssign::makePriorityQueue()
    {
        return new structures::PriorityQueueLinkedList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLimitedSortedArrayListTestAssign::makePriorityQueue()
    {
        structures::PriorityQueueLimitedSortedArrayList<int>* queue = new  structures::PriorityQueueLimitedSortedArrayList<int>();
        queue->trySetCapacity(20);
        return queue;
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestAssign::makePriorityQueue()
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    structures::PriorityQueue<int>* HeapTestAssign::makePriorityQueue()
    {
        return new structures::Heap<int>();
    }

    PriorityQueueTestPerformance::PriorityQueueTestPerformance(int ratioPush, int ratioPop, int ratioPeek, std::string queueType, std::string scenario) :
        SimpleTest("Performance " + scenario),
        ratioPush_(ratioPush),
        ratioPop_(ratioPop),
        ratioPeek_(ratioPeek),
        queueType_(queueType),
        scenario_(scenario)
    {
        srand(static_cast<unsigned int>(time(0)));
    }

    void PriorityQueueTestPerformance::test()
    {
        const int repetitions = 10;
        const int operations = 1000000;
        const int maxPercentage = 100;
        const int minPriority = 100000;

        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        for (int i = 0; i < repetitions; i++)
        {
            int pushOperations = (operations / maxPercentage) * this->ratioPush_;
            int popOperations = (operations / maxPercentage) * this->ratioPop_;
            int peekOperations = (operations / maxPercentage) * this->ratioPeek_;
            structures::DurationType duration = structures::DurationType();

            for (int j = 0; j < operations; j++)
            {
                int funId = rand() % 100;
                if ((funId < this->ratioPush_ && pushOperations > 0) ||
                    (popOperations == 0 && peekOperations == 0 && pushOperations > 0) ||
                    pushOperations > 0 && queue->isEmpty())
                {
                    int data = rand();
                    int priority = rand() % (minPriority + 1);
                    this->startStopwatch();
                    queue->push(priority, data);
                    this->stopStopwatch();
                    duration += this->getElapsedTime();
                    pushOperations--;
                }
                else if ((funId < this->ratioPush_ + this->ratioPop_ && popOperations > 0) ||
                    (pushOperations == 0 && peekOperations == 0 && popOperations > 0))
                {
                    if (queue->isEmpty())
                    {
                        queue->push(0, 0);
                    }
                    this->startStopwatch();
                    queue->pop();
                    this->stopStopwatch();
                    duration += this->getElapsedTime();
                    popOperations--;
                }
                else
                {
                    if (queue->isEmpty())
                    {
                        queue->push(0, 0);
                    }
                    this->startStopwatch();
                    queue->peek();
                    this->stopStopwatch();
                    duration += this->getElapsedTime();
                    peekOperations--;
                }
            }
            structures::Logger::getInstance().logDuration(static_cast<size_t>(operations), duration, this->scenario_ + ";" + this->queueType_);
        }

        delete queue;
    }


    PriorityQueueTestPerformanceA::PriorityQueueTestPerformanceA(std::string priorityQueueType) :
        PriorityQueueTestPerformance(35, 35, 30, priorityQueueType, "A")
    {
    }

    PriorityQueueTestPerformanceB::PriorityQueueTestPerformanceB(std::string priorityQueueType) :
        PriorityQueueTestPerformance(50, 30, 20, priorityQueueType, "B")
    {
    }

    PriorityQueueTestPerformanceC::PriorityQueueTestPerformanceC(std::string priorityQueueType) :
        PriorityQueueTestPerformance(70, 25, 5, priorityQueueType, "C")
    {
    }

    HeapTestPerformanceA::HeapTestPerformanceA() :
        PriorityQueueTestPerformanceA("Heap")
    {
    }

    structures::PriorityQueue<int>* HeapTestPerformanceA::makePriorityQueue() const
    {
        return new structures::Heap<int>();
    }

    HeapTestPerformanceB::HeapTestPerformanceB() :
        PriorityQueueTestPerformanceB("Heap")
    {
    }

    structures::PriorityQueue<int>* HeapTestPerformanceB::makePriorityQueue() const
    {
        return new structures::Heap<int>();
    }

    HeapTestPerformanceC::HeapTestPerformanceC() :
        PriorityQueueTestPerformanceC("Heap")
    {
    }

    structures::PriorityQueue<int>* HeapTestPerformanceC::makePriorityQueue() const
    {
        return new structures::Heap<int>();
    }

    PriorityQueueTwoListsTestPerformanceA::PriorityQueueTwoListsTestPerformanceA() :
        PriorityQueueTestPerformanceA("Priority Queue Two Lists")
    {
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestPerformanceA::makePriorityQueue() const
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    PriorityQueueTwoListsTestPerformanceB::PriorityQueueTwoListsTestPerformanceB() :
        PriorityQueueTestPerformanceB("Priority Queue Two Lists")
    {
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestPerformanceB::makePriorityQueue() const
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    PriorityQueueTwoListsTestPerformanceC::PriorityQueueTwoListsTestPerformanceC() :
        PriorityQueueTestPerformanceC("Priority Queue Two Lists")
    {
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestPerformanceC::makePriorityQueue() const
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    PriorityQueueTimeTest::PriorityQueueTimeTest(std::string queueType) :
        SimpleTest("Time Test"),
        queueType_(queueType)
    {
        srand(static_cast<unsigned int>(time(0)));
    }

    void PriorityQueueTimeTest::test()
    {
        structures::PriorityQueue<int>* queue = makePriorityQueue();
        const int repetitions = 500;
        const int toSize = 10;
        const int minPriority = 100;
        const int testsCount = 100;
        for (int j = 0; j < repetitions; j++)
        {
            for (int i = 0; i < toSize; i++)
            {
                int data = rand();
                int priority = rand() % (minPriority + 1);
                queue->push(priority, data);
            }
            structures::DurationType pushDuration = structures::DurationType();
            structures::DurationType peekDuration = structures::DurationType();
            structures::DurationType popDuration = structures::DurationType();
            for (int k = 0; k < testsCount; k++)
            {
                int data = rand();
                int priority = rand() % (minPriority + 1);

                this->startStopwatch();
                queue->push(priority, data);
                this->stopStopwatch();
                pushDuration += this->getElapsedTime();

                this->startStopwatch();
                queue->peek();
                this->stopStopwatch();
                peekDuration += this->getElapsedTime();

                this->startStopwatch();
                queue->pop();
                this->stopStopwatch();
                popDuration += this->getElapsedTime();
            }
            pushDuration /= testsCount;
            peekDuration /= testsCount;
            popDuration /= testsCount;
            structures::Logger::getInstance().logDuration(queue->size(), pushDuration, "push();" + this->queueType_);
            structures::Logger::getInstance().logDuration(queue->size(), peekDuration, "peek();" + this->queueType_); 
            structures::Logger::getInstance().logDuration(queue->size(), popDuration, "pop();" + this->queueType_);
        }
        delete queue;
    }

    HeapTimeTest::HeapTimeTest() :
        PriorityQueueTimeTest("Heap")
    {
    }

    structures::PriorityQueue<int>* HeapTimeTest::makePriorityQueue() const
    {
        return new structures::Heap<int>();
    }

    PriorityQueueTwoListsTimeTest::PriorityQueueTwoListsTimeTest() :
        PriorityQueueTimeTest("Priority Queue Two Lists")
    {
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTimeTest::makePriorityQueue() const
    {
        return new structures::PriorityQueueTwoLists<int>();
    }
}