#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include "../utils.h"

namespace structures
{
    /// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    template<typename T>
    class LinkedListItem : public DataItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        LinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        LinkedListItem(LinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~LinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        LinkedListItem<T>* getNext();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setNext(LinkedListItem<T>* next);

    private:
        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        LinkedListItem<T>* next_;
    };

    /// <summary> Jednostranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
    template<typename T>
    class LinkedList : public List<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        LinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        LinkedList(LinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~LinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

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
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;

    protected:
        /// <summary> Pocet prvkov v zozname. </summary>
        size_t size_;
        /// <summary> Prvy prvok zoznamu. </summary>
        LinkedListItem<T>* first_;
        /// <summary> Posledny prvok zoznamu. </summary>
        LinkedListItem<T>* last_;

    protected:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </summary>
        /// <returns> Prvok zoznamu na danom indexe. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        virtual LinkedListItem<T>* getItemAtIndex(int index);

    private:
        /// <summary> Iterator pre LinkedList. </summary>
        class LinkedListIterator : public Iterator<T>
        {
        public:
            /// <summary> Konstruktor. </summary>
            /// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
            LinkedListIterator(LinkedListItem<T>* position);

            /// <summary> Destruktor. </summary>
            ~LinkedListIterator();

            /// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> Vrati seba po priradeni. </returns>
            Iterator<T>& operator= (Iterator<T>& other) override;

            /// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
            bool operator!=(Iterator<T>& other) override;

            /// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
            /// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
            T operator*() override;

            /// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
            /// <returns> Iterator na dalsi prvok v strukture. </returns>
            /// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
            Iterator<T>& operator++() override;

        private:
            /// <summary> Aktualna pozicia v zozname. </summary>
            LinkedListItem<T>* position_;
        };
    };

    template<typename T>
    inline LinkedListItem<T>::LinkedListItem(T data) :
        DataItem<T>(data),
        next_(nullptr)
    {
    }

    template<typename T>
    inline LinkedListItem<T>::LinkedListItem(LinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_)
    {
    }

    template<typename T>
    inline LinkedListItem<T>::~LinkedListItem()
    {
        next_ = nullptr;
    }

    template<typename T>
    inline LinkedListItem<T>* LinkedListItem<T>::getNext()
    {
        return next_;
    }

    template<typename T>
    inline void LinkedListItem<T>::setNext(LinkedListItem<T>* next)
    {
        next_ = next;
    }

    template<typename T>
    inline LinkedList<T>::LinkedList() :
        size_(0),
        first_(nullptr),
        last_(nullptr)
    {
    }

    template<typename T>
    inline LinkedList<T>::LinkedList(LinkedList<T>& other)
    {
        //Done 04: LinkedList LinkedList
        this->assign(other);
    }

    template<typename T>
    inline LinkedList<T>::~LinkedList()
    {
        //Done 04: LinkedList ~LinkedList
        this->clear();
    }

    template<typename T>
    inline size_t LinkedList<T>::size()
    {
        return size_;
    }

    template<typename T>
    inline Structure& LinkedList<T>::assign(Structure& other)
    {
        //Done 04: LinkedList assign
        LinkedList<T>& otherLL = dynamic_cast<LinkedList<T>&>(other);
        if (this != &other)
        {
            this->clear();
            for (T data : otherLL)
            {
                this->add(data);
            }
        }
        return *this;
    }

    template<typename T>
    inline bool LinkedList<T>::equals(Structure& other)
    {
        //Done 04: LinkedList equals
        LinkedList<T>* otherLL = dynamic_cast<LinkedList<T>*>(&other);
        if (otherLL == nullptr || this->size_ != otherLL->size_)
        {
            return false;
        }
        LinkedListItem<T>* currThis = this->first_;
        LinkedListItem<T>* currOther = otherLL->first_;
        while (currThis != nullptr)
        {
            if (currThis->accessData() != currOther->accessData())
            {
                return false;
            }
            currOther = currOther->getNext();
            currThis = currThis->getNext();
        }
        return true;
    }

    template<typename T>
    inline T& LinkedList<T>::at(int index)
    {
        //Done 04: LinkedList at
        if (index < 0 || index >= this->size_)
        {
            throw std::out_of_range("LinkedList<T>::at: Invalid index");
        }
        return this->getItemAtIndex(index)->accessData();
    }

    template<typename T>
    inline void LinkedList<T>::add(const T& data)
    {
        //Done 04: LinkedList add
        LinkedListItem<T>* item = new LinkedListItem<T>(data);
        if (this->first_ == nullptr)
        {
            this->first_ = item;
        }
        else
        {
            this->last_->setNext(item);
        }
        this->last_ = item;
        this->size_++;
    }

    template<typename T>
    inline void LinkedList<T>::insert(const T& data, int index)
    {
        //Done 04: LinkedList insert
        if (index < 0 || index > this->size_)
        {
            throw std::out_of_range("LinkedList<T>::insert: Invalid index");
        }
        if (index == this->size_)
        {
            this->add(data);
        }
        else
        {
            LinkedListItem<T>* item = new LinkedListItem<T>(data);
            if (index == 0)
            {
                item->setNext(this->first_);
                this->first_ = item;
            }
            else
            {
                LinkedListItem<T>* prevItem = this->getItemAtIndex(index - 1);
                item->setNext(prevItem->getNext());
                prevItem->setNext(item);
            }
            this->size_++;
        }
    }

    template<typename T>
    inline bool LinkedList<T>::tryRemove(const T& data)
    {
        //Done 04: LinkedList tryRemove
        int index = this->getIndexOf(data);
        if (index < 0)
        {
            return false;
        }
        else
        {
            this->removeAt(index);
            return true;
        }
    }

    template<typename T>
    inline T LinkedList<T>::removeAt(int index)
    {
        //Done 04: LinkedList removeAt
        if (index < 0 || index >= this->size_)
        {
            throw std::out_of_range("LinkedList<T>::removeAt: Invalid index");
        }
        LinkedListItem<T>* item = nullptr;
        if (index == 0)
        {
            item = this->first_;
            this->first_ = item->getNext();
            if (item == this->last_)
            {
                this->last_ = nullptr;
            }
        }
        else
        {
            LinkedListItem<T>* prevItem = this->getItemAtIndex(index - 1);
            item = prevItem->getNext();
            prevItem->setNext(item->getNext());
            if (item == this->last_)
            {
                this->last_ = prevItem;
            }
        }
        T data = item->accessData();
        delete item;
        this->size_--;
        return data;
    }

    template<typename T>
    inline int LinkedList<T>::getIndexOf(const T& data)
    {
        //Done 04: LinkedList getIndexOf
        LinkedListItem<T>* item = this->first_;
        int i= 0;
        while (item != nullptr)
        {
            if (item->accessData() == data)
            {
                return i;
            }
            i++;
            item = item->getNext();
        }
        return -1;
    }

    template<typename T>
    inline void LinkedList<T>::clear()
    {
        //Done 04: LinkedList clear
        LinkedListItem<T>* item = this->first_;
        while (item != nullptr)
        {
            this->first_ = item->getNext();
            delete item;
            item = this->first_;
        }
        this->size_ = 0;
        this->last_ = nullptr;
    }

    template<typename T>
    inline Iterator<T>* LinkedList<T>::getBeginIterator()
    {
        return new LinkedListIterator(first_);
    }

    template<typename T>
    inline Iterator<T>* LinkedList<T>::getEndIterator()
    {
        return new LinkedListIterator(nullptr);
    }

    template<typename T>
    inline LinkedListItem<T>* LinkedList<T>::getItemAtIndex(int index)
    {
        //Done 04: LinkedList getItemAtIndex
        // Privatna metoda, nemusim vyhadzovat vynimku a kontrolovat index, postara sa o to public metoda
        if (index == this->size_ - 1)
        {
            return this->last_;
        }
        LinkedListItem<T>* item = this->first_;
        for (int i = 0; i < index; i++)
        {
            item = item->getNext();
        }
        return item;
    }

    template<typename T>
    inline LinkedList<T>::LinkedListIterator::LinkedListIterator(LinkedListItem<T>* position) :
        position_(position)
    {
    }

    template<typename T>
    inline LinkedList<T>::LinkedListIterator::~LinkedListIterator()
    {
        this->position_ = nullptr;
    }

    template<typename T>
    inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator=(Iterator<T>& other)
    {
        //Done 04: LinkedList operator=
        if (this != &other)
        {
            LinkedListIterator& otherIt = dynamic_cast<LinkedListIterator&>(other);
            this->position_ = otherIt.position_;
        }
        return *this;
    }

    template<typename T>
    inline bool LinkedList<T>::LinkedListIterator::operator!=(Iterator<T>& other)
    {
        //Done 04: LinkedList
        LinkedListIterator* otherIt = dynamic_cast<LinkedListIterator*>(&other);
        return otherIt == nullptr || this->position_ != otherIt->position_;
    }

    template<typename T>
    inline T LinkedList<T>::LinkedListIterator::operator*()
    {
        //Done 04: LinkedList operator*
        return this->position_->accessData();
    }

    template<typename T>
    inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator++()
    {
        //Done 04: LinkedList operator++
        this->position_ = this->position_->getNext();
        return *this;
    }

}