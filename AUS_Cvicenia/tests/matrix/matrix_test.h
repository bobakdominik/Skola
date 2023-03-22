#pragma once

#include <cstdlib>
#include "../test.h"
#include "../../structures/matrix/matrix.h"
#include "../../structures/_logger/logger.h"
#include "../../structures/array/array.h"

namespace tests
{

	/// <summary>
	/// Zavola vsetky metody z rozhrania matice avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class MatrixTestInterface
		: public SimpleTest
	{
	public:
		MatrixTestInterface();
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody koherentnej matice.
	/// </summary>
	class CoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zavola vsetky metody nekoherentnej matice.
	/// </summary>
	class IncoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherentMatrix.
	/// </summary>
	class CoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		CoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju IncoherentMatrix.
	/// </summary>
	class IncoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		IncoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherrentMatrix a IncoherrentMatrix.
	/// </summary>
	class MatrixTestOverall
		: public ComplexTest
	{
	public:
		MatrixTestOverall();
	};

	//########################################################################################################
	// Uloha 1
	//########################################################################################################

	//################################################################
	// Matrix test, copy() funkcionalita
	//################################################################

	class MatrixTestCopy
		: public SimpleTest
	{
	public:
		MatrixTestCopy();
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
		virtual structures::Matrix<int>* makeMatrix(structures::Matrix<int>& matrix) const = 0;
	};

	class CoherentMatrixTestCopy
		: public MatrixTestCopy
	{
	public:
		CoherentMatrixTestCopy();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
		structures::Matrix<int>* makeMatrix(structures::Matrix<int>& matrix) const override;
	};

	class IncoherentMatrixTestCopy
		: public MatrixTestCopy
	{
	public:
		IncoherentMatrixTestCopy();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
		structures::Matrix<int>* makeMatrix(structures::Matrix<int>& matrix) const override;
	};

	//################################################################
	// Matrix test, size() funkcionalita
	//################################################################

	class MatrixTestSize
		: public SimpleTest
	{
	public:
		MatrixTestSize();
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	};

	class CoherentMatrixTestSize
		: public MatrixTestSize
	{
	public:
		CoherentMatrixTestSize();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class IncoherentMatrixTestSize
		: public MatrixTestSize
	{
	public:
		IncoherentMatrixTestSize();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	//################################################################
	// Matrix test, at() funkcionalita
	//################################################################

	class MatrixTestAt
		: public SimpleTest
	{
	public:
		MatrixTestAt();
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	};

	class CoherentMatrixTestAt
		: public MatrixTestAt
	{
	public:
		CoherentMatrixTestAt();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class IncoherentMatrixTestAt
		: public MatrixTestAt
	{
	public:
		IncoherentMatrixTestAt();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	//########################################################################################################
	// Uloha 2
	//########################################################################################################

	//################################################################
	// Matrix test, casove zlozitosti
	//################################################################

	class MatrixTestPerformance
		: public SimpleTest
	{
	public:
		MatrixTestPerformance(int ratioGetRows, int ratioGetColumns, int ratioAt, std::string matrixType, std::string scenario, int rows, int columns);
		void test() override;
		void testUnused();

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;

		int ratioGetRows_;
		int ratioGetColumns_;
		int ratioAt_;
		int rows_;
		int columns_;
		std::string matrixType_;
		std::string scenario_;

	private:
		structures::DurationType testGetRows(structures::Matrix<int>* matrix);
		structures::DurationType testGetColumns(structures::Matrix<int>* matrix);
		structures::DurationType testAt(structures::Matrix<int>* matrix);
	};

	//################################################################
	// Matrix test, scenar A-D
	//################################################################

	class MatrixTestPerformanceA
		: public MatrixTestPerformance
	{
	public:
		MatrixTestPerformanceA(std::string matrixType);
	};

	class MatrixTestPerformanceB
		: public MatrixTestPerformance
	{
	public:
		MatrixTestPerformanceB(std::string matrixType);
	};

	class MatrixTestPerformanceC
		: public MatrixTestPerformance
	{
	public:
		MatrixTestPerformanceC(std::string matrixType);
	};

	class MatrixTestPerformanceD
		: public MatrixTestPerformance
	{
	public:
		MatrixTestPerformanceD(std::string matrixType);
	};

	//################################################################
	// Coherent matrix test, scenar A-D
	//################################################################

	class CoherentMatrixTestPerformanceA
		: public MatrixTestPerformanceA
	{
	public:
		CoherentMatrixTestPerformanceA();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class CoherentMatrixTestPerformanceB
		: public MatrixTestPerformanceB
	{
	public:
		CoherentMatrixTestPerformanceB();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class CoherentMatrixTestPerformanceC
		: public MatrixTestPerformanceC
	{
	public:
		CoherentMatrixTestPerformanceC();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class CoherentMatrixTestPerformanceD
		: public MatrixTestPerformanceD
	{
	public:
		CoherentMatrixTestPerformanceD();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	//################################################################
	// Incoherent matrix test, scenar A-D
	//################################################################

	class IncoherentMatrixTestPerformanceA
		: public MatrixTestPerformanceA
	{
	public:
		IncoherentMatrixTestPerformanceA();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class IncoherentMatrixTestPerformanceB
		: public MatrixTestPerformanceB
	{
	public:
		IncoherentMatrixTestPerformanceB();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class IncoherentMatrixTestPerformanceC
		: public MatrixTestPerformanceC
	{
	public:
		IncoherentMatrixTestPerformanceC();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class IncoherentMatrixTestPerformanceD
		: public MatrixTestPerformanceD
	{
	public:
		IncoherentMatrixTestPerformanceD();

	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	//########################################################################################################
	// Uloha 3
	//########################################################################################################

	//################################################################
	// Matrix test, casova analyza pre at() 
	//################################################################

	class MatrixTimeTestAt
		: public SimpleTest
	{
	public:
		MatrixTimeTestAt(std::string matrixType);
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	private:
		std::string matrixType_;
	};

	class CoherentMatrixTimeTestAt
		: public MatrixTimeTestAt
	{
	public:
		CoherentMatrixTimeTestAt();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class IncoherentMatrixTimeTestAt
		: public MatrixTimeTestAt
	{
	public:
		IncoherentMatrixTimeTestAt();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	//################################################################
	// Matrix test, casova analyza pre assign() 
	//################################################################

	class MatrixTimeTestAssign
		: public SimpleTest
	{
	public:
		MatrixTimeTestAssign(std::string matrixType);
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	private:
		std::string matrixType_;
	};

	class CoherentMatrixTimeTestAssign
		: public MatrixTimeTestAssign
	{
	public:
		CoherentMatrixTimeTestAssign();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class IncoherentMatrixTimeTestAssign
		: public MatrixTimeTestAssign
	{
	public:
		IncoherentMatrixTimeTestAssign();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	//########################################################################################################
	// Uloha 4
	//########################################################################################################

	//################################################################
	// Matrix test casova analyza k-tej mocniny
	//################################################################

	class MatrixTimeTestKPower
		: public SimpleTest
	{
	public:
		MatrixTimeTestKPower(std::string matrixType);
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	private:
		structures::Matrix<int>* multiply(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2);
		int multiplyRowAndColumn(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2, int row, int column);
		void printMatrix(structures::Matrix<int>* matrix);
		void fillMatrix(structures::Matrix<int>* matrix);
		std::string matrixType_;
	};

	class CoherentMatrixTimeTestKPower
		: public MatrixTimeTestKPower
	{
	public:
		CoherentMatrixTimeTestKPower();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	class IncoherentMatrixTimeTestKPower
		: public MatrixTimeTestKPower
	{
	public:
		IncoherentMatrixTimeTestKPower();
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};
}