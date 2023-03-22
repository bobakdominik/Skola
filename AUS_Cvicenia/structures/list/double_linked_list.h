#pragma once

#include "list.h"
#include "linked_list.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include "../utils.h"

namespace structures
{

    /// <summary> Prvok obojstranne zretazeneho zoznamu. </summary>
   /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    template<typename T>
    class DoubleLinkedListItem : public LinkedListItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        DoubleLinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok obojstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        DoubleLinkedListItem<T>* getPrevious();

        /// <summary> Setter predchadzajuceho prvku obojstranne zretazeneho zoznamu. </summary>
        /// <param name´= "previous"> Novy predchadzajuci prvok obojstranne zretazeneho zoznamu. </param>
        void setPrevious(DoubleLinkedListItem<T>* previous);

    private:
        /// <summary> predchadzajuci prvok obojstranne zretazeneho zoznamu. </summary>
        DoubleLinkedListItem<T>* prev_;
    };

	// implementacne tipy: 
	//  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
	//    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
	//    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
	//    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
	//    zvysok nechat na predka.
	//  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
	//    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
	//  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
	//    takze ich nebudete musiet implementovat.
	
    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoubleLinkedList : public LinkedList<T> 
	{
    public:
        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        //size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        //Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        //T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        //bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        //int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        //void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        //Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        //Iterator<T>* getEndIterator() override;
    private:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </summary>
        /// <returns> Prvok zoznamu na danom indexe. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        LinkedListItem<T>* getItemAtIndex(int index) override;
	};

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList() :
        LinkedList()
    {
        //Done Zadanie 2: DoubleLinkedList DoubleLinkedList
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other)
    {
        //Done Zadanie 2: DoubleLinkedList DoubleLinkedList
        this->assign(other);
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        //Done Zadanie 2: DoubleLinkedList ~DoubleLinkedList
        this->clear();
    }

    //template<typename T>
    //inline size_t DoubleLinkedList<T>::size()
    //{
    //    //Done Zadanie 2: DoubleLinkedList size
    //    return LinkedList::size();
    //}

    //template<typename T>
    //inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    //{
    //    //Done Zadanie 2: DoubleLinkedList assign
    //    throw std::runtime_error("DoubleLinkedList<T>::assign: Not implemented yet.");
    //}

    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        //Done Zadanie 2: DoubleLinkedList equals
        DoubleLinkedList<T>* otherDLL = dynamic_cast<DoubleLinkedList<T>*>(&other);
        if (otherDLL == nullptr || this->size_ != otherDLL->size_)
        {
            return false;
        }
        return LinkedList<T>::equals(other);
    }

    //template<typename T>
    //inline T& DoubleLinkedList<T>::at(int index)
    //{
    //    //Done Zadanie 2: DoubleLinkedList at
    //    throw std::runtime_error("DoubleLinkedList<T>::at: Not implemented yet.");
    //}

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        //Done Zadanie 2: DoubleLinkedList add
        DoubleLinkedListItem<T>* item = new DoubleLinkedListItem<T>(data);
        if (this->first_ == nullptr)
        {
            this->first_ = item;
        }
        else
        {
            this->last_->setNext(item);
            item->setPrevious(dynamic_cast<DoubleLinkedListItem<T>*>(this->last_));
        }
        this->last_ = item;
        this->size_++;
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {
        //Done Zadanie 2: DoubleLinkedList insert
        if (index < 0 || index > this->size_)
        {
            throw std::out_of_range("DoubleLinkedList<T>::insert: Invalid index");
        }
        if (index == this->size_)
        {
            this->add(data);
        }
        else
        {
            DoubleLinkedListItem<T>* item = new DoubleLinkedListItem<T>(data);
            if (index == 0)
            {
                item->setNext(this->first_);
                dynamic_cast<DoubleLinkedListItem<T>*>(this->first_)->setPrevious(item);
                this->first_ = item;
            }
            else
            {
                DoubleLinkedListItem<T>* oldItem = dynamic_cast<DoubleLinkedListItem<T>*>(this->getItemAtIndex(index));
                oldItem->getPrevious()->setNext(item);
                item->setPrevious(oldItem->getPrevious());
                item->setNext(oldItem);
                oldItem->setPrevious(item);
            }
            this->size_++;
        }
    }

    //template<typename T>
    //inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    //{
    //    //Done Zadanie 2: DoubleLinkedList tryRemove
    //    throw std::runtime_error("DoubleLinkedList<T>::tryRemove: Not implemented yet.");
    //}

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {
        //Done Zadanie 2: DoubleLinkedList removeAt
        if (index < 0 || index >= this->size_)
        {
            throw std::out_of_range("DoubleLinkedList<T>::removeAt: Invalid index");
        }
        DoubleLinkedListItem<T>* item = nullptr;
        if (index == 0)
        {
            item = dynamic_cast<DoubleLinkedListItem<T>*>(this->first_);
            this->first_ = item->getNext();
            if (this->first_ != nullptr)
            {
                dynamic_cast<DoubleLinkedListItem<T>*>(this->first_)->setPrevious(nullptr);
            }
            if (item == this->last_)
            {
                this->last_ = nullptr;
            }
        }
        else if (index == this->size() - 1)
        {
            item = dynamic_cast<DoubleLinkedListItem<T>*>(this->last_);
            this->last_ = item->getPrevious();
            this->last_->setNext(nullptr);
        }
        else
        {
            item = dynamic_cast<DoubleLinkedListItem<T>*>(this->getItemAtIndex(index));
            item->getPrevious()->setNext(item->getNext());
            dynamic_cast<DoubleLinkedListItem<T>*>(item->getNext())->setPrevious(item->getPrevious());
        }
        T data = item->accessData();
        delete item;
        this->size_--;
        return data;
    }

    template<typename T>
    inline LinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
    {
        //Done Zadanie 2: DoubleLinkedList getItemAtIndex
        // Privatna metoda, nemusim vyhadzovat vynimku a kontrolovat index, postara sa o to public metoda
        if (index == this->size_ - 1)
        {
            return this->last_;
        }
        int mid = static_cast<int>(this->size() - 1) / 2;
        DoubleLinkedListItem<T>* item = nullptr;
        if (index > mid)
        {
            item = dynamic_cast<DoubleLinkedListItem<T>*>(this->last_);
            for (int i = static_cast<int>(this->size()) - 1; i > index; i--)
            {
                item = item->getPrevious();
            }
        }
        else
        {
            item = dynamic_cast<DoubleLinkedListItem<T>*>(this->first_);
            for (int i = 0; i < index; i++)
            {
                item = dynamic_cast<DoubleLinkedListItem<T>*>(item->getNext());
            }
        }
        return item;
    }

    //template<typename T>
    //inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    //{
    //    //Done Zadanie 2: DoubleLinkedList getIndexOf
    //    throw std::runtime_error("DoubleLinkedList<T>::getIndexOf: Not implemented yet.");
    //}

    //template<typename T>
    //inline void DoubleLinkedList<T>::clear()
    //{
    //    //Done Zadanie 2: DoubleLinkedList clear
    //    throw std::runtime_error("DoubleLinkedList<T>::clear: Not implemented yet.");
    //}

    //template<typename T>
    //inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    //{
    //    //Done Zadanie 2: DoubleLinkedList getBeginIterator
    //    throw std::runtime_error("DoubleLinkedList<T>::getBeginIterator: Not implemented yet.");
    //}

    //template<typename T>
    //inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    //{
    //    //Done Zadanie 2: DoubleLinkedList getEndIterator
    //    throw std::runtime_error("DoubleLinkedList<T>::getEndIterator: Not implemented yet.");
    //}

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data) :
        LinkedListItem<T>(data),
        prev_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other):
        LinkedListItem<T>(other),
        prev_(other.prev_)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
    {
        this->prev_ = nullptr;
        LinkedListItem<T>::~LinkedListItem();
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrevious()
    {
        return this->prev_;
    }
    template<typename T>
    inline void DoubleLinkedListItem<T>::setPrevious(DoubleLinkedListItem<T>* previous)
    {
        this->prev_ = previous;
    }
}