#pragma once

#include "matrix.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;
	private:
		Array<Array<T>*>* array_;

		size_t rows_;
		size_t columns_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount) :
		Matrix(),
		rows_(rowCount),
		columns_(columnCount),
		array_(new Array<Array<T>*>(rowCount))
	{
		//Done Zadanie 1: InCoherentMatrix IncoherentMatrix
		for (int i = 0; i < static_cast<int>(this->rows_); i++)
		{
			this->array_->at(i) = new Array<T>(this->columns_);
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other) :
		Matrix(),
		rows_(other.rows_),
		columns_(other.columns_),
		array_(new Array<Array<T>*>(other.rows_))
	{
		//Done Zadanie 1: InCoherentMatrix IncoherentMatrix
		for (int i = 0; i < static_cast<int>(this->rows_); i++)
		{
			this->array_->at(i) = new Array<T>(*other.array_->at(i));
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		//Done Zadanie 1: InCoherentMatrix ~IncoherentMatrix
		for (size_t i = 0; i < this->rows_; i++)
		{
			delete this->array_->at(static_cast<int>(i));
			this->array_->at(static_cast<int>(i)) = nullptr;
		}
		delete this->array_;
		this->array_ = nullptr;
		this->rows_ = 0;
		this->columns_ = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		//Done Zadanie 1: InCoherentMatrix assign
		if (this != &other)
		{
			IncoherentMatrix<T>& otherIM = dynamic_cast<IncoherentMatrix<T>&>(other);
			if (this->rows_ == otherIM.rows_ &&
				this->columns_ == otherIM.columns_)
			{
				for (size_t i = 0; i < this->rows_; i++)
				{
					Array<T>* testedArray = dynamic_cast<Array<T>*>(otherIM.array_->at(static_cast<int>(i)));
					this->array_->at(static_cast<int>(i))->assign(*testedArray);
				}
			}
			else
			{
				std::logic_error("IncoherentMatrix<T>::assign: Sizes of matrixes are different");
			}
		}
		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		//Done Zadanie 1: InCoherentMatrix equals
		IncoherentMatrix<T>* otherIM = dynamic_cast<IncoherentMatrix<T>*>(&other);
		if (otherIM == nullptr || otherIM->rows_ != this->rows_ || otherIM->columns_ != this->columns_)
		{
			return false;
		}
		for (size_t i = 0; i < this->rows_; i++)
		{
			Array<T>* testedArray = dynamic_cast<Array<T>*>(otherIM->array_->at(static_cast<int>(i)));
			if (!this->array_->at(static_cast<int>(i))->equals(*testedArray))
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		//Done Zadanie 1: InCoherentMatrix size
		return this->rows_ * this->columns_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		//Done Zadanie 1: InCoherentMatrix getRowCount
		return this->rows_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		//Done Zadanie 1: InCoherentMatrix getColumnCount
		return this->columns_;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		//Done Zadanie 1: InCoherentMatrix
		if (rowIndex < 0 || rowIndex >= this->rows_ ||
			columnIndex < 0 || columnIndex >= this->columns_)
		{
			throw new std::out_of_range("IncoherentMatrix<T>::at: Invalid index.");
		}
		return this->array_->at(rowIndex)->at(columnIndex);
	}
}