#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany haldou. Implementujucim typom haldy je struktura ArrayList. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class Heap : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Heap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Halda, z ktorej sa prevezmu vlastnosti. </param>
		Heap(Heap<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do haldy. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z haldy. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je halda prazdna. </exception>
		T pop() override;

	protected:
		/// <summary> Vrati index v ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je ArrayList prazdny. </exception>
		int indexOfPeek() override;

	private:
		/// <summary> Vrati index v ArrayList-e, na ktorom by sa mal nachadzat otec daneho prvku. </summary>
		/// <param name = "index"> Index prvku, ktoreho otca chceme vratit. </param>
		/// <returns> Index, na ktorom ba sa mal nachadzat otec prvku. </returns>
		int getParentIndex(int index);

		/// <summary> Vrati index v ArrayList-e, na ktorom by mal mat dany prvok syna s najvacsou prioritou. </summary>
		/// <param name = "index"> Index prvku, ktoreho syna chceme vratit. </param>
		/// <returns> Index, na ktorom by sa mal nachadzat syn prvku. </returns>
		int getGreaterSonIndex(int index);
	};

	template<typename T>
	Heap<T>::Heap() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	Heap<T>::Heap(Heap<T>& other) :
		Heap<T>()
	{
		assign(other)
	}

	template<typename T>
	inline Structure& Heap<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueList<T>&>(other));
	}

	template<typename T>
	void Heap<T>::push(int priority, const T& data)
	{
		//Done 06: Heap push
		PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
		int itemIndex = static_cast<int>(this->size());
		this->list_->add(item);
		int parentIndex = this->getParentIndex(itemIndex);
		while (itemIndex > 0 && this->list_->at(itemIndex)->getPriority() < this->list_->at(parentIndex)->getPriority())
		{
			Utils::swap(this->list_->at(itemIndex), this->list_->at(parentIndex));
			itemIndex = parentIndex;
			parentIndex = this->getParentIndex(itemIndex);
		}
	}

	template<typename T>
	T Heap<T>::pop()
	{
		//Done 06: Heap pop
		int endIndex = static_cast<int>(this->size()) - 1;
		int itemIndex = this->indexOfPeek();
		Utils::swap(this->list_->at(endIndex), this->list_->at(itemIndex));
		PriorityQueueItem<T>* item = this->list_->removeAt(endIndex);
		T data = item->accessData();
		delete item;
		int sonIndex = this->getGreaterSonIndex(itemIndex);
		while (sonIndex < this->size() &&
			this->list_->at(sonIndex)->getPriority() < this->list_->at(itemIndex)->getPriority())
		{
			Utils::swap(this->list_->at(sonIndex), this->list_->at(itemIndex));
			itemIndex = sonIndex;
			sonIndex = this->getGreaterSonIndex(itemIndex);
		}
		return data;
	}

	template<typename T>
	inline int Heap<T>::getParentIndex(int index)
	{
		//Done 06: Heap getParentIndex
		return (index - 1) / 2;

	}

	template<typename T>
	inline int Heap<T>::getGreaterSonIndex(int index)
	{
		//Done 06: Heap getGreaterSonIndex
		int sonIndex = (index + 1) * 2;
		if (sonIndex >= this->size() ||
			this->list_->at(sonIndex)->getPriority() > this->list_->at(sonIndex - 1)->getPriority())
		{
			sonIndex--;
		}
		return sonIndex;
	}

	template<typename T>
	inline int Heap<T>::indexOfPeek()
	{
		//Done 06: Heap indexOfPeek
		if (this->size() == 0)
		{
			throw std::logic_error("Heap<T>::indexOfPeek: Heap is empty");
		}
		return 0;
	}
}