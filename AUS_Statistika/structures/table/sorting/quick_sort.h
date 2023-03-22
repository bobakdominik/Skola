#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../../criterion.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T, typename R>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;

		void sort(UnsortedSequenceTable<K, T>& table, Criterion<T, R>& criterion , bool ascending = true);

	private:
		void quick(UnsortedSequenceTable<K, T>& table, int startIndex, int endIndex);
		void quick(UnsortedSequenceTable<K, T>& table, Criterion<T, R>& criterion, int startIndex, int endIndex, bool ascending = true);
	};

	template<typename K, typename T, typename CriterionT>
	inline void QuickSort<K, T, typename CriterionT>::sort(UnsortedSequenceTable<K, T>& table)
	{
		if (table.size() > 1)
		{
			this->quick(table, 0, static_cast<int>(table.size() - 1));
		}
	}

	template<typename K, typename T, typename R>
	inline void QuickSort<K, T, R>::sort(UnsortedSequenceTable<K, T>& table, Criterion<T, R>& criterion, bool ascending)
	{
		if (table.size() > 1)
		{
			this->quick(table, criterion, 0, static_cast<int>(table.size() - 1), ascending);
		}
	}


	template<typename K, typename T, typename CriterionT>
	inline void QuickSort<K, T, typename CriterionT>::quick(UnsortedSequenceTable<K, T>& table, int startIndex, int endIndex)
	{
		K pivot = table.getItemAtIndex(startIndex + ((endIndex - startIndex) / 2)).getKey();

		int left = startIndex;
		int right = endIndex;

		while (left <= right)
		{
			while (table.getItemAtIndex(left).getKey() < pivot)
			{
				left++;
			}
			while (table.getItemAtIndex(right).getKey() > pivot)
			{
				right--;
			}
			if (left <= right)
			{
				table.swap(left, right);
				left++;
				right--;
			}
		}
		if (startIndex < right)
		{
			this->quick(table, startIndex, right);
		}
		if (left < endIndex)
		{
			this->quick(table, left, endIndex);
		}
	}

	template<typename K, typename T, typename R>
	inline void QuickSort<K, T, R>::quick(UnsortedSequenceTable<K, T>& table, Criterion<T, R>& criterion, int startIndex, int endIndex, bool ascending)
	{
		T pivot = table.getItemAtIndex(startIndex + ((endIndex - startIndex) / 2)).accessData();

		int left = startIndex;
		int right = endIndex;

		while (left <= right)
		{
			while ((ascending && criterion.evaluate(table.getItemAtIndex(left).accessData()) < criterion.evaluate(pivot)) || 
				(!ascending && criterion.evaluate(table.getItemAtIndex(left).accessData()) > criterion.evaluate(pivot)))
			{
				left++;
			}
			while ((ascending && criterion.evaluate(table.getItemAtIndex(right).accessData()) > criterion.evaluate(pivot)) ||
				(!ascending && criterion.evaluate(table.getItemAtIndex(right).accessData()) < criterion.evaluate(pivot)))
			{
				right--;
			}
			if (left <= right)
			{
				table.swap(left, right);
				left++;
				right--;
			}
		}
		if (startIndex < right)
		{
			this->quick(table, criterion, startIndex, right, ascending);
		}
		if (left < endIndex)
		{
			this->quick(table, criterion, left, endIndex, ascending);
		}
	}

}