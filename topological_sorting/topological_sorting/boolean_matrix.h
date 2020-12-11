//#pragma once

#ifndef boolean_matrix
#define boolean_matrix

#include "boolean_vector.h"

int const DEFAULT_COL_COUNT = 8;
int const DEFAULT_STR_COUNT = 8;


enum ErrorCodeBoolMatrix
{
	errorColCountLessZero = 11,
	errorStrCountLessZero,
	errorColIndexOutRange,
	errorStrIndexOutRange,
};


class BoolMatrix
{
	BoolVector* matrix_;
	int colCount_, strCount_;

public:
	BoolMatrix(int colCount = DEFAULT_COL_COUNT, int strCount = DEFAULT_COL_COUNT);
	BoolMatrix(int colCount, int strCount, bool valueElem);
	BoolMatrix(char** charMatrix, int colCount, int strCount);
	BoolMatrix(const BoolMatrix& copy);
	~BoolMatrix() { delete[] matrix_; };

	void outputFull();
	void outputInverse();
	
	int getCountCol() { return colCount_; };

	friend std::ostream& operator << (std::ostream& f, BoolMatrix& matrix);
	friend std::istream& operator >> (std::istream& f, BoolMatrix& matrix);

	int searchWeight();
	int searchWeight(int strIndex);

	BoolVector disjunctionAllStr();
	BoolVector conjunctionAllStr();

	void invertInd(int strInd, int colInd, int count = 1);

	void setZeroInd(int strInd, int colInd, int count = 1) { if ((strInd >= strCount_) || (strInd < 0)) throw errorStrIndexOutRange; matrix_[strInd].setZeroInd(colInd, count); };  //
	void setOneInd(int strInd, int colInd, int count = 1) { if ((strInd >= strCount_) || (strInd < 0)) throw errorStrIndexOutRange; matrix_[strInd].setOneInd(colInd, count); };  //

	BoolMatrix& operator =(const BoolMatrix& copy);
	BoolVector& operator [](int strInd);

	BoolMatrix operator ~();

	void operator &=(const BoolMatrix& term);
	BoolMatrix operator &(const BoolMatrix& term) { BoolMatrix result(*this); result &= term; return result; };

	void operator |=(const BoolMatrix& term);
	BoolMatrix operator |(const BoolMatrix& term) { BoolMatrix result(*this); result |= term; return result; };

	void operator ^=(const BoolMatrix& term);
	BoolMatrix operator ^(const BoolMatrix& term) { BoolMatrix result(*this); result ^= term; return result; };
};


#endif