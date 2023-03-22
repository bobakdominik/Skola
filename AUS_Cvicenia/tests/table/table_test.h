#pragma once

#include "../test.h"
#include "../../structures/table/table.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania tabulky avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class TableTestInterface
		: public SimpleTest
	{
	public:
		TableTestInterface();
		void test() override;

	protected:
		virtual structures::Table<int, int>* makeTable() = 0;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class BinarySearchTreeTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class HashTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class LinkedTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class SortedSequenceTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class TreapTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class UnsortedSequenceTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class BinarySearchTreeTestOverall
		: public ComplexTest
	{
	public:
		BinarySearchTreeTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class HashTableTestOverall
		: public ComplexTest
	{
	public:
		HashTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class LinkedTableTestOverall
		: public ComplexTest
	{
	public:
		LinkedTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class SortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		SortedSequenceTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class TreapTestOverall
		: public ComplexTest
	{
	public:
		TreapTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class UnsortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		UnsortedSequenceTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju tabulku.
	/// </summary>
	class TableTestOverall
		: public ComplexTest
	{
	public:
		TableTestOverall();
	};

	//########################################################################################################
	// Uloha 1
	//########################################################################################################

	//################################################################
	// Table test implementacie 
	//################################################################


	class TableTestInsertRemove
		: public SimpleTest
	{
	public:
		TableTestInsertRemove();
		void test() override;

	protected:
		virtual structures::Table<int, int>* makeTable() = 0;
		virtual structures::Table<int, int>* makeTable(structures::Table<int, int>& table) = 0;
	};

	class BinarySearchTreeTestInsertRemove
		: public TableTestInsertRemove
	{
	protected:
		structures::Table<int, int>* makeTable() override;
		structures::Table<int, int>* makeTable(structures::Table<int, int>& table);
	};

	class SortedSequenceTableTestInsertRemove
		: public TableTestInsertRemove
	{
	protected:
		structures::Table<int, int>* makeTable() override;
		structures::Table<int, int>* makeTable(structures::Table<int, int>& table);
	};

	class TreapTestInsertRemove
		: public TableTestInsertRemove
	{
	protected:
		structures::Table<int, int>* makeTable() override;
		structures::Table<int, int>* makeTable(structures::Table<int, int>& table);
	};

	class LinkedTableTestInsertRemove
		: public TableTestInsertRemove
	{
	protected:
		structures::Table<int, int>* makeTable() override;
		structures::Table<int, int>* makeTable(structures::Table<int, int>& table);
	};

	class UnsortedSequenceTableTestInsertRemove
		: public TableTestInsertRemove
	{
	protected:
		structures::Table<int, int>* makeTable() override;
		structures::Table<int, int>* makeTable(structures::Table<int, int>& table);
	};

	//########################################################################################################
	// Uloha 2
	//########################################################################################################

	//################################################################
	// Table test, overenie vykonu v scenari 
	//################################################################

	class TableTestPerformance
		: public SimpleTest
	{
	public:
		TableTestPerformance(int ratioInsert, int ratioRemove, int ratioTryFind, std::string tableType, std::string scenario);
		void test() override;

	protected:
		virtual structures::Table<int,int>* makeTable() const = 0;

	private:
		int ratioInsert_;
		int ratioRemove_;
		int ratioTryFind_;
		std::string tableType_;
		std::string scenario_;

	};

	//################################################################
	// Table test, scenar A-B
	//################################################################

	class TableTestPerformanceA
		: public TableTestPerformance
	{
	public:
		TableTestPerformanceA(std::string tableType);
	};

	class TableTestPerformanceB
		: public TableTestPerformance
	{
	public:
		TableTestPerformanceB(std::string tableType);
	};

	//################################################################
	// Binary search tree test, scenar A-B
	//################################################################

	class BSTTestPerformanceA
		: public TableTestPerformanceA
	{
	public:
		BSTTestPerformanceA();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};

	class BSTTestPerformanceB
		: public TableTestPerformanceB
	{
	public:
		BSTTestPerformanceB();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};

	//################################################################
	// Sorted sequence table test, scenar A-B
	//################################################################

	class SSTTestPerformanceA
		: public TableTestPerformanceA
	{
	public:
		SSTTestPerformanceA();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};

	class SSTTestPerformanceB
		: public TableTestPerformanceB
	{
	public:
		SSTTestPerformanceB();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};

	//################################################################
	// Binary search tree test, scenar A-B
	//################################################################

	class TreapTestPerformanceA
		: public TableTestPerformanceA
	{
	public:
		TreapTestPerformanceA();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};

	class TreapTestPerformanceB
		: public TableTestPerformanceB
	{
	public:
		TreapTestPerformanceB();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};

	//########################################################################################################
	// Uloha 3
	//########################################################################################################

	//################################################################
	//Casova analyza funkcii insert(), remove() a tryFind()
	//################################################################

	class TableTimeTest
		: public SimpleTest
	{
	public:
		TableTimeTest(std::string tableType);
		void test() override;

	protected:
		virtual structures::Table<int, int>* makeTable() const = 0;

	private:
		std::string tableType_;
	};

	class BSTTimeTest
		: public TableTimeTest
	{
	public:
		BSTTimeTest();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};

	class SSTTimeTest
		: public TableTimeTest
	{
	public:
		SSTTimeTest();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};

	class TreapTimeTest
		: public TableTimeTest
	{
	public:
		TreapTimeTest();

	protected:
		structures::Table<int, int>* makeTable() const override;
	};
}