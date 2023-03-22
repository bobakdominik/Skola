#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany utriednym ArrayList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueSortedArrayList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueSortedArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueSortedArrayList(PriorityQueueSortedArrayList<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

	protected:
		/// <summary> Vrati index v utriedenom ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>
		int indexOfPeek() override;
	};

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList(PriorityQueueSortedArrayList<T>& other) :
		PriorityQueueList<T>(
			new ArrayList<PriorityQueueItem<T>*>(
				dynamic_cast<ArrayList<PriorityQueueItem<T>*>&>(*other.list_)))
	{
	}

	template<typename T>
	inline Structure& PriorityQueueSortedArrayList<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueSortedArrayList<T>&>(other));
	}

	template<typename T>
	inline void PriorityQueueSortedArrayList<T>::push(int priority, const T& data)
	{
		//Done 06: PriorityQueueSortedArrayList push
		int i = 0;
		while (i < this->list_->size() && this->list_->at(i)->getPriority() > priority)
		{
			i++;
		}
		PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
		this->list_->insert(item, i);
	}

	template<typename T>
	inline int PriorityQueueSortedArrayList<T>::indexOfPeek()
	{
		//Done 06: PriorityQueueSortedArrayList indexOfPeek
		return static_cast<int>(this->list_->size() - 1);
	}
}