#pragma once

#include "../list/array_list.h"
#include "sequence_table.h"

namespace structures
{

	/// <summary> Utriedena sekvencna tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SortedSequenceTable : public SequenceTable<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		SortedSequenceTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> SortedSequenceTable, z ktorej sa prevezmu vlastnosti. </param>
		SortedSequenceTable(SortedSequenceTable<K, T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

	protected:
		/// <summary> Najde prvok tabulky s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <returns> Prvok tabulky s danym klucom, ak neexistuje, vrati nullptr. </returns>
		TableItem<K, T>* findTableItem(const K& key) override;

	private:
		/// <summary> Najde index prvku s danym klucom. Kontroluje rozsah [indexStart, indexEnd). Pracuje na principe bisekcie. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "indexStart"> Pociatocny index prehladavanej sekvencie. </param>
		/// <param name = "indexEnd"> Koncovy index prehladavanej sekvencie. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Index prvku s danym klucom. Ak sa kluc v tabulke nenachadza, vrati index, kde by sa mal prvok s takym klucom nachadzat. </returns>
		int indexOfKey(K key, int indexStart, int indexEnd, bool& found);
	};

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable() :
		SequenceTable<K, T>(new ArrayList<TableItem<K, T>*>())
	{
	}

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable(SortedSequenceTable<K, T>& other) :
		SortedSequenceTable()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline Structure& SortedSequenceTable<K, T>::assign(Structure& other)
	{
		return SequenceTable<K, T>::assignSequenceTable(dynamic_cast<SortedSequenceTable<K, T>&>(other));
	}

	template<typename K, typename T>
	inline bool SortedSequenceTable<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<SortedSequenceTable<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline void SortedSequenceTable<K, T>::insert(const K& key, const T& data)
	{
		//Done 08: SortedSequenceTable insert
		bool found;
		int index = this->indexOfKey(key, 0, static_cast<int>(this->list_->size()), found);
		/*if (found)
		{
			throw std::logic_error("SortedSequenceTable<K, T>::insert: Key already exists in table.");
		}*/
		this->list_->insert(new TableItem<K, T>(key, data), index);
	}

	template<typename K, typename T>
	inline T SortedSequenceTable<K, T>::remove(const K& key)
	{
		//Done 08: SortedSequenceTable remove
		bool found;
		int index = this->indexOfKey(key, 0, static_cast<int>(this->list_->size()), found);
		if (!found)
		{
			throw std::logic_error("SortedSequenceTable<K, T>::remove: No such key in table.");
		}
		TableItem<K, T>* item = this->list_->removeAt(index);
		T data = item->accessData();
		delete item;
		return data;
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SortedSequenceTable<K, T>::findTableItem(const K& key)
	{
		//Done 08: SortedSequenceTable findTableItem
		bool found;
		int index = this->indexOfKey(key, 0, static_cast<int>(this->list_->size()), found);
		return found ? this->list_->at(index) : nullptr;
	}

	template<typename K, typename T>
	inline int SortedSequenceTable<K, T>::indexOfKey(K key, int indexStart, int indexEnd, bool& found)
	{
		//Done 08: SortedSequenceTable indexOfKey
		int mid = indexStart + ((indexEnd - indexStart) / 2);
		if (mid == static_cast<int>(this->list_->size()))
		{
			found = false;
			return mid;
		}
		if (this->list_->at(mid)->getKey() == key)
		{
			found = true;
			return mid;
		}
		else
		{
			if (indexStart >= indexEnd -1) // dorobit kontrolu indexov, ci porovnavam mensi alebo vacsi kluc
			{
				found = false;
				return this->list_->at(mid)->getKey() > key? indexStart : indexEnd;
			}
			else
			{
				if (this->list_->at(mid)->getKey() < key)
				{
					return this->indexOfKey(key, mid+1, indexEnd, found);
				}
				else
				{
					return this->indexOfKey(key, indexStart, mid, found);
				}
			}
		}
	}
}