#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../array/array.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

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
		Array<T>* array_;

		size_t rows_;
		size_t columns_;
	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount) :
		Matrix<T>(),
		rows_(rowCount),
		columns_(columnCount),
		array_(new Array<T>(rowCount * columnCount))
	{
		//Done Zadanie 1: CoherentMatrix CoherentMatrix
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other) :
		Matrix<T>(),
		rows_(other.rows_),
		columns_(other.columns_),
		array_(new Array<T>(*other.array_))
	{
		//Done Zadanie 1: CoherentMatrix CoherentMatrix
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		//Done Zadanie 1: CoherentMatrix ~CoherentMatrix
		delete this->array_;
		this->array_ = nullptr;
		this->rows_ = 0;
		this->columns_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		//Done Zadanie 1: CoherentMatrix assign
		if (this != &other)
		{
			CoherentMatrix<T>& otherCM = dynamic_cast<CoherentMatrix<T>&>(other);
			if (this->rows_ == otherCM.rows_ &&
				this->columns_ == otherCM.columns_)
			{
				this->array_->assign(*otherCM.array_);
			}
			else
			{
				std::logic_error("CoherentMatrix<T>::assign: Sizes of matrixes are different");
			}
		}
		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		//Done Zadanie 1: CoherentMatrix equals
		CoherentMatrix<T>* otherCM = dynamic_cast<CoherentMatrix<T>*>(&other);
		return otherCM != nullptr &&
			otherCM->rows_ == this->rows_ &&
			otherCM->columns_ == this->columns_ &&
			this->array_->equals(*otherCM->array_);
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		//Done Zadanie 1: CoherentMatrix size
		return this->rows_ * this->columns_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		//Done Zadanie 1: CoherentMatrix getRowCount
		return this->rows_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		//Done Zadanie 1: CoherentMatrix getColumnCount
		return this->columns_;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		//Done Zadanie 1: CoherentMatrix at
		if (rowIndex < 0 || rowIndex >= this->rows_ ||
			columnIndex < 0 || columnIndex >= this->columns_)
		{
			throw new std::out_of_range("CoherentMatrix<T>::at: Invalid index.");
		}
		//int row = this->columns_ * rowIndex;
		//int arrayIndex = row + columnIndex;
		return this->array_->at(static_cast<int>((this->columns_ * rowIndex) + columnIndex));
	}
}