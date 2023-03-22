#pragma once

#include "queue.h"
#include "../array/array.h"

#include <stdexcept>

namespace structures
{
	/// <summary> Implicitny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class ImplicitQueue : public Queue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ImplicitQueue();

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "capacity"> Maximalna velkost frontu. </param>
		ImplicitQueue(size_t capacity);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Implicitny front, z ktoreho sa prevezmu vlastnosti. </param>
		ImplicitQueue(ImplicitQueue<T>& other);

		/// <summary> Destruktor. </summary>
		~ImplicitQueue();

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
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front plny. </exception>
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
		/// <summary> Pole, pomocou ktoreho je implementovany front. </summary>
		Array<T>* array_;

		/// <summary> Index prveho prvku vo fronte. </summary>
		int startIndex_;

		/// <summary> Pocet prvkov vo fronte. </summary>
		size_t size_;
	};

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue() :
		ImplicitQueue(10)
	{
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(size_t capacity) :
		Queue<T>(),
		array_(new Array<T>(capacity)),
		startIndex_(0),
		size_(0)
	{
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(ImplicitQueue<T>& other) :
		Queue<T>(other),
		array_(new Array<T>(*other.array_)),
		startIndex_(other.startIndex_),
		size_(other.size_)
	{
	}

	template<typename T>
	ImplicitQueue<T>::~ImplicitQueue()
	{
		//Done 05: ImplicitQueue ~ImplicitQueue
		delete this->array_;
		this->array_ = nullptr;
		this->size_ = 0;
		this->startIndex_ = 0;
	}

	template<typename T>
	inline Structure& ImplicitQueue<T>::assign(Structure& other)
	{ 
		//Done 05: ImplicitQueue assign
		if (this != &other)
		{
			ImplicitQueue<T>& otherQ = dynamic_cast<ImplicitQueue<T>&>(other);
			if (this->array_->size() == otherQ.array_->size())
			{
				this->array_->assign(*otherQ.array_);
			}
			else
			{
				delete this->array_;
				this->array_ = new Array<T>(*otherQ.array_);
			}
			this->size_ = otherQ.size_;
			this->startIndex_ = otherQ.startIndex_;
		}
		return *this;
	}

	template<typename T>
	size_t ImplicitQueue<T>::size()
	{
		//Done 05: ImplicitQueue size
		return this->size_;
	}

	template<typename T>
	inline bool ImplicitQueue<T>::equals(Structure& other)
	{
		//Done 05: ImplicitQueue equals
		if (this == &other)
		{
			return true;
		}
		ImplicitQueue<T>* otherQ = dynamic_cast<ImplicitQueue<T>*>(&other);
		if (otherQ == nullptr || this->size_ != otherQ->size_)
		{
			return false;
		}
		for (int i = 0; i < this->size_; i++)
		{
			int index = (this->startIndex_ + i) % this->array_->size();
			int otherIndex = (otherQ->startIndex_ + i) % otherQ->array_->size();
			if (this->array_->at(index) != otherQ->array_->at(otherIndex))
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline void ImplicitQueue<T>::clear()
	{
		//Done 05: ImplicitQueue clear
		this->startIndex_ = 0;
		this->size_ = 0;
	}

	template<typename T>
	inline void ImplicitQueue<T>::push(const T& data)
	{
		//Done 05: ImplicitQueue push
		if (this->size_ >= this->array_->size())
		{
			throw std::out_of_range("ImplicitQueue<T>::push: Queue is full");
		}
		this->array_->at(static_cast<int>((this->startIndex_ + this->size_) % this->array_->size())) = data;
		this->size_++;
	}

	template<typename T>
	inline T ImplicitQueue<T>::pop()
	{
		//Done 05: ImplicitQueue pop
		if (this->size_ <= 0)
		{
			throw std::out_of_range("ImplicitQueue<T>::pop: Queue is empty");
		}
		T data = this->array_->at(this->startIndex_);
		this->startIndex_ = (this->startIndex_ + 1) % this->array_->size();
		this->size_--;
		return data;
	}

	template<typename T>
	inline T& ImplicitQueue<T>::peek()
	{
		//Done 05: ImplicitQueue peek
		if (this->size_ <= 0)
		{
			throw std::out_of_range("ImplicitQueue<T>::peek: Queue is empty");
		}
		return this->array_->at(this->startIndex_);
	}
}