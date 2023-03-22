#pragma once

#include "queue.h"
#include "../list/linked_list.h"

namespace structures
{
	/// <summary> Explicitny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class ExplicitQueue : public Queue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ExplicitQueue();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Explicitny front, z ktoreho sa prevezmu vlastnosti. </param>
		ExplicitQueue(ExplicitQueue<T>& other);

		/// <summary> Destruktor. </summary>
		~ExplicitQueue();

		/// <summary> Vrati pocet prvkov vo fronte. </summary>
		/// <returns> Pocet prvkov vo fronte. </returns>
		size_t size() override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vymaze front. </summary>
		void clear() override;

		/// <summary> Prida prvok do frontu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void push(const T& data) override;

		/// <summary> Odstrani prvok z frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
		T pop() override;

		/// <summary> Vrati prvok na zaciatku frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>
		T& peek() override;

	protected:
		/// <summary> Zoznam, pomocou ktoreho je implementovany front. </summary>
		LinkedList<T>* list_;
	};

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue() :
		Queue<T>(),
		list_(new LinkedList<T>())
	{
	}

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue(ExplicitQueue<T>& other) :
		ExplicitQueue()
	{
		assign(other);
	}

	template<typename T>
	ExplicitQueue<T>::~ExplicitQueue()
	{
		//Done 05: ExplicitQueue ~ExplicitQueue
		this->list_->clear();
		delete this->list_;
		this->list_ = nullptr;
	}

	template<typename T>
	inline Structure& ExplicitQueue<T>::assign(Structure& other)
	{
		//Done 05: ExplicitQueue assign
		if (this != &other)
		{
			ExplicitQueue<T>& otherQ = dynamic_cast<ExplicitQueue<T>&>(other);
			this->list_->assign(*otherQ.list_);
		}
		return *this;
	}

	template<typename T>
	inline bool ExplicitQueue<T>::equals(Structure& other)
	{
		//Done 05: ExplicitQueue equals
		if (this == &other)
		{
			return true;
		}
		ExplicitQueue<T>* otherQ = dynamic_cast<ExplicitQueue<T>*>(&other);
		return otherQ != nullptr && this->list_->equals(*otherQ->list_);
	}

	template<typename T>
	size_t ExplicitQueue<T>::size()
	{
		//Done 05: ExplicitQueue size
		return this->list_->size();
	}

	template<typename T>
	inline void ExplicitQueue<T>::clear()
	{
		//Done 05: ExplicitQueue clear
		this->list_->clear();
	}

	template<typename T>
	inline void ExplicitQueue<T>::push(const T& data)
	{
		//Done 05: ExplicitQueue push
		this->list_->add(data);
	}

	template<typename T>
	inline T ExplicitQueue<T>::pop()
	{
		//Done 05: ExplicitQueue pop
		return this->list_->removeAt(0);
	}

	template<typename T>
	inline T& ExplicitQueue<T>::peek()
	{
		//Done 05: ExplicitQueue peek
		return this->list_->at(0);
	}
}