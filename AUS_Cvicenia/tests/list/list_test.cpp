#include "list_test.h"

namespace tests
{
// ListTestInterface:

	ListTestInterface::ListTestInterface(std::string name) :
		SimpleTest(std::move(name))
	{
	}

	void ListTestInterface::test()
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

// ArrayListTestInterface:

	ArrayListTestInterface::ArrayListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* ArrayListTestInterface::makeList() const
	{
		return new structures::ArrayList<int>();
	}

// LinkedListTestInterface:

	LinkedListTestInterface::LinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* LinkedListTestInterface::makeList() const
	{
		return new structures::LinkedList<int>();
	}

// DoubleLinkedListTestInterface

	DoubleLinkedListTestInterface::DoubleLinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* DoubleLinkedListTestInterface::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}

// ArrayListTestOverall:

	ArrayListTestOverall::ArrayListTestOverall() :
		ComplexTest("ArrayList")
	{
		addTest(new ArrayListTestInterface());
		addTest(new ArrayListTestInsert());
		addTest(new ArrayListTestRemove());
		addTest(new ArrayListTestPerformanceA());
		addTest(new ArrayListTestPerformanceB());
		addTest(new ArrayListTestPerformanceC());
		addTest(new ArrayListTimeTest());
	}

// LinkedListTestOverall:

	LinkedListTestOverall::LinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		addTest(new LinkedListTestInterface());
		addTest(new LinkedListTestInsert());
		addTest(new LinkedListTestRemove());

		addTest(new LinkedListTimeTest());
	}

// DoubleLinkedListTestOverall


	DoubleLinkedListTestOverall::DoubleLinkedListTestOverall():
		ComplexTest("DoubleLinkedList")
	{
		addTest(new DoubleLinkedListTestInterface());
		addTest(new DoubleLinkedListTestInsert());
		addTest(new DoubleLinkedListTestRemove());
		addTest(new DoubleLinkedListTestPerformanceA());
		addTest(new DoubleLinkedListTestPerformanceB());
		addTest(new DoubleLinkedListTestPerformanceC());
		addTest(new DoubleLinkedListTimeTest());
	}


// ListTestOverall:

	ListTestOverall::ListTestOverall() :
		ComplexTest("List")
	{
		addTest(new ArrayListTestOverall());
		addTest(new LinkedListTestOverall());
		addTest(new DoubleLinkedListTestOverall());
	}

	ListTestInsert::ListTestInsert():
		SimpleTest("Insert")
	{
		
	}
	void ListTestInsert::test()
	{
		structures::List<int>* list = makeList();
		list->add(10);
		list->add(20);
		list->add(30);
		list->add(40);
		this->assertTrue(list->size() == 4, "Step 1: list->size() == 4");
		list->add(100);
		list->add(200);
		list->add(300);
		list->add(400);
		this->assertTrue(list->size() == 8, "Step 2: list->size() == 8");
		for (int i = 0; i < 9; i++)
		{
			list->insert(1, 0);
		}
		this->assertTrue(list->size() == 17, "Step 3: list->size() == 17");
		list->insert(7, 0);
		list->insert(77, 4);
		list->insert(777, 18);
		list->insert(7777, 20);
		this->assertTrue(list->size() == 21, "Step 7: list->size() == 21");
		this->assertTrue(list->at(0) == 7, "list->at(0) == 7");
		this->assertTrue(list->at(1) == 1, "list->at(1) == 1");
		this->assertTrue(list->at(2) == 1, "list->at(2) == 1");
		this->assertTrue(list->at(3) == 1, "list->at(3) == 1");
		this->assertTrue(list->at(4) == 77, "list->at(4) == 77");
		this->assertTrue(list->at(5) == 1, "list->at(5) == 1");
		this->assertTrue(list->at(6) == 1, "list->at(6) == 1");
		this->assertTrue(list->at(7) == 1, "list->at(7) == 1");
		this->assertTrue(list->at(8) == 1, "list->at(8) == 1");
		this->assertTrue(list->at(9) == 1, "list->at(9) == 1");
		this->assertTrue(list->at(10) == 1, "list->at(10) == 1");
		this->assertTrue(list->at(11) == 10, "list->at(11) == 10");
		this->assertTrue(list->at(12) == 20, "list->at(12) == 20");
		this->assertTrue(list->at(13) == 30, "list->at(13) == 30");
		this->assertTrue(list->at(14) == 40, "list->at(14) == 40");
		this->assertTrue(list->at(15) == 100, "list->at(15) == 100");
		this->assertTrue(list->at(16) == 200, "list->at(16) == 200");
		this->assertTrue(list->at(17) == 300, "list->at(17) == 300");
		this->assertTrue(list->at(18) == 777, "list->at(18) == 777");
		this->assertTrue(list->at(19) == 400, "list->at(19) == 400");
		this->assertTrue(list->at(20) == 7777, "list->at(20) == 7777");
		structures::List<int>* listCopy = makeList();
		listCopy->assign(*list);
		this->assertTrue(listCopy->equals(*list), "listCopy->equals(*list)");
		delete list;
		delete listCopy;
	}
	ArrayListTestInsert::ArrayListTestInsert() :
		ListTestInsert()
	{

	}

	structures::List<int>* ArrayListTestInsert::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	LinkedListTestInsert::LinkedListTestInsert() :
		ListTestInsert()
	{

	}

	structures::List<int>* LinkedListTestInsert::makeList() const
	{
		return new structures::LinkedList<int>();
	}

	ListTestRemove::ListTestRemove() :
		SimpleTest("Remove")
	{
	}

	void ListTestRemove::test()
	{
		structures::List<int>* list = makeList();
		for (int i = 0; i < 100; i++)
		{
			list->add(i);
		}
		list->removeAt(99);
		this->assertTrue(list->size() == 99, "Step 1: list->size() == 99");
		this->assertFalse(list->getIndexOf(99) >= 0, "Step 1: list->getIndexOf(99) >= 0");
		list->removeAt(50);
		this->assertTrue(list->size() == 98, "Step 2: list->size() == 98");
		this->assertFalse(list->getIndexOf(50) >= 0, "Step 2: list->getIndexOf(50) >= 0");
		list->removeAt(0);
		this->assertTrue(list->size() == 97, "Step 3: list->size() == 97");
		this->assertFalse(list->getIndexOf(0) >= 0, "Step 3: list->getIndexOf(0) >= 0");
		int data = 5;
		while (data < list->at(static_cast<int>(list->size() - 1)))
		{
			if (data == 50)
			{
				this->assertFalse(list->tryRemove(data), "Step 4: list->tryRemove(" + std::to_string(data) + ")");
			}
			else
			{
				this->assertTrue(list->tryRemove(data), "Step 4: list->tryRemove(" + std::to_string(data) + ")");
			}
			data += 5;
		}
		this->assertTrue(list->size() == 79, "Step 4: list->size() == 79");
		list->clear();
		this->assertTrue(list->isEmpty(), "Step 5: list->isEmpty()");
		delete list;
	}

	ArrayListTestRemove::ArrayListTestRemove() :
		ListTestRemove()
	{
	}

	structures::List<int>* ArrayListTestRemove::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	LinkedListTestRemove::LinkedListTestRemove():
		ListTestRemove()
	{
	}

	structures::List<int>* LinkedListTestRemove::makeList() const
	{
		return new structures::LinkedList<int>();
	}

	DoubleLinkedListTestRemove::DoubleLinkedListTestRemove() :
		ListTestRemove()
	{
	}

	structures::List<int>* DoubleLinkedListTestRemove::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}

	DoubleLinkedListTestInsert::DoubleLinkedListTestInsert() :
		ListTestInsert()
	{
	}

	structures::List<int>* DoubleLinkedListTestInsert::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}

	ListTestPerformance::ListTestPerformance(int ratioInsert, int ratioRemoveAt, int ratioAt, int ratioGetIndexOf, std::string listType, std::string scenario) :
		SimpleTest("Performance " + scenario),
		ratioInsert_(ratioInsert),
		ratioRemoveAt_(ratioRemoveAt),
		ratioAt_(ratioAt),
		ratioGetIndexOf_(ratioGetIndexOf),
		listType_(listType),
		scenario_(scenario)
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void ListTestPerformance::test()
	{
		const int repetitions = 10;
		const int operations = 1000000;
		const int maxPercentage = 100;

		structures::List<int>* list = makeList();
		for (int i = 0; i < repetitions; i++)
		{
			int insertOperations = (operations / maxPercentage) * this->ratioInsert_;
			int removeAtOperations = (operations / maxPercentage) * this->ratioRemoveAt_;
			int atOperations = (operations / maxPercentage) * this->ratioAt_;
			int getIndexOfOperations = (operations / maxPercentage) * this->ratioGetIndexOf_;
			structures::DurationType duration = structures::DurationType();
			for (int j = 0; j < operations; j++)
			{
				int funId = rand() % 100;
				if ((funId < this->ratioInsert_ && insertOperations > 0) ||
					(removeAtOperations == 0 && atOperations == 0 && getIndexOfOperations == 0 && insertOperations > 0) ||
					insertOperations > 0 && list->isEmpty())
				{
					int index = rand() % (list->size() + 1);
					this->startStopwatch();
					list->insert(index, index);
					this->stopStopwatch();
					duration += this->getElapsedTime();
					insertOperations--;
				}
				else if ((funId < this->ratioRemoveAt_ + this->ratioInsert_ && removeAtOperations > 0) ||
					(insertOperations == 0 && atOperations == 0 && getIndexOfOperations == 0 && removeAtOperations > 0))
				{
					if (list->isEmpty())
					{
						list->add(1);
					}
					int index = rand() % list->size();
					this->startStopwatch();
					list->removeAt(index);
					this->stopStopwatch();
					duration += this->getElapsedTime();
					removeAtOperations--;
				}
				else if ((funId < this->ratioRemoveAt_ + this->ratioInsert_ + this->ratioAt_ && atOperations > 0) ||
					(insertOperations == 0 && removeAtOperations == 0 && getIndexOfOperations == 0 && atOperations > 0))
				{
					if (list->isEmpty())
					{
						list->add(1);
					}
					int index = rand() % list->size();
					this->startStopwatch();
					list->at(index) = index;
					this->stopStopwatch();
					duration += this->getElapsedTime();
					atOperations--;
				}
				else if (getIndexOfOperations > 0)
				{
					if (list->isEmpty())
					{
						list->add(1);
					}
					int index = rand() % list->size();
					this->startStopwatch();
					list->getIndexOf(index);
					this->stopStopwatch();
					duration += this->getElapsedTime();
					getIndexOfOperations--;
				}
			}
			structures::Logger::getInstance().logDuration(static_cast<size_t>(operations), duration, this->scenario_ + ";" + this->listType_);
		}
		delete list;
	}

	ListTestPerformanceA::ListTestPerformanceA(std::string listType) :
		ListTestPerformance(20, 20, 50, 10, listType, "A")
	{
	}

	ListTestPerformanceB::ListTestPerformanceB(std::string listType) :
		ListTestPerformance(35, 35, 20, 10, listType, "B")
	{
	}

	ListTestPerformanceC::ListTestPerformanceC(std::string listType) :
		ListTestPerformance(45, 45, 5, 5, listType, "C")
	{
	}

	ArrayListTestPerformanceA::ArrayListTestPerformanceA() :
		ListTestPerformanceA("Array List")
	{
	}

	structures::List<int>* ArrayListTestPerformanceA::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	ArrayListTestPerformanceB::ArrayListTestPerformanceB() :
		ListTestPerformanceB("Array List")
	{
	}

	structures::List<int>* ArrayListTestPerformanceB::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	ArrayListTestPerformanceC::ArrayListTestPerformanceC() :
		ListTestPerformanceC("Array List")
	{
	}

	structures::List<int>* ArrayListTestPerformanceC::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	DoubleLinkedListTestPerformanceA::DoubleLinkedListTestPerformanceA() :
		ListTestPerformanceA("Double Linked List")
	{
	}

	structures::List<int>* DoubleLinkedListTestPerformanceA::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}

	DoubleLinkedListTestPerformanceB::DoubleLinkedListTestPerformanceB() :
		ListTestPerformanceB("Double Linked List")
	{
	}

	structures::List<int>* DoubleLinkedListTestPerformanceB::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}
	DoubleLinkedListTestPerformanceC::DoubleLinkedListTestPerformanceC() :
		ListTestPerformanceC("Double Linked List")
	{
	}

	structures::List<int>* DoubleLinkedListTestPerformanceC::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}

	ListTimeTest::ListTimeTest(std::string listType) :
		SimpleTest("Time Test"),
		listType_(listType)
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void ListTimeTest::test()
	{
		structures::List<int>* list = makeList();
		const int repetitions = 1000;
		const int toSize = 100;
		for (int j = 0; j < repetitions; j++)
		{
			structures::DurationType insertDuration = structures::DurationType();
			structures::DurationType atDuration = structures::DurationType();
			for (int k = 0; k < toSize; k++)
			{
				int index = rand() % static_cast<int>(list->size() + 1);

				this->startStopwatch();
				list->insert(index, index);
				this->stopStopwatch();
				insertDuration += this->getElapsedTime();

				index = rand() % static_cast<int>(list->size());
				this->startStopwatch();
				list->at(index) = index;
				this->stopStopwatch();
				atDuration += this->getElapsedTime();
			}
			insertDuration /= toSize;
			atDuration /= toSize;
			structures::Logger::getInstance().logDuration(list->size(), insertDuration, "insert();" + this->listType_);
			structures::Logger::getInstance().logDuration(list->size(), atDuration, "at();" + this->listType_);
		}
		for (int j = 0; j < repetitions; j++)
		{
			size_t size = list->size();
			structures::DurationType removeAtDuration = structures::DurationType();
			for (int k = 0; k < toSize; k++)
			{
				int index = static_cast<int>(rand() % list->size());
				this->startStopwatch();
				list->removeAt(index);
				this->stopStopwatch();
				removeAtDuration += this->getElapsedTime();
			}
			removeAtDuration /= toSize;
			structures::Logger::getInstance().logDuration(size, removeAtDuration, "removeAt();" + this->listType_);
		}
		delete list;
	}

	ArrayListTimeTest::ArrayListTimeTest() :
		ListTimeTest("Array List")
	{
	}

	structures::List<int>* ArrayListTimeTest::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	DoubleLinkedListTimeTest::DoubleLinkedListTimeTest() :
		ListTimeTest("Double Linked List")
	{
	}

	structures::List<int>* DoubleLinkedListTimeTest::makeList() const
	{
		return new structures::DoubleLinkedList<int>();
	}

	LinkedListTimeTest::LinkedListTimeTest() :
		ListTimeTest("Linked List")
	{
	}

	structures::List<int>* LinkedListTimeTest::makeList() const
	{
		return new structures::LinkedList<int>();
	}
}