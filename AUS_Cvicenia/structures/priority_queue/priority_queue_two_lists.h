#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;

		/// <summary> Minimalna kapacita kratkeho zoznamu. </summary>
		const int minShortListCapacity_ = 4;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
		this->shortList_->trySetCapacity(minShortListCapacity_);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		//Done 06: PriorityQueueTwoLists ~PriorityQueueTwoLists
		this->clear();
		delete this->longList_;
		delete this->shortList_;
		this->longList_ = nullptr;
		this->shortList_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		//Done 06: PriorityQueueTwoLists assign
		if (this != &other)
		{
			this->clear();
			PriorityQueueTwoLists<T>& otherPQ = dynamic_cast<PriorityQueueTwoLists<T>&>(other);

			this->shortList_->assign(*otherPQ.shortList_);
			for (PriorityQueueItem<T>* otherItem : *otherPQ.longList_)
			{
				PriorityQueueItem<T>* item = new PriorityQueueItem<T>(*otherItem);
				this->longList_->add(item);
			}
		}
		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		//Done 06: PriorityQueueTwoLists size
		return this->longList_->size() + this->shortList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		//Done 06: PriorityQueueTwoLists clear
		this->shortList_->clear();
		for (PriorityQueueItem<T>* item : *this->longList_)
		{
			delete item;
		}
		this->longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		//Done 06: PriorityQueueTwoLists push
		if (this->longList_->size() == 0 || this->shortList_->minPriority() > priority)
		{
			PriorityQueueItem<T>* ret = this->shortList_->pushAndRemove(priority, data);
			if (ret != nullptr)
			{
				this->longList_->add(ret);
			}
		}
		else
		{
			PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
			this->longList_->add(item);
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		//Done 06: PriorityQueueTwoLists pop
		T data = this->shortList_->pop();
		if (this->shortList_->size() == 0 && this->longList_->size() > 0)
		{
			size_t newSize = static_cast<size_t>(sqrt(this->longList_->size()));
			if (newSize < minShortListCapacity_)
			{
				newSize = minShortListCapacity_;
			}
			this->shortList_->trySetCapacity(newSize);
			LinkedList<PriorityQueueItem<T>*>* newList = new LinkedList<PriorityQueueItem<T>*>();
			while (this->longList_->size() > 0)
			{
				PriorityQueueItem<T>* listItem = this->longList_->removeAt(0);
				if (this->shortList_->size() < newSize || this->shortList_->minPriority() > listItem->getPriority())
				{
					PriorityQueueItem<T>* ret = this->shortList_->pushAndRemove(listItem->getPriority(), listItem->accessData());
					delete listItem;
					if (ret != nullptr)
					{
						newList->add(ret);
					}
				}
				else
				{
					newList->add(listItem);
				}
				/*PriorityQueueItem<T>* ret = this->shortList_->pushAndRemove(listItem->getPriority(), listItem->accessData());
				delete listItem;
				if (ret != nullptr)
				{
					newList->add(ret);
				}*/
			}
			delete this->longList_;
			this->longList_ = newList;
		}
		return data;
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		//Done 06: PriorityQueueTwoLists peek
		return this->shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		//Done 06: PriorityQueueTwoLists peekPriority
		return this->shortList_->peekPriority();
	}
}