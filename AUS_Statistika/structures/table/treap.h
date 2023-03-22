#pragma once

#include "binary_search_tree.h"
#include <random>

namespace structures
{
	/// <summary> Prvok treap-u. </summary>
	/// <typeparam name = "K"> Kluc prvku. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template <typename K, typename T>
	class TreapItem : public TableItem<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		/// <param name = "priority"> Priorita. </param>
		TreapItem(K key, T data, int priority);

		/// <summary> Getter atributu priorita. </summary>
		/// <returns> Priorita. </returns>
		int getPriority();

		/// <summary> Nastavi minimalnu prioritu. </summary>
		void minimizePriority();
	private:
		/// <summary> Kluc prvku. </summary>
		int priority_;
	};

	/// <summary> Treap. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Treap : public BinarySearchTree<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Treap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Treap, z ktoreho sa prevezmu vlastnosti. </param>
		Treap(Treap<K, T>& other);

		/// <summary> Destruktor. </summary>
		~Treap();

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
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

	private:
		/// <summary> Generator nahodnej priority. </summary>
		std::default_random_engine* generator_;

		/// <summary> Skontroluje, ci je haldove usporiadanie prvkov okolo vrcholu OK. </summary>
		/// <param name = "node"> Vrchol, ktoreho susedstvo sa kontroluje. </param>
		/// <returns> true, ak je haldove usporiadanie prvkov okolo vrcholu OK, false inak. </returns>
		bool isHeapOK(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Vytiahne prioritu z vrcholu stromu. </summary>
		/// <param name = "node"> Vrchol, ktoreho priorita ma byt zistena. </param>
		/// <returns> Priorita vrcholu. Ak je vrchol nullptr, vrati -1. </returns>
		int extractPriority(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi lavu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks>
		/// Musi byt pravym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane lavym synom tohto vrchola.
		/// Potencialny lavy syn tohto vrchola sa stane pravym synom otca.
		/// </remarks>
		void rotateLeftOverParent(BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi pravu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks>
		/// Musi byt lavym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane pravym synom tohto vrchola.
		/// Potencialny pravy syn tohto vrchola sa stane lavym synom otca.
		/// </remarks>
		void rotateRightOverParent(BinarySearchTree<K, T>::BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline TreapItem<K, T>::TreapItem(K key, T data, int priority):
		TableItem<K, T>(key, data),
		priority_(priority)
	{
	}

	template<typename K, typename T>
	inline int TreapItem<K, T>::getPriority()
	{
		return priority_;
	}

	template<typename K, typename T>
	inline void TreapItem<K, T>::minimizePriority()
	{
		priority_ = INT_MAX;
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap() :
		BinarySearchTree<K, T>(),
		generator_(new std::default_random_engine())
	{
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap(Treap<K, T>& other) :
		Treap()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline Treap<K, T>::~Treap()
	{
		//Done 10: Treap ~Treap
		delete this->generator_;
		this->generator_ = nullptr;
	}

	template<typename K, typename T>
	inline Structure& Treap<K, T>::assign(Structure& other)
	{
		//Done 10: Treap assign
		if (this != &other)
		{
			Treap<K, T>& otherTreap = dynamic_cast<Treap<K, T>&>(other);
			BinarySearchTree<K, T>::assign(otherTreap);
			delete this->generator_;
			this->generator_ = new std::default_random_engine(*otherTreap.generator_);
		}
		return *this;
	}

	template<typename K, typename T>
	inline bool Treap<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<Treap<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline void Treap<K, T>::insert(const K& key, const T& data)
	{
		//Done 10: Treap insert
		int priority = (*this->generator_)();
		TreapItem<K, T>* item = new TreapItem<K, T>(key, data, priority);
		BinarySearchTree<K,T>::BSTTreeNode* node = new BinarySearchTree<K, T>::BSTTreeNode(item);
		if (!this->tryToInsertNode(node))
		{
			delete node;
			delete item;
			throw std::logic_error("Treap<K, T>::insert: Key is already present in Treap.");
		}
		while(!this->isHeapOK(node))
		{
			if (node->isLeftSon())
			{
				this->rotateRightOverParent(node);
			}
			else
			{
				this->rotateLeftOverParent(node);
			}
		}
	}

	template<typename K, typename T>
	inline T Treap<K, T>::remove(const K& key)
	{
		//Done 10: Treap remove
		bool found;
		BinarySearchTree<K, T>::BSTTreeNode* node = this->findBSTNode(key, found);
		if (!found)
		{
			throw std::logic_error("Treap<K, T>::remove: No such key in Treap");
		}
		dynamic_cast<TreapItem<K,T>*>(node->accessData())->minimizePriority();
		while (!this->isHeapOK(node))
		{
			BinarySearchTree<K, T>::BSTTreeNode* leftSon = node->getLeftSon();
			BinarySearchTree<K, T>::BSTTreeNode* rightSon = node->getRightSon();
			if (leftSon != nullptr && rightSon != nullptr)
			{
				if (dynamic_cast<TreapItem<K, T>*>(leftSon->accessData())->getPriority() < dynamic_cast<TreapItem<K, T>*>(rightSon->accessData())->getPriority())
				{
					this->rotateRightOverParent(leftSon);
				}
				else
				{
					this->rotateLeftOverParent(rightSon);
				}
			}
			else if (leftSon != nullptr)
			{
				this->rotateRightOverParent(leftSon);
			}
			else
			{
				this->rotateLeftOverParent(rightSon);
			}
		}
		this->extractNode(node);
		T data = node->accessData()->accessData();
		delete node->accessData();
		delete node;
		this->size_--;
		return data;
	}

	template<typename K, typename T>
	inline bool Treap<K, T>::isHeapOK(BinarySearchTree<K, T>::BSTTreeNode* node)
	{
		//Done 10: Treap isHeapOK
		bool result = true; 
		if (node != nullptr)
		{
			if ((node->getParent() != nullptr && dynamic_cast<TreapItem<K, T>*>(node->getParent()->accessData())->getPriority() > dynamic_cast<TreapItem<K, T>*>(node->accessData())->getPriority()) ||
				(node->hasLeftSon() && dynamic_cast<TreapItem<K, T>*>(node->getLeftSon()->accessData())->getPriority() < dynamic_cast<TreapItem<K, T>*>(node->accessData())->getPriority()) ||
				(node->hasRightSon() && dynamic_cast<TreapItem<K, T>*>(node->getRightSon()->accessData())->getPriority() < dynamic_cast<TreapItem<K, T>*>(node->accessData())->getPriority()))
			{
				result = false;
			}
		}
		return result;
	}

	template<typename K, typename T>
	inline int Treap<K, T>::extractPriority(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		//Done 10: Treap extractPriority
		return node == nullptr ? -1 : node->accessData()->getPriority();
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateLeftOverParent(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		//Done 10: Treap rotateLeftOverParent
		if (node->isRightSon())
		{
			BinarySearchTree<K, T>::BSTTreeNode* leftSon = node->getLeftSon();
			node->setLeftSon(nullptr);
			BinarySearchTree<K, T>::BSTTreeNode* parent = node->getParent();
			BinarySearchTree<K, T>::BSTTreeNode* grandParent = parent->getParent();
			parent->setRightSon(nullptr);
			if (grandParent != nullptr)
			{
				if (parent->isLeftSon())
				{
					grandParent->setLeftSon(node);
				}
				else
				{
					grandParent->setRightSon(node);
				}
			}
			parent->setRightSon(leftSon);
			node->setLeftSon(parent);
			if (parent == this->binaryTree_->getRoot())
			{
				this->binaryTree_->replaceRoot(node);
			}
		}
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateRightOverParent(BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		//Done 10: Treap rotateRightOverParent
		if (node->isLeftSon())
		{
			BinarySearchTree<K, T>::BSTTreeNode* rightSon = node->getRightSon();
			node->setRightSon(nullptr);
			BinarySearchTree<K, T>::BSTTreeNode* parent = node->getParent();
			BinarySearchTree<K, T>::BSTTreeNode* grandParent = parent->getParent();
			parent->setLeftSon(nullptr);
			if (grandParent != nullptr)
			{
				if (parent->isLeftSon())
				{
					grandParent->setLeftSon(node);
				}
				else
				{
					grandParent->setRightSon(node);
				}
			}
			parent->setLeftSon(rightSon);
			node->setRightSon(parent);
			if (parent == this->binaryTree_->getRoot())
			{
				this->binaryTree_->replaceRoot(node);
			}
		}
	}
}