#include "matrix_test.h"
#include "../../structures/matrix/coherent_matrix.h"
#include "../../structures/matrix/incoherent_matrix.h"

namespace tests
{
	tests::MatrixTestInterface::MatrixTestInterface() :
		SimpleTest("Interface")
	{
	}

	void tests::MatrixTestInterface::test()
	{
		structures::Matrix<int>* matrix = this->makeMatrix(20, 20);
		matrix->assign(*matrix);
		matrix->equals(*matrix);
		matrix->size();
		matrix->isEmpty();
		matrix->getRowCount();
		matrix->getColumnCount();
		matrix->at(10, 10);
		delete matrix;
	}

	structures::Matrix<int>* CoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* IncoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestOverall::CoherentMatrixTestOverall() :
		ComplexTest("CoherentMatrix")
	{
		addTest(new CoherentMatrixTestInterface());
		addTest(new CoherentMatrixTestCopy());
		addTest(new CoherentMatrixTestSize());
		addTest(new CoherentMatrixTestAt());
		addTest(new CoherentMatrixTestPerformanceA());
		addTest(new CoherentMatrixTestPerformanceB());
		addTest(new CoherentMatrixTestPerformanceC());
		addTest(new CoherentMatrixTestPerformanceD());
		addTest(new CoherentMatrixTimeTestAt());
		addTest(new CoherentMatrixTimeTestAssign());
		addTest(new CoherentMatrixTimeTestKPower());
	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
		addTest(new IncoherentMatrixTestCopy());
		addTest(new IncoherentMatrixTestSize());
		addTest(new IncoherentMatrixTestAt());
		addTest(new IncoherentMatrixTestPerformanceA());
		addTest(new IncoherentMatrixTestPerformanceB());
		addTest(new IncoherentMatrixTestPerformanceC());
		addTest(new IncoherentMatrixTestPerformanceD());
		addTest(new IncoherentMatrixTimeTestAt());
		addTest(new IncoherentMatrixTimeTestAssign());
		addTest(new IncoherentMatrixTimeTestKPower);
	}

	MatrixTestOverall::MatrixTestOverall() :
		ComplexTest("Matrix")
	{
		addTest(new CoherentMatrixTestOverall());
		addTest(new IncoherentMatrixTestOverall());
	}

	MatrixTestCopy::MatrixTestCopy() :
		SimpleTest("Copy")
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void MatrixTestCopy::test()
	{
		int rows = 100;
		int columns = 50;
		this->logInfo("Creating matrix with rows: " + std::to_string(rows) + " and columns: " + std::to_string(columns));
		structures::Matrix<int>* matrix = this->makeMatrix(rows, columns);
		unsigned int value = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				matrix->at(i, j) = value;
				value = (value + 1) % UINT_MAX;
			}
		}
		structures::Matrix<int>* matrixCopy = makeMatrix(*matrix);
		this->assertTrue(matrix->equals(*matrixCopy), "matrix->equals(*matrixCopy)");
		matrixCopy->at(rows / 2, columns / 2) = rand() % UINT_MAX;
		this->assertFalse(matrix->equals(*matrixCopy), "matrix->equals(*matrixCopy)");
		matrix->assign(*matrixCopy);
		this->assertTrue(matrix->equals(*matrixCopy), "matrix->equals(*matrixCopy)");
		delete matrix;
		delete matrixCopy;
	}

	CoherentMatrixTestCopy::CoherentMatrixTestCopy() :
		MatrixTestCopy()
	{
	}

	structures::Matrix<int>* CoherentMatrixTestCopy::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* CoherentMatrixTestCopy::makeMatrix(structures::Matrix<int>& matrix) const
	{
		structures::CoherentMatrix<int>& cm = dynamic_cast<structures::CoherentMatrix<int>&>(matrix);
		return new structures::CoherentMatrix<int>(cm);
	}

	IncoherentMatrixTestCopy::IncoherentMatrixTestCopy():
		MatrixTestCopy()
	{
	}

	structures::Matrix<int>* IncoherentMatrixTestCopy::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* IncoherentMatrixTestCopy::makeMatrix(structures::Matrix<int>& matrix) const
	{
		structures::IncoherentMatrix<int>& cm = dynamic_cast<structures::IncoherentMatrix<int>&>(matrix);
		return new structures::IncoherentMatrix<int>(cm);
	}

	MatrixTestSize::MatrixTestSize() :
		SimpleTest("Size")
	{
	}

	void MatrixTestSize::test()
	{
		int rows = 95;
		int colums = 60;
		structures::Matrix<int>* matrix = makeMatrix(rows, colums);
		this->assertTrue(matrix->getRowCount() == rows, "matrix->getRowCount() == rows");
		this->assertTrue(matrix->getColumnCount() == colums, "matrix->getColumnCount() == colums");
		this->assertTrue(matrix->size() == rows * colums, "matrix->size() == rows * colums");
		delete matrix;
	}

	CoherentMatrixTestSize::CoherentMatrixTestSize() :
		MatrixTestSize()
	{
	}

	structures::Matrix<int>* CoherentMatrixTestSize::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTestSize::IncoherentMatrixTestSize() :
		MatrixTestSize()
	{
	}

	structures::Matrix<int>* IncoherentMatrixTestSize::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	MatrixTestAt::MatrixTestAt() :
		SimpleTest("At")
	{
	}

	void MatrixTestAt::test()
	{
		int rows = 100;
		int columns = 80;
		int value = 123;
		structures::Matrix<int>* matrix = makeMatrix(rows, columns);

		matrix->at(55, 79) = value;
		this->logInfo("matrix->at(55, 79) = value (" + std::to_string(value) + ")");
		this->assertTrue(matrix->at(55, 79) == value, "(matrix->at(55, 79) == value");

		value = value + 50;
		matrix->at(55, 79) = value;
		this->logInfo("value = value + 50 (" + std::to_string(value) + ")");
		this->assertFalse(matrix->at(55, 79) == 123, "(matrix->at(55, 79) == 123");
		this->assertTrue(matrix->at(55, 79) == value, "(matrix->at(55, 79) == value");
		
		delete matrix;
	}

	CoherentMatrixTestAt::CoherentMatrixTestAt() :
		MatrixTestAt()
	{
	}

	structures::Matrix<int>* CoherentMatrixTestAt::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTestAt::IncoherentMatrixTestAt() :
		MatrixTestAt()
	{
	}

	structures::Matrix<int>* IncoherentMatrixTestAt::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	MatrixTestPerformance::MatrixTestPerformance(int ratioGetRows, int ratioGetColumns, int ratioAt, std::string matrixType, std::string scenario, int rows, int columns) :
		SimpleTest("Performance " + scenario),
		ratioGetRows_(ratioGetRows),
		ratioGetColumns_(ratioGetColumns),
		ratioAt_(ratioAt),
		matrixType_(matrixType),
		scenario_(scenario),
		rows_(rows),
		columns_(columns)
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void MatrixTestPerformance::testUnused()
	{
		int operations = 1000000;
		int maxPercentage = 100;
		int getRowsOperations = (operations / maxPercentage) * this->ratioGetRows_;
		int getColumnsOperations = (operations / maxPercentage) * this->ratioGetColumns_;
		int atOperations = (operations / maxPercentage) * this->ratioAt_;
		structures::Matrix<int>* matrix = makeMatrix(this->rows_, this->columns_);

		structures::Logger::getInstance().logInfo("");
		structures::Logger::getInstance().logInfo(this->matrixType_ + ";rows:;columns:");
		structures::Logger::getInstance().logInfo(this->scenario_ + ";" + std::to_string(this->rows_) + ";" + std::to_string(this->columns_));
		structures::Logger::getInstance().logInfo("Remaining Operatios:;Duration:;Function:;Total Duration:");

		structures::DurationType totalTime;
		for (int i = 0; i < operations; i++)
		{
			int funId = rand() % 100;
			std::string funName;
			structures::DurationType time;
			int funLeft = 0;
			if ((funId < this->ratioGetRows_ && getRowsOperations > 0 )||
				(getColumnsOperations == 0 && atOperations == 0 && getRowsOperations > 0))
			{
				time = testGetRows(matrix);
				funName = "getRowCount";
				funLeft = getRowsOperations;
				getRowsOperations--;
			}
			else if ((funId < this->ratioGetRows_ + this->ratioGetColumns_ && getColumnsOperations > 0) ||
				(getRowsOperations == 0 && atOperations == 0 && getColumnsOperations > 0))
			{
				time = testGetColumns(matrix);
				funName = "getColumnCount";
				funLeft = getColumnsOperations;
				getColumnsOperations--;
			}
			else if (atOperations > 0)
			{
				time = testAt(matrix);
				funName = "at";
				funLeft = atOperations;
				atOperations--;
			}
			totalTime += time;
			structures::Logger::getInstance().logDuration(funLeft, time, funName + ";" + std::to_string(totalTime.count()));
		}

		delete matrix;
	}

	void MatrixTestPerformance::test()
	{
		const int repetitions = 10;
		const int operations = 1000000;
		const int maxPercentage = 100;
		
		structures::Matrix<int>* matrix = makeMatrix(this->rows_, this->columns_);

		for (int i = 0; i < repetitions; i++)
		{
			int getRowsOperations = (operations / maxPercentage) * this->ratioGetRows_;
			int getColumnsOperations = (operations / maxPercentage) * this->ratioGetColumns_;
			int atOperations = (operations / maxPercentage) * this->ratioAt_;
			structures::DurationType duration = structures::DurationType();
			for (int j = 0; j < operations; j++)
			{
				int funId = rand() % 100;
				if ((funId < this->ratioGetRows_ && getRowsOperations > 0) ||
					(getColumnsOperations == 0 && atOperations == 0 && getRowsOperations > 0))
				{
					duration += testGetRows(matrix);
					getRowsOperations--;
				}
				else if ((funId < this->ratioGetRows_ + this->ratioGetColumns_ && getColumnsOperations > 0) ||
					(getRowsOperations == 0 && atOperations == 0 && getColumnsOperations > 0))
				{
					duration += testGetColumns(matrix);
					getColumnsOperations--;
				}
				else if (atOperations > 0)
				{
					duration += testAt(matrix);
					atOperations--;
				}
			}
			structures::Logger::getInstance().logDuration(matrix->size(), duration, this->scenario_ + ";" + this->matrixType_);
		}
		delete matrix;
	}

	structures::DurationType MatrixTestPerformance::testGetRows(structures::Matrix<int>* matrix)
	{
		this->startStopwatch();
		size_t rows = matrix->getRowCount();
		this->stopStopwatch();
		return this->getElapsedTime();
	}

	structures::DurationType MatrixTestPerformance::testGetColumns(structures::Matrix<int>* matrix)
	{
		this->startStopwatch();
		size_t columns = matrix->getColumnCount();
		this->stopStopwatch();
		return this->getElapsedTime();
	}

	structures::DurationType MatrixTestPerformance::testAt(structures::Matrix<int>* matrix)
	{
		int row = rand() % this->rows_;
		int column = rand() % this->columns_;
		int value = rand();
		this->startStopwatch();
		matrix->at(row, column) = value;
		this->stopStopwatch();
		return this->getElapsedTime();
	}

	MatrixTestPerformanceA::MatrixTestPerformanceA(std::string matrixType) :
		MatrixTestPerformance(5, 5, 90, matrixType, "A", 10, 50)
	{
	}

	MatrixTestPerformanceB::MatrixTestPerformanceB(std::string matrixType) :
		MatrixTestPerformance(5, 5, 90, matrixType, "B", 2000, 500)
	{
	}

	MatrixTestPerformanceC::MatrixTestPerformanceC(std::string matrixType) :
		MatrixTestPerformance(10, 30, 60, matrixType, "C", 50, 10)
	{
	}

	MatrixTestPerformanceD::MatrixTestPerformanceD(std::string matrixType) :
		MatrixTestPerformance(10, 30, 60, matrixType, "D", 500, 2000)
	{
	}


	CoherentMatrixTestPerformanceA::CoherentMatrixTestPerformanceA() :
		MatrixTestPerformanceA("Coherent Matrix")
	{
	}

	structures::Matrix<int>* CoherentMatrixTestPerformanceA::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestPerformanceB::CoherentMatrixTestPerformanceB() :
		MatrixTestPerformanceB("Coherent Matrix")
	{
	}

	structures::Matrix<int>* CoherentMatrixTestPerformanceB::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestPerformanceC::CoherentMatrixTestPerformanceC() :
		MatrixTestPerformanceC("Coherent Matrix")
	{
	}

	structures::Matrix<int>* CoherentMatrixTestPerformanceC::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestPerformanceD::CoherentMatrixTestPerformanceD() :
		MatrixTestPerformanceD("Coherent Matrix")
	{
	}

	structures::Matrix<int>* CoherentMatrixTestPerformanceD::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTestPerformanceA::IncoherentMatrixTestPerformanceA() :
		MatrixTestPerformanceA("Incoherent Matrix")
	{
	}

	structures::Matrix<int>* IncoherentMatrixTestPerformanceA::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTestPerformanceB::IncoherentMatrixTestPerformanceB() :
		MatrixTestPerformanceB("Incoherent Matrix")
	{
	}

	structures::Matrix<int>* IncoherentMatrixTestPerformanceB::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTestPerformanceC::IncoherentMatrixTestPerformanceC() :
		MatrixTestPerformanceC("Incoherent Matrix")
	{
	}

	structures::Matrix<int>* IncoherentMatrixTestPerformanceC::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTestPerformanceD::IncoherentMatrixTestPerformanceD() :
		MatrixTestPerformanceD("Incoherent Matrix")
	{
	}

	structures::Matrix<int>* IncoherentMatrixTestPerformanceD::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	MatrixTimeTestAt::MatrixTimeTestAt(std::string matrixType):
		SimpleTest("Time at"),
		matrixType_(matrixType)
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void MatrixTimeTestAt::test()
	{
		size_t rows = 100;
		for (int i = 0; i < 10; i++)
		{
			size_t columns = 100;
			for (int j = 0; j < 10; j++)
			{
				structures::Matrix<int>* matrix = makeMatrix(rows, columns);
				for (int k = 0; k < 100; k++)
				{
					int col = rand() % columns;
					int row = rand() % rows;
					int val = rand();
					this->startStopwatch();
					matrix->at(row, col) = val;
					this->stopStopwatch();
					structures::Logger::getInstance().logDuration(matrix->size(),
						this->getElapsedTime(),
						"at;"
						+ this->matrixType_ + ";"
						+ std::to_string(rows) + "x" + std::to_string(columns));
				}
				delete matrix;
				columns += 100;
			}
			rows += 100;
		}
	}

	CoherentMatrixTimeTestAt::CoherentMatrixTimeTestAt() :
		MatrixTimeTestAt("Coherent Matrix")
	{
	}

	structures::Matrix<int>* CoherentMatrixTimeTestAt::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTimeTestAt::IncoherentMatrixTimeTestAt():
		MatrixTimeTestAt("Incoherent Matrix")
	{
	}

	structures::Matrix<int>* IncoherentMatrixTimeTestAt::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	MatrixTimeTestAssign::MatrixTimeTestAssign(std::string matrixType) :
		SimpleTest("Time assign"),
		matrixType_(matrixType)
	{
	}

	void MatrixTimeTestAssign::test()
	{
		size_t rows = 100;
		for (int i = 0; i < 10; i++)
		{
			size_t columns = 100;
			for (int j = 0; j < 10; j++)
			{
				structures::Matrix<int>* matrix = makeMatrix(rows, columns);
				structures::Matrix<int>* otheMatrix = makeMatrix(rows, columns);
				for (int k = 0; k < 100; k++)
				{
					this->startStopwatch();
					matrix->assign(*otheMatrix);
					this->stopStopwatch();
					structures::Logger::getInstance().logDuration(matrix->size(),
						this->getElapsedTime(),
						"assign;"
						+ this->matrixType_ + ";"
						+ std::to_string(rows) + "x" + std::to_string(columns));
				}
				delete matrix;
				delete otheMatrix;
				columns += 100;
			}
			rows += 100;
		}
	}

	CoherentMatrixTimeTestAssign::CoherentMatrixTimeTestAssign() :
		MatrixTimeTestAssign("Coherent Matrix")
	{
	}

	structures::Matrix<int>* CoherentMatrixTimeTestAssign::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTimeTestAssign::IncoherentMatrixTimeTestAssign():
		MatrixTimeTestAssign("Incoherent Matrix")
	{
	}

	structures::Matrix<int>* IncoherentMatrixTimeTestAssign::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	MatrixTimeTestKPower::MatrixTimeTestKPower(std::string matrixType) :
		SimpleTest("k-power"),
		matrixType_(matrixType)
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	void MatrixTimeTestKPower::test()
	{
		int matrixSize = 10;
		for (int i = 0; i < 10; i++)
		{
			structures::Matrix<int>* matrix1 = makeMatrix(matrixSize, matrixSize);
			fillMatrix(matrix1);
			structures::Matrix<int>* matrix2 = makeMatrix(matrixSize, matrixSize);
			matrix2->assign(*matrix1);
			structures::Matrix<int>* result;
			structures::DurationType duration = structures::DurationType();
			for (int j = 0; j < 10; j++)
			{
				if (j == 0)
				{
					result = makeMatrix(matrixSize, matrixSize);
					this->startStopwatch();
					result->assign(*matrix1);
					this->stopStopwatch();
				}
				else
				{
					result = multiply(matrix1, matrix2);
				}
				duration += this->getElapsedTime();
				structures::Logger::getInstance().logDuration(result->size(), 
					duration,
					this->matrixType_ + ";" 
					+ std::to_string(matrixSize) + "x" + std::to_string(matrixSize) + ";" 
					+ std::to_string(j + 1));
				matrix1->assign(*result);
				delete result;
			}
			delete matrix1;
			delete matrix2;
			matrixSize += 10;
		}
	}

	structures::Matrix<int>* MatrixTimeTestKPower::multiply(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2)
	{
		if (matrix1 != nullptr && matrix2 != nullptr && matrix1->getColumnCount() == matrix2->getRowCount())
		{
			structures::Matrix<int>* newMatrix = this->makeMatrix(matrix1->getRowCount(), matrix2->getColumnCount());
			this->startStopwatch();
			for (int i = 0; i < static_cast<int>(newMatrix->getRowCount()); i++)
			{
				for (int j = 0; j < static_cast<int>(newMatrix->getColumnCount()); j++)
				{
					newMatrix->at(i, j) = this->multiplyRowAndColumn(matrix1, matrix2, i, j);
				}
			}
			this->stopStopwatch();
			return newMatrix;
		}
		return nullptr;
	}

	int MatrixTimeTestKPower::multiplyRowAndColumn(structures::Matrix<int>* matrix1, structures::Matrix<int>* matrix2, int row, int column)
	{
		int value = 0;
		for (int i = 0; i < static_cast<int>(matrix1->getColumnCount()); i++)
		{
			value += matrix1->at(row, i) * matrix2->at(i, column);
		}
		return value;
	}

	void MatrixTimeTestKPower::printMatrix(structures::Matrix<int>* matrix)
	{
		for (int i = 0; i < static_cast<int>(matrix->getRowCount()); i++)
		{
			std::string row = "";
			for (int j = 0; j < static_cast<int>(matrix->getColumnCount()); j++)
			{
				row += " " + std::to_string( matrix->at(i, j));
			}
			this->logInfo(row);
		}
	}

	void MatrixTimeTestKPower::fillMatrix(structures::Matrix<int>* matrix)
	{
		for (int i = 0; i < static_cast<int>(matrix->getRowCount()); i++)
		{
			for (int j = 0; j < static_cast<int>(matrix->getColumnCount()); j++)
			{
				matrix->at(i, j) = rand() % 201 - 100;
			}
		}
	}

	CoherentMatrixTimeTestKPower::CoherentMatrixTimeTestKPower() :
		MatrixTimeTestKPower("Coherent Matrix")
	{
	}

	structures::Matrix<int>* CoherentMatrixTimeTestKPower::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	IncoherentMatrixTimeTestKPower::IncoherentMatrixTimeTestKPower() :
		MatrixTimeTestKPower("Incoherent Matrix")
	{
	}

	structures::Matrix<int>* IncoherentMatrixTimeTestKPower::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}
}
