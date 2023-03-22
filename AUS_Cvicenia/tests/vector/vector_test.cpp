#include "vector_test.h"
#include "../../structures/vector/vector.h"

namespace tests
{
// VectorTestInterface:

    VectorTestInterface::VectorTestInterface() :
        SimpleTest("Interface")
    {
    }

    void VectorTestInterface::test()
    {
        structures::Vector* vector = new structures::Vector(10);
        vector->size();
        vector->assign(*vector);
        vector->equals(*vector);
        vector->at(0);
        vector->getBytePointer(0);
        structures::Vector::copy(*vector, 0, *vector, 0, 1);
        SimpleTest::logPass("Compiled.");
        delete vector;
        vector = nullptr;
    }



// VectorTestOverall:

    VectorTestOverall::VectorTestOverall() :
        ComplexTest("Vector")
    {
        this->addTest(new VectorTestInterface());
        this->addTest(new VectorTestAt());
        this->addTest(new VectorTestCopyConstruct());
        this->addTest(new VectorTimeTest());
    }


    VectorTestAt::VectorTestAt() :
        SimpleTest("At")
    {
    }

    void VectorTestAt::test()
    {
        structures::Vector* vector = new structures::Vector(10);
        this->assertTrue(vector->size() == 10, "vector->size() == 10");
        for (int i = 0; i < 10; i++)
        {
            vector->at(i) = static_cast<structures::byte>(i);
        }

        for (int i = 0; i < 10; i++)
        {
            this->assertTrue(vector->at(i) == i, "vector->at(" + std::to_string(i) + ") == " + std::to_string(i));

        }

        for (int i = 0; i < 10; i++)
        {
            this->assertTrue(*vector->getBytePointer(i) == i, "*vector->getBytePointer(" + std::to_string(i) + ") == " + std::to_string(i));

        }
        delete vector;
        vector = nullptr;
    }


    VectorTestCopyConstruct::VectorTestCopyConstruct() :
        SimpleTest("Copy")
    {
    }

    void VectorTestCopyConstruct::test()
    {
        structures::Vector* vector = new structures::Vector(10);
        this->assertTrue(vector->size() == 10, "vector->size() == 10");
        for (int i = 0; i < 10; i++)
        {
            vector->at(i) = static_cast<structures::byte>(i);
        }

        structures::Vector* vectorCopy = new structures::Vector(*vector);
        this->assertTrue(vector->equals(*vectorCopy), "vector->equals(*vectorCopy)");
        vectorCopy->at(0) = 10;
        this->assertFalse(vector->equals(*vectorCopy), "vector->equals(*vectorCopy)");
        vector->assign(*vectorCopy);
        this->assertTrue(vector->equals(*vectorCopy), "vector->equals(*vectorCopy)");
        delete vector;
        vector = nullptr;
        delete vectorCopy;
        vectorCopy = nullptr;
    }

    VectorTimeTest::VectorTimeTest() :
        SimpleTest("Time")
    {

    }

    void VectorTimeTest::test()
    {
        this->startStopwatch();
        structures::Vector* vector = new structures::Vector(1000000);
        for (int i = 0; i < vector->size(); i++)
        {
            vector->at(i) = static_cast<structures::byte>(i % 256);
        }
        delete vector;
        vector = nullptr;
        this->stopStopwatch();
        Milliseconds time = this->getElapsedTime();
        this->logInfo("Operation required " + std::to_string(time.count()) + "ms");
        structures::Logger::getInstance().logDuration(1000000, time, "Time tests of vector creation and deletion");
    }
}