#include "table_test.h"
#include "../../structures/table/binary_search_tree.h"
#include "../../structures/table/hash_table.h"
#include "../../structures/table/linked_table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/table.h"
#include "../../structures/table/treap.h"
#include "../../structures/table/unsorted_sequence_table.h"
#include "../../structures/utils.h"

namespace tests
{
	TableTestInterface::TableTestInterface() :
		SimpleTest("Interface")
	{
	}

	void TableTestInterface::test()
	{
		int x = 0;
		structures::Table<int, int>* table = this->makeTable();
		table->equals(*table);
		table->assign(*table);
		table->insert(0, 0);
		table->find(0);
		table->remove(0);
		table->tryFind(0, x);
		table->containsKey(0);
		delete table;
		this->logPass("Compiled.");
	}

	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* HashTableTestInterface::makeTable()
	{
		return new structures::HashTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInterface::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	structures::Table<int, int>* TreapTestInterface::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInterface::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() :
		ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
		addTest(new BinarySearchTreeTestInsertRemove());
		addTest(new BSTTestPerformanceA);
		addTest(new BSTTestPerformanceB);
		addTest(new BSTTimeTest);
	}

	HashTableTestOverall::HashTableTestOverall() :
		ComplexTest("HashTable")
	{
		addTest(new HashTableTestInterface());
	}

	LinkedTableTestOverall::LinkedTableTestOverall() :
		ComplexTest("LinkedTable")
	{
		addTest(new LinkedTableTestInterface());
		addTest(new LinkedTableTestInsertRemove());
	}

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() :
		ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
		addTest(new SortedSequenceTableTestInsertRemove());
		addTest(new SSTTestPerformanceA);
		addTest(new SSTTestPerformanceB);
		addTest(new SSTTimeTest);
	}

	TreapTestOverall::TreapTestOverall() :
		ComplexTest("Treap")
	{
		addTest(new TreapTestInterface());
		addTest(new TreapTestInsertRemove());
		addTest(new TreapTestPerformanceA());
		addTest(new TreapTestPerformanceB());
		addTest(new TreapTimeTest());
	}

	UnsortedSequenceTableTestOverall::UnsortedSequenceTableTestOverall() :
		ComplexTest("UnsortedSequenceTable")
	{
		addTest(new UnsortedSequenceTableTestInterface());
		addTest(new UnsortedSequenceTableTestInsertRemove());
	}

	TableTestOverall::TableTestOverall() :
		ComplexTest("Table")
	{
		addTest(new BinarySearchTreeTestOverall());
		addTest(new HashTableTestOverall());
		addTest(new LinkedTableTestOverall());
		addTest(new SortedSequenceTableTestOverall());
		addTest(new TreapTestOverall());
		addTest(new UnsortedSequenceTableTestOverall());
	}

	TableTestInsertRemove::TableTestInsertRemove() :
		SimpleTest("Insert/Remove")
	{
	}
	void TableTestInsertRemove::test()
	{
		structures::Logger::getInstance().logInfo("Zacina test!");
		structures::Table<int, int>* table = this->makeTable();
		structures::Table<int, int>* tableCopy;

		table->insert(128, 128);
		this->logInfo("table->insert(128, 128);");
		table->insert(125, 125);
		this->logInfo("table->insert(125, 125);");
		table->insert(213, 213);
		this->logInfo("table->insert(213, 213);");
		table->insert(178, 178);
		this->logInfo("table->insert(178, 178);");
		table->insert(143, 143);
		this->logInfo("table->insert(143, 143);");
		table->insert(122, 122);
		this->logInfo("table->insert(122, 122);");
		table->insert(222, 222);
		this->logInfo("table->insert(222, 222);");
		table->insert(241, 241);
		this->logInfo("table->insert(241, 241);");
		table->insert(259, 259);
		this->logInfo("table->insert(259, 259);");
		table->insert(237, 237);
		this->logInfo("table->insert(237, 237);");

		this->assertTrue(table->size() == 10, "table->size() == 10");
		this->assertTrue(table->containsKey(122), "table->containsKey(122)");
		this->assertTrue(table->containsKey(143), "table->containsKey(143)");
		this->assertTrue(table->containsKey(241), "table->containsKey(241)");
		this->assertFalse(table->containsKey(123), "table->containsKey(123)");

		tableCopy = this->makeTable(*table);
		this->logInfo("tableCopy = this->makeTable(*table);");

		this->assertTrue(tableCopy != table, "&tableCopy != &table");
		this->assertTrue(tableCopy->equals(*table), "tableCopy->equals(*table)");

		tableCopy->find(237) = 234;
		this->logInfo("tableCopy->find(237) = 234;");
		this->assertFalse(table->equals(*tableCopy), "table->equals(*tableCopy)");
		table->find(237) = 234;
		this->logInfo("table->find(237) = 234;");
		this->assertTrue(table->equals(*tableCopy), "table->equals(*tableCopy)");

		tableCopy->remove(241);
		this->logInfo("tableCopy->remove(241)");
		tableCopy->remove(128);
		this->logInfo("tableCopy->remove(128)");
		tableCopy->remove(222);
		this->logInfo("tableCopy->remove(222)");

		this->assertTrue(tableCopy->size() == 7, "tableCopy->size() == 7");
		this->assertTrue(table->size() == 10, "table->size() == 10");
		this->assertFalse(table->equals(*tableCopy), "table->equals(*tableCopy)");

		table->remove(259);
		this->logInfo("table->remove(259);");
		table->remove(125);
		this->logInfo("table->remove(125);");
		table->remove(213);
		this->logInfo("table->remove(213);");
		table->remove(222);
		this->logInfo("table->remove(222);");
		table->remove(178);
		this->logInfo("table->remove(178);");
		table->remove(143);
		this->logInfo("table->remove(143);");
		table->remove(128);
		this->logInfo("table->remove(128);");
		table->remove(122);
		this->logInfo("table->remove(122);");
		table->remove(241);
		this->logInfo("table->remove(241);");
		table->remove(237);
		this->logInfo("table->remove(237);");

		this->assertTrue(tableCopy->size() == 7, "tableCopy->size() == 7");
		this->assertTrue(table->isEmpty(), "table->isEmpty()");
		this->assertFalse(table->equals(*tableCopy), "table->equals(*tableCopy)");
		
		delete tableCopy;
		delete table;
	}
	structures::Table<int, int>* BinarySearchTreeTestInsertRemove::makeTable()
	{
		return new structures::BinarySearchTree<int,int>();
	}
	structures::Table<int, int>* BinarySearchTreeTestInsertRemove::makeTable(structures::Table<int, int>& table)
	{
		structures::BinarySearchTree<int, int>& otherBST = dynamic_cast<structures::BinarySearchTree<int, int>&>(table);
		return new structures::BinarySearchTree<int,int>(otherBST);
	}
	structures::Table<int, int>* SortedSequenceTableTestInsertRemove::makeTable()
	{
		return new structures::SortedSequenceTable<int,int>();
	}
	structures::Table<int, int>* SortedSequenceTableTestInsertRemove::makeTable(structures::Table<int, int>& table)
	{
		structures::SortedSequenceTable<int, int>& otherSST = dynamic_cast<structures::SortedSequenceTable<int, int>&>(table);
		return new structures::SortedSequenceTable<int, int>(otherSST);
	}

	structures::Table<int, int>* TreapTestInsertRemove::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* TreapTestInsertRemove::makeTable(structures::Table<int, int>& table)
	{
		structures::Treap<int, int>& otherTreap = dynamic_cast<structures::Treap<int, int>&>(table);
		return new structures::Treap<int, int>(otherTreap);
	}

	structures::Table<int, int>* LinkedTableTestInsertRemove::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInsertRemove::makeTable(structures::Table<int, int>& table)
	{
		structures::LinkedTable<int, int>& otherLT = dynamic_cast<structures::LinkedTable<int, int>&>(table);
		return new structures::LinkedTable<int, int>(otherLT);
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInsertRemove::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInsertRemove::makeTable(structures::Table<int, int>& table)
	{
		structures::UnsortedSequenceTable<int, int>& otherUST = dynamic_cast<structures::UnsortedSequenceTable<int, int>&>(table);
		return new structures::UnsortedSequenceTable<int, int>(otherUST);
	}

	TableTestPerformance::TableTestPerformance(int ratioInsert, int ratioRemove, int ratioTryFind, std::string tableType, std::string scenario):
		SimpleTest("Performance " + scenario),
		scenario_(scenario),
		ratioInsert_(ratioInsert),
		ratioRemove_(ratioRemove),
		ratioTryFind_(ratioTryFind),
		tableType_(tableType)
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void TableTestPerformance::test()
	{
		const int repetitions = 10;
		const int operations = 100000;
		const int maxPercentage = 100;
		const int maxKey = 100000;

		for (int i = 0; i < repetitions; i++)
		{
			structures::List<int>* freeKeys = new structures::ArrayList<int>();
			structures::List<int>* usedKeys = new structures::ArrayList<int>();
			structures::Table<int, int>* table = this->makeTable();
			for (int j = 0; j <= maxKey; j++)
			{
				freeKeys->add(i);
			}
			int insertOperations = (operations / maxPercentage) * this->ratioInsert_;
			int removeOperations = (operations / maxPercentage) * this->ratioRemove_;
			int tryFindOperations = (operations / maxPercentage) * this->ratioTryFind_;
			structures::DurationType duration = structures::DurationType();

			for (int j = 0; j < operations; j++)
			{
				int funId = rand() % 100; 
				if ((funId < this->ratioInsert_ && insertOperations > 0) ||
					(removeOperations == 0 && tryFindOperations == 0 && insertOperations > 0))
				{
					int index = rand() % freeKeys->size();
					int key = freeKeys->at(index);
					structures::Utils::swap(freeKeys->at(index), freeKeys->at(static_cast<int>(freeKeys->size() - 1)));
					usedKeys->add(freeKeys->removeAt(static_cast<int>(freeKeys->size() - 1)));

					this->startStopwatch();
					table->insert(key, key);
					this->stopStopwatch();
					duration += this->getElapsedTime();
					insertOperations--;
				}
				else if ((funId < this->ratioInsert_ + this->ratioRemove_ && removeOperations > 0) ||
					(insertOperations == 0 && tryFindOperations == 0 && removeOperations > 0))
				{
					if (table->isEmpty())
					{
						int key = freeKeys->removeAt(static_cast<int>(freeKeys->size() - 1));
						usedKeys->add(key);
						table->insert(key, key);
					}
					int index = rand() % usedKeys->size();
					int key = usedKeys->at(index);
					structures::Utils::swap(usedKeys->at(index), usedKeys->at(static_cast<int>(usedKeys->size() - 1)));
					freeKeys->add(usedKeys->removeAt(static_cast<int>(usedKeys->size() - 1)));

					this->startStopwatch();
					table->remove(key);
					this->stopStopwatch();
					duration += this->getElapsedTime();
					removeOperations--;
				}
				else
				{
					int key = rand() % (maxKey + 1);
					int data;
					this->startStopwatch();
					table->tryFind(key, data);
					this->stopStopwatch();
					duration += this->getElapsedTime();
					tryFindOperations--;
				}
			}
			structures::Logger::getInstance().logDuration(static_cast<size_t>(operations), duration, this->scenario_ + ";" + this->tableType_);
			delete usedKeys;
			delete freeKeys;
			delete table;
		}
	}

	TableTestPerformanceA::TableTestPerformanceA(std::string tableType) :
		TableTestPerformance(20, 20, 60, tableType, "A")
	{
	}

	TableTestPerformanceB::TableTestPerformanceB(std::string tableType) :
		TableTestPerformance(40, 40, 20, tableType, "B")
	{
	}

	SSTTestPerformanceA::SSTTestPerformanceA():
		TableTestPerformanceA("Sorted Sequence Table")
	{
	}

	structures::Table<int, int>* SSTTestPerformanceA::makeTable() const
	{
		return new structures::SortedSequenceTable<int,int>();
	}

	SSTTestPerformanceB::SSTTestPerformanceB() :
		TableTestPerformanceB("Sorted Sequence Table")
	{
	}

	structures::Table<int, int>* SSTTestPerformanceB::makeTable() const
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	BSTTestPerformanceA::BSTTestPerformanceA() :
		TableTestPerformanceA("Binary Search Tree")
	{
	}

	structures::Table<int, int>* BSTTestPerformanceA::makeTable() const
	{
		return new structures::BinarySearchTree<int,int>();
	}

	BSTTestPerformanceB::BSTTestPerformanceB() :
		TableTestPerformanceB("Binary Search Tree")
	{
	}

	structures::Table<int, int>* BSTTestPerformanceB::makeTable() const
	{
		return new structures::BinarySearchTree<int,int>();
	}

	TreapTestPerformanceA::TreapTestPerformanceA() :
		TableTestPerformanceA("Treap")
	{
	}

	structures::Table<int, int>* TreapTestPerformanceA::makeTable() const
	{
		return new structures::Treap<int, int>();
	}

	TreapTestPerformanceB::TreapTestPerformanceB() :
		TableTestPerformanceB("Treap")
	{
	}

	structures::Table<int, int>* TreapTestPerformanceB::makeTable() const
	{
		return new structures::Treap<int, int>();
	}

	TableTimeTest::TableTimeTest(std::string tableType):
		SimpleTest("Time"),
		tableType_(tableType)
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void TableTimeTest::test()
	{
		int sizeGap = 10;
		const int repetitions = 500;
		const int maxKey = 100000;
		const int testsCount = 100;

		structures::List<int>* freeKeys = new structures::ArrayList<int>();
		structures::List<int>* usedKeys = new structures::ArrayList<int>();
		structures::Table<int, int>* table = this->makeTable();

		for (int i = 0; i <= maxKey; i++)
		{
			freeKeys->add(i);
		}

		for (int i = 0; i < repetitions; i++)
		{
			for (int j = 0; j < sizeGap; j++)
			{
				int index = rand() % freeKeys->size();
				int key = freeKeys->at(index);
				structures::Utils::swap(freeKeys->at(index), freeKeys->at(static_cast<int>(freeKeys->size() - 1)));
				usedKeys->add(freeKeys->removeAt(static_cast<int>(freeKeys->size() - 1)));
				table->insert(key, key);
			}
			structures::DurationType insertDuration = structures::DurationType();
			structures::DurationType deleteDuration = structures::DurationType();
			structures::DurationType tryFindDuration = structures::DurationType();

			for (int j = 0; j < testsCount; j++)
			{
				int index = rand() % freeKeys->size();
				structures::Utils::swap(freeKeys->at(index), freeKeys->at(static_cast<int>(freeKeys->size() - 1)));
				int key = freeKeys->removeAt(static_cast<int>(freeKeys->size() - 1));
				usedKeys->add(key);

				this->startStopwatch();
				table->insert(key, key);
				this->stopStopwatch();
				insertDuration += this->getElapsedTime();

				key = rand() % (maxKey + 1);
				int data;
				this->startStopwatch();
				table->tryFind(key, data);
				this->stopStopwatch();
				tryFindDuration += this->getElapsedTime();

				index = rand() % usedKeys->size();
				structures::Utils::swap(usedKeys->at(index), usedKeys->at(static_cast<int>(usedKeys->size() - 1)));
				key = usedKeys->removeAt(static_cast<int>(usedKeys->size() - 1));
				freeKeys->add(key);

				this->startStopwatch();
				table->remove(key);
				this->stopStopwatch();
				deleteDuration += this->getElapsedTime();
			}
			insertDuration /= testsCount;
			tryFindDuration /= testsCount;
			deleteDuration /= testsCount;
			structures::Logger::getInstance().logDuration(table->size(), insertDuration, "insert();" + this->tableType_);
			structures::Logger::getInstance().logDuration(table->size(), tryFindDuration, "tryFind();" + this->tableType_);
			structures::Logger::getInstance().logDuration(table->size(), deleteDuration, "remove();" + this->tableType_);
		}
		delete freeKeys;
		delete usedKeys;
		delete table;
	}

	BSTTimeTest::BSTTimeTest() :
		TableTimeTest("Binary Search Tree")
	{
	}

	structures::Table<int, int>* BSTTimeTest::makeTable() const
	{
		return new structures::BinarySearchTree<int,int>();
	}

	SSTTimeTest::SSTTimeTest():
		TableTimeTest("Sorted Sequence Table")
	{
	}

	structures::Table<int, int>* SSTTimeTest::makeTable() const
	{
		return new structures::SortedSequenceTable<int, int>();
	}


	TreapTimeTest::TreapTimeTest() :
		TableTimeTest("Treap")
	{
	}

	structures::Table<int, int>* TreapTimeTest::makeTable() const
	{
		return new structures::Treap<int, int>();
	}

}