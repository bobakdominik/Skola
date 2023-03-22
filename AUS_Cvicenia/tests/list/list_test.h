#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"
#include "../../structures/list/double_linked_list.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania listu avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class ListTestInterface
		: public SimpleTest
	{
	public:
		ListTestInterface(std::string name);
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody ArrayListu.
	/// </summary>
	class ArrayListTestInterface
		: public ListTestInterface
	{
	public:
		ArrayListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zavola vsetky metody LinkedListu.
	/// </summary>
	class LinkedListTestInterface
		: public ListTestInterface
	{
	public:
		LinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zavola vsetky metody Double LinkedListu.
	/// </summary>
	class DoubleLinkedListTestInterface
		: public ListTestInterface
	{
	public:
		DoubleLinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};


	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList.
	/// </summary>
	class ArrayListTestOverall
		: public ComplexTest
	{
	public:
		ArrayListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju LinkedList.
	/// </summary>
	class LinkedListTestOverall
		: public ComplexTest
	{
	public:
		LinkedListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju Double LinkedList.
	/// </summary>
	class DoubleLinkedListTestOverall
		: public ComplexTest
	{
	public:
		DoubleLinkedListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList a LinkedList.
	/// </summary>
	class ListTestOverall :
		public ComplexTest
	{
	public:
		ListTestOverall();
	};

	class ListTestInsert :
		public SimpleTest 
	{
	public:
		ListTestInsert();
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	};

	class ArrayListTestInsert :
		public ListTestInsert
	{
	public:
		ArrayListTestInsert();

	protected: 
		structures::List<int>* makeList() const override;
	};

	class LinkedListTestInsert :
		public ListTestInsert
	{
	public:
		LinkedListTestInsert();

	protected:
		structures::List<int>* makeList() const override;
	};

	class DoubleLinkedListTestInsert :
		public ListTestInsert
	{
	public:
		DoubleLinkedListTestInsert();

	protected:
		structures::List<int>* makeList() const override;
	};

	class ListTestRemove :
		public SimpleTest
	{
	public:
		ListTestRemove();
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	};

	class ArrayListTestRemove :
		public ListTestRemove
	{
	public:
		ArrayListTestRemove();

	protected:
		structures::List<int>* makeList() const override;
	};

	class LinkedListTestRemove :
		public ListTestRemove
	{
	public:
		LinkedListTestRemove();

	protected:
		structures::List<int>* makeList() const override;
	};

	class DoubleLinkedListTestRemove :
		public ListTestRemove
	{
	public:
		DoubleLinkedListTestRemove();

	protected:
		structures::List<int>* makeList() const override;
	};

	//########################################################################################################
	// Uloha 2
	//########################################################################################################

	//################################################################
	// List test, casove zlozitosti
	//################################################################

	class ListTestPerformance
		: public SimpleTest
	{
	public:
		ListTestPerformance(int ratioInsert, int ratioRemoveAt, int ratioAt, int ratioGetIndexOf, std::string listType, std::string scenario);
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	
	private:
		int ratioInsert_;
		int ratioRemoveAt_;
		int ratioAt_;
		int ratioGetIndexOf_;
		std::string listType_;
		std::string scenario_;

	};

	//################################################################
	// List test, scenar A-C
	//################################################################

	class ListTestPerformanceA
		: public ListTestPerformance
	{
	public:
		ListTestPerformanceA(std::string listType);
	};

	class ListTestPerformanceB
		: public ListTestPerformance
	{
	public:
		ListTestPerformanceB(std::string listType);
	};

	class ListTestPerformanceC
		: public ListTestPerformance
	{
	public:
		ListTestPerformanceC(std::string listType);
	};

	//################################################################
	// ArrayList test, scenar A-C
	//################################################################

	class ArrayListTestPerformanceA
		: public ListTestPerformanceA
	{
	public:
		ArrayListTestPerformanceA();

	protected:
		structures::List<int>* makeList() const override;
	};

	class ArrayListTestPerformanceB
		: public ListTestPerformanceB
	{
	public:
		ArrayListTestPerformanceB();

	protected:
		structures::List<int>* makeList() const override;
	};

	class ArrayListTestPerformanceC
		: public ListTestPerformanceC
	{
	public:
		ArrayListTestPerformanceC();

	protected:
		structures::List<int>* makeList() const override;
	};

	//################################################################
	// DoubleLinkedList test, scenar A-C
	//################################################################

	class DoubleLinkedListTestPerformanceA
		: public ListTestPerformanceA
	{
	public:
		DoubleLinkedListTestPerformanceA();

	protected:
		structures::List<int>* makeList() const override;
	};

	class DoubleLinkedListTestPerformanceB
		: public ListTestPerformanceB
	{
	public:
		DoubleLinkedListTestPerformanceB();

	protected:
		structures::List<int>* makeList() const override;
	};

	class DoubleLinkedListTestPerformanceC
		: public ListTestPerformanceC
	{
	public:
		DoubleLinkedListTestPerformanceC();

	protected:
		structures::List<int>* makeList() const override;
	};

	//########################################################################################################
	// Uloha 3
	//########################################################################################################

	//################################################################
	//Casova analyza funkcii insert(), at(), removeAt()
	//################################################################

	class ListTimeTest
		: public SimpleTest
	{
	public:
		ListTimeTest(std::string listType);
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;

	private:
		std::string listType_;
	};

	class ArrayListTimeTest
		: public ListTimeTest
	{
	public:
		ArrayListTimeTest();

	protected:
		structures::List<int>* makeList() const override;
	};

	class LinkedListTimeTest
		: public ListTimeTest
	{
	public:
		LinkedListTimeTest();

	protected:
		structures::List<int>* makeList() const override;
	};

	class DoubleLinkedListTimeTest
		: public ListTimeTest
	{
	public:
		DoubleLinkedListTimeTest();

	protected:
		structures::List<int>* makeList() const override;
	};
}