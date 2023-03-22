#pragma once

#include "table.h"
#include "../list/list.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Sekvencna tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SequenceTable : public Table<K, T>
	{
	public:
		/// <summary> Destruktor. </sumary>
		~SequenceTable();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

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

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky tabulky. </param>
		/// <remarks>
		/// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu.
		/// List dealokuje tento objekt.
		/// </remarks>
		SequenceTable(List<TableItem<K, T>*>* list);

		/// <summary> Najde prvok tabulky s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <returns> Prvok tabulky s danym klucom, ak neexistuje, vrati nullptr. </returns>
		virtual TableItem<K, T>* findTableItem(const K& key);

		/// <summary> Priradenie struktury. Pomocna metoda, ktora prebera referenciu, ktoru posle potomok. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		/// <summary>
		SequenceTable<K, T>& assignSequenceTable(SequenceTable<K, T>& other);

	protected:
		List<TableItem<K, T>*>* list_;
	};

	template<typename K, typename T>
	inline SequenceTable<K, T>::~SequenceTable()
	{
		//Done 08: SequenceTable ~SequenceTable
		this->clear();
		delete this->list_;
		this->list_ = nullptr;
	}

	template<typename K, typename T>
	inline size_t SequenceTable<K, T>::size()
	{
		//Done 08: SequenceTable size
		return this->list_->size();
	}

	template<typename K, typename T>
	inline T& SequenceTable<K, T>::find(const K& key)
	{ 
		//Done 08: SequenceTable find
		TableItem<K, T>* tableItem = this->findTableItem(key);
		if (tableItem == nullptr)
		{
			throw std::out_of_range("SequenceTable<K, T>::find: No such key");
		}
		return tableItem->accessData();
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::insert(const K& key, const T& data)
	{
		//Done 08: SequenceTable insert
		if (this->containsKey(key))
		{
			throw std::logic_error("SequenceTable<K, T>::insert: Key already exists in table");
		}
		TableItem<K, T>* tableItem = new TableItem<K, T>(key, data);
		this->list_->add(tableItem);
	}

	template<typename K, typename T>
	inline T SequenceTable<K, T>::remove(const K& key)
	{
		//Done 08: SequenceTable remove
		int index = -1;
		for (int i = 0; i < static_cast<int>(this->list_->size()); i++)
		{
			if (this->list_->at(i)->getKey() == key)
			{
				index = i;
				break;
			}
		}
		if (index < 0)
		{
			throw std::logic_error("SequenceTable<K, T>::remove: No such key in table");
		}
		TableItem<K, T>* item = this->list_->removeAt(index);
		T data = item->accessData();
		delete item;
		return data;

		/*TableItem<K, T>* tableItem = this->findTableItem(key);
		if (tableItem == nullptr)
		{
			throw std::logic_error("SequenceTable<K, T>::remove: No such key in table");
		}
		T data = tableItem->accessData();
		this->list_->tryRemove(tableItem);
		delete tableItem;
		return data;*/
	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::tryFind(const K& key, T& data)
	{
		//Done 08: SequenceTable tryFind
		TableItem<K, T>* tableItem = this->findTableItem(key);
		if (tableItem != nullptr)
		{
			data = tableItem->accessData();
			return true;
		}
		return false;
	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::containsKey(const K& key)
	{
		//Done 08: SequenceTable containsKey
		return this->findTableItem(key) != nullptr;
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::clear()
	{
		//Done 08: SequenceTable clear
		for (TableItem<K,T>* tableItem: *this->list_)
		{
			delete tableItem;
		}
		this->list_->clear();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getBeginIterator()
	{
		//Done 08: SequenceTable getBeginIterator
		return this->list_->getBeginIterator();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getEndIterator()
	{
		//Done 08: SequenceTable getEndIterator
		return this->list_->getEndIterator();
	}

	template<typename K, typename T>
	inline SequenceTable<K, T>::SequenceTable(List<TableItem<K, T>*>* list) :
		Table<K, T>(),
		list_(list)
	{
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SequenceTable<K, T>::findTableItem(const K& key)
	{
		//Done 08: SequenceTable findTableItem
		for (TableItem<K, T>* tableItem: *this->list_)
		{
			if (tableItem->getKey() == key)
			{
				return tableItem;
			}
		}
		return nullptr;
	}
	
	template<typename K, typename T>
	inline SequenceTable<K, T>& SequenceTable<K, T>::assignSequenceTable(SequenceTable<K, T>& other)
	{
		//Done 08: SequenceTable assignSequenceTable
		if (this != &other)
		{
			this->clear();
			for (TableItem<K,T>* item: *other.list_)
			{
				this->list_->add(new TableItem<K,T>(*item));
			}
		}
		return *this;
	}
}