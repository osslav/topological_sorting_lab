//#pragma once

#ifndef boolean_vector
#define boolean_vector


#include <iostream>

int const DEFAULT_COUNT = 8;
int const MAX_COUNT_FOR_INPUT = 64;

enum ErrorCodeBoolVector
{
	errorCountLessZero = 1,
	errorStringEmpty,
	errorSymbolString,

	errorIndexOutVector,
	errorRangeIndexOutVector,
};



// ������ 1110110001 �������� � ������ ���:  00000011 10110001 
class BoolVector
{
	unsigned char* vector_;
	int count_;									//����� �������
	int memory_;								//���������� ���������� ����

public:
	BoolVector(int count = DEFAULT_COUNT);
	BoolVector(int count, bool value);
	BoolVector(int count, unsigned char* string, int countString);
	BoolVector(int count, const char* stringVector);
	BoolVector(const BoolVector& copy);
	~BoolVector() { delete[] vector_; };

	void reloadVector(int count);														//����� �����
	int getCount() { return count_; };													//����� �����
	int getMemory() { return memory_; };


	void outputFull();
	void outputInverse();

	friend std::ostream& operator << (std::ostream& f, const BoolVector& vector);
	friend std::istream& operator >> (std::istream& f, BoolVector& vector);				//������� ����������

	void invertVector();
	BoolVector operator ~();															//����� �����
	void invertInd(int index);

	void setZero();
	void setOne();
	void setZeroInd(int index, int count = 1);
	void setOneInd(int index, int count = 1);

	int searchWeight();

	BoolVector operator &(BoolVector term);
	void operator &=(BoolVector term);

	BoolVector operator |(BoolVector term);
	void operator |=(BoolVector term);

	BoolVector operator ^(BoolVector term);
	void operator ^=(BoolVector term);

	BoolVector& operator =(const BoolVector& copy);

	bool operator [](int index);

	BoolVector operator <<(int count);

	BoolVector operator >>(int count);                  

	void operator <<=(int count);

	void operator >>=(int count);
};


#endif
