#pragma once

#include "priority_queue_list.h"
#include "../list/linked_list.h"

namespace structures
{
	/// <summary> Prioritny front implementovany neutriednym LinkedList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueLinkedList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany neutriednym LinkedList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueLinkedList(PriorityQueueLinkedList<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho neutriednym LinkedList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;
	};

	template<typename T>
	PriorityQueueLinkedList<T>::PriorityQueueLinkedList() :
		PriorityQueueList<T>(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueLinkedList<T>::PriorityQueueLinkedList(PriorityQueueLinkedList<T>& other) :
		PriorityQueueLinkedList()
		/*PriorityQueueList<T>()
			new LinkedList<PriorityQueueItem<T>*>(
				dynamic_cast<LinkedList<PriorityQueueItem<T>*>&>(*other.list_))) */ // Nie dobre spraveny konstruktor
	{
		//Done 06: PriorityQueueLinkedList PriorityQueueLinkedList
		this->assign(other);
	}

	template<typename T>
	inline Structure& PriorityQueueLinkedList<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueLinkedList<T>&>(other));
	}

	template<typename T>
	inline void PriorityQueueLinkedList<T>::push(int priority, const T& data)
	{
		//Done 06: PriorityQueueLinkedList push
		PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
		PriorityQueueList<T>::list_->add(item);
	}
}