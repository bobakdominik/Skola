#pragma once

#include "priority_queue.h"
#include "../list/list.h"
#include <stdexcept>
#include "../utils.h"

namespace structures
{
    /// <summary> Spolocny predok pre vsetky prioritne fronty, ktorych implementujucim typom je zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
    template<typename T>
    class PriorityQueueList : public PriorityQueue<T>
    {
    public:
        /// <summary> Destruktor. </summary>
        ~PriorityQueueList();

        /// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom zoznamom. </summary>
        /// <returns> Pocet prvkov v prioritnom fronte implementovanom zoznamom. </returns>
        size_t size() override;

        /// <summary> Vymaze obsah prioritneho frontu implementovaneho zoznamom. </summary>
        void clear() override;

        /// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho zoznamom. </summary>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        T pop() override;

        /// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
        /// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        T& peek() override;

        /// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
        /// <returns> Priorita prvku s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        int peekPriority() override;

    protected:
        /// <summary> Konstruktor. </summary>
        /// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky prioritneho frontu. </param>
        /// <remarks>
        /// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu.
        /// Prioritny front implementovany zoznamom dealokuje tento objekt.
        /// </remarks>
        PriorityQueueList(List<PriorityQueueItem<T>*>* list);

        /// <summary> Vrati index v zozname, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
        /// <returns> Index prvku s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>
        virtual int indexOfPeek();

        /// <summary> Priradenie struktury. Pomocna metoda, ktora prebera referenciu, ktoru posle potomok. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        /// <summary>
        Structure& assignPrioQueueList(PriorityQueueList<T>& other); //assign(Structure& other)

    protected:
        /// <summary> Smernik na zoznam, do ktoreho sa ukladaju prvky prioritneho frontu. </summary>
        List<PriorityQueueItem<T>*>* list_;
    };

    template<typename T>
    inline PriorityQueueList<T>::PriorityQueueList(List<PriorityQueueItem<T>*>* list) :
        list_(list)
    {
    }

    template<typename T>
    inline PriorityQueueList<T>::~PriorityQueueList()
    {
        //Done 06: PriorityQueueList ~PriorityQueueList
        this->clear();
        delete this->list_;
        this->list_ = nullptr;
    }

    template<typename T>
    inline size_t PriorityQueueList<T>::size()
    { 
        //Done 06: PriorityQueueList size
        return this->list_->size();
    }

    template<typename T>
    inline void PriorityQueueList<T>::clear()
    {
        //Done 06: PriorityQueueList clear
        for (PriorityQueueItem<T>* item : *this->list_)
        {
            delete item;
        }
        this->list_->clear();
    }

    template<typename T>
    inline int PriorityQueueList<T>::indexOfPeek()
    { 
        //Done 06: PriorityQueueList indexOfPeek
        int index = 0;
        int priorityIndex = 0;
        int priority = this->list_->at(0)->getPriority(); 
        for (PriorityQueueItem<T>* item : *this->list_)
        {
            if (item->getPriority() < priority)
            {
                priority = item->getPriority();
                priorityIndex = index;
            }
            index++;
        }
        return priorityIndex;
    }

    template<typename T>
    inline Structure& PriorityQueueList<T>::assignPrioQueueList(PriorityQueueList<T>& other) //assign(Structure& other)
    {
        //Done 06: PriorityQueueList assign
        if (this != &other)
        {
            this->clear();
            // Normalny foreach
            /*for (PriorityQueueItem<T>* otherItem : *otherPQ.list_)
            {
                PriorityQueueItem<T>* item = new PriorityQueueItem<T>(*otherItem);
                this->list_->add(item);
            }*/

            // Foreach pomocou iteratora
            Iterator<PriorityQueueItem<T>*>* current = other.list_->getBeginIterator();
            Iterator<PriorityQueueItem<T>*>* end = other.list_->getEndIterator();
            while (*current != *end)
            {
                PriorityQueueItem<T>* otherItem = **current;
                PriorityQueueItem<T>* item = new PriorityQueueItem<T>(*otherItem);
                this->list_->add(item);
                ++(*current); // musi byt prefixove
            }
            delete current;
            delete end;
        }
        return *this;
    }

    template<typename T>
    inline T PriorityQueueList<T>::pop()
    {
        //Done 06: PriorityQueueList pop
        PriorityQueueItem<T>* item = this->list_->removeAt(this->indexOfPeek());
        T data = item->accessData();
        delete item;
        return data;
    }

    template<typename T>
    inline T& PriorityQueueList<T>::peek()
    {
        //Done 06: PriorityQueueList peek
        PriorityQueueItem<T>* item = this->list_->at(this->indexOfPeek());
        return item->accessData();
    }

    template<typename T>
    inline int PriorityQueueList<T>::peekPriority()
    {
        //Done 06: PriorityQueueList peekPriority
        PriorityQueueItem<T>* item = this->list_->at(this->indexOfPeek());
        return item->getPriority();
    }
}