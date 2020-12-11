#include "boolean_matrix.h"


BoolMatrix::BoolMatrix(int colCount, int strCount)
{
	if (colCount < 0) 	throw errorColCountLessZero;
	if (strCount < 0) 	throw errorStrCountLessZero;
	
	colCount_ = colCount;
	strCount_ = strCount;

	matrix_ = new BoolVector[strCount_];
	if (colCount != DEFAULT_COUNT)
		for (int i = 0; i < strCount_; i++) matrix_[i].reloadVector(colCount);
}


BoolMatrix::BoolMatrix(int colCount, int strCount, bool valueElem)
{
	if (colCount < 0) 	throw errorColCountLessZero;
	if (strCount < 0) 	throw errorStrCountLessZero;
	
	colCount_ = colCount;
	strCount_ = strCount;

	matrix_ = new BoolVector[strCount_];
	if (colCount != DEFAULT_COUNT)
		for (int i = 0; i < strCount_; i++)
		{
			matrix_[i].reloadVector(colCount);
			if (valueElem) matrix_[i].setOne();
			else matrix_[i].setZero();
		}
	else
		for (int i = 0; i < strCount_; i++)
		{
			if (valueElem) matrix_[i].setOne();
			else matrix_[i].setZero();
		}

}


BoolMatrix::BoolMatrix(char** charMatrix, int colCount, int strCount)
{
	if (colCount < 0) 	throw errorColCountLessZero;
	if (strCount < 0) 	throw errorStrCountLessZero;
	
	colCount_ = colCount;
	strCount_ = strCount;

	matrix_ = new BoolVector[strCount_];
	for (int i = 0; i < strCount_; i++)
	{
		BoolVector newVector(colCount_, charMatrix[i]);
		matrix_[i] = newVector;
	}
};


BoolMatrix::BoolMatrix(const BoolMatrix& copy)
{
	colCount_ = copy.colCount_;
	strCount_ = copy.strCount_;

	matrix_ = new BoolVector[strCount_];
	for (int i = 0; i < strCount_; i++)
		matrix_[i] = copy.matrix_[i];

};


void BoolMatrix::outputFull()
{
	if (strCount_ == 0) std::cout << "Matrix is empty.\n";
	else
	{
		std::cout << "Matrix:\n";
		for (int i = 0; i < strCount_; i++) matrix_[i].outputFull();
	}
}

void BoolMatrix::outputInverse()
{
	if (strCount_ == 0) std::cout << "Matrix is empty.\n";
	else
	{
		std::cout << "Matrix:\n";
		for (int i = 0; i < strCount_; i++) matrix_[i].outputInverse();
	}
}


std::ostream& operator << (std::ostream& f, BoolMatrix& matrix)
{
	if (matrix.strCount_ == 0) std::cout << "Matrix is empty.\n";
	else
	{
		std::cout << "Matrix:\n";
		for (int i = 0; i < matrix.strCount_; i++) f << matrix.matrix_[i] << '\n';
	}
	return f;
};


std::istream& operator >> (std::istream& f, BoolMatrix& matrix)
{
	int oldStrCount = matrix.strCount_;
	std::cout << "Enter row count: ";
	f >> matrix.strCount_;		
	while (matrix.strCount_ < 0)
	{
		std::cout << "Row  count must be > -1. Enter it again: ";
		f >> matrix.strCount_;
	}
	
	std::cout << "Enter coloumn count: ";
	f >> matrix.colCount_;
	while (matrix.colCount_ < 0)
	{
		std::cout << "Coloumn count must be > -1. Enter it again: ";
		f >> matrix.strCount_;
	}

	
	if (oldStrCount != matrix.strCount_)
	{
		delete[]matrix.matrix_;
		matrix.matrix_ = new BoolVector[matrix.strCount_];
	}
	
	std::cout << "Enter matrix:\n";
	for (int i = 0; i < matrix.strCount_; i++)
	{		
		f >> matrix.matrix_[i];
		while (matrix.matrix_[i].getCount() != matrix.colCount_)
		{
			std::cout << "Error. Introduce a vector of length " << matrix.colCount_ << ". Enter " << i << " string again : ";
			f >> matrix.matrix_[i];
		}
	}
	return f;
};


int BoolMatrix::searchWeight()
{
	int result = 0;
	for (int i = 0; i < strCount_; i++) result += matrix_[i].searchWeight();

	return result;
};


int BoolMatrix::searchWeight(int strIndex)
{
	if ((strIndex >= 0) && (strIndex < strCount_)) return matrix_[strIndex].searchWeight();
	else throw 	errorStrIndexOutRange;
};


BoolVector BoolMatrix::disjunctionAllStr()
{
	BoolVector result(0);
	for (int i = 0; i < strCount_; i++) result |= matrix_[i];

	return result;
};


BoolVector BoolMatrix::conjunctionAllStr()
{
	if (strCount_ != 0)
	{
		BoolVector result(matrix_[0]);
		for (int i = 1; i < strCount_; i++) result &= matrix_[i];
		return result;
	}
	else 
	{
		BoolVector result(0);
		return result;
	}
};

void BoolMatrix::invertInd(int strInd, int colInd, int count)
{
	if (count < 0)
	{
		colInd += count;
		count *= -1;
	}

	if ((colInd + count > colCount_) || (colInd < 0)) throw errorColIndexOutRange;
	if ((strInd >= strCount_) || (strInd < 0)) throw errorStrIndexOutRange;

	for (int i = 0; i < count; i++)
		matrix_[strInd].invertInd(colInd + i);

}


BoolMatrix& BoolMatrix::operator =(const BoolMatrix& copy)
{
	if (this != &copy)
	{
		if (strCount_ != copy.strCount_)
		{
			strCount_ = copy.strCount_;
			delete[] matrix_;
			matrix_ = new BoolVector[strCount_];
		}
		colCount_ = copy.colCount_;
		for (int i = 0; i < strCount_; i++) matrix_[i] = copy.matrix_[i];
	}
	return *this;
}

BoolVector& BoolMatrix::operator [](int strInd)
{
	if ((strInd >= strCount_) || (strInd < 0)) throw errorStrIndexOutRange;
	return matrix_[strInd];
}


BoolMatrix BoolMatrix::operator ~()
{
	BoolMatrix result(colCount_, strCount_);
	for (int i = 0; i < strCount_; i++) result.matrix_[i] = ~matrix_[i];

	return result;
}


void BoolMatrix::operator &=(const BoolMatrix& term)
{
	if (term.colCount_ > colCount_) colCount_ = term.colCount_;
	
	if (strCount_ > term.strCount_)
	{
		for (int i = 0; i < term.strCount_; i++) matrix_[i] &= term.matrix_[i];
		for (int i = term.strCount_; i < strCount_; i++) matrix_[i].reloadVector(colCount_);
			
	}
	else
	{
		BoolVector* result;
		result = new BoolVector[term.strCount_];

		for (int i = 0; i < strCount_; i++) result[i] = matrix_[i] & term.matrix_[i];
		for (int i = strCount_; i < term.strCount_ ; i++) result[i].reloadVector(colCount_);

		delete[] matrix_;
		matrix_ = result;
		strCount_ = term.strCount_;
	}	
};


void BoolMatrix::operator |=(const BoolMatrix& term)
{
	if (term.colCount_ > colCount_) colCount_ = term.colCount_;

	if (strCount_ > term.strCount_)
	{
		for (int i = 0; i < term.strCount_; i++) matrix_[i] |= term.matrix_[i];
	}
	else
	{
		BoolVector* result;
		result = new BoolVector[term.strCount_];

		for (int i = 0; i < strCount_; i++) result[i] = matrix_[i] | term.matrix_[i];
		for (int i = strCount_; i < term.strCount_; i++)
		{
			result[i].reloadVector(colCount_);
			result[i] |= term.matrix_[i];
		}

		delete[] matrix_;
		matrix_ = result;
		strCount_ = term.strCount_;
	}
};


void BoolMatrix::operator ^=(const BoolMatrix& term)
{
	if (term.colCount_ > colCount_) colCount_ = term.colCount_;

	if (strCount_ > term.strCount_)
	{
		for (int i = 0; i < term.strCount_; i++) matrix_[i] ^= term.matrix_[i];
		for (int i = term.strCount_; i < strCount_; i++) matrix_[i].invertVector();
	}
	else
	{
		BoolVector* result;
		result = new BoolVector[term.strCount_];

		for (int i = 0; i < strCount_; i++) result[i] = matrix_[i] ^ term.matrix_[i];
		for (int i = strCount_; i < term.strCount_; i++)
		{
			result[i].reloadVector(colCount_);
			result[i] = ~term.matrix_[i];
		}

		delete[] matrix_;
		matrix_ = result;
		strCount_ = term.strCount_;
	}
};