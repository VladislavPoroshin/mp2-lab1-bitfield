#include "tbitfield.h"
typedef unsigned int ui;
using namespace std;

const int P_SIZE = sizeof(ui) * 8;

ui TBitField::GetMemMask(const int n) const {
	return (1 << (n % P_SIZE));
}

TBitField::TBitField(int len) {
	if (len < 0) {
		throw out_of_range("Отрицательная длина!");
	}
	else {
		BitLen = len;
		if (len == 0) {
			pMem = nullptr;
			MemLen = 0;
		}
		else {
			MemLen = (len - 1) / P_SIZE + 1;
			pMem = new ui[MemLen];
			for (int i = 0; i < MemLen; i++)
				pMem[i] = 0;
		}
	}
}

TBitField::~TBitField() {
	delete[] pMem;
};

TBitField::TBitField(const TBitField& bf) {
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new ui[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField& TBitField::operator=(const TBitField& bf) {
	if (*this != bf) {
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		pMem = new ui[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return(*this);
}

int TBitField::GetLength(void) const {
	return(BitLen);
}

void TBitField::SetBit(const int n) {
	if ((n < 0) || (n >= BitLen))
		throw out_of_range("Неверное значение бита!");
	else
		pMem[n / P_SIZE] |= GetMemMask(n % P_SIZE);
}

void TBitField::ClrBit(const int n) {
	if ((n < 0) || (n >= BitLen))
		throw out_of_range("Неверное значение бита!");
	else
		pMem[n / P_SIZE] &= (~(GetMemMask(n % P_SIZE)));
}

int TBitField::GetBit(const int n) const {
	if ((n < 0) || (n >= BitLen))
		throw out_of_range("Неверное значение бита!");
	else {
		return((GetMemMask(n % P_SIZE) | pMem[n / P_SIZE]) == pMem[n / P_SIZE]);
	}
}

int TBitField::operator==(const TBitField& bf) const {
	if ((BitLen != bf.BitLen) || (MemLen != bf.MemLen))
		return(0);
	else {
		for (int i = 0; i < BitLen; i++)
			if (this->GetBit(i) != bf.GetBit(i)) {
				return(0);
			}
		return(1);
	}
}

int TBitField::operator!=(const TBitField& bf) const {
	return (!(this->operator==(bf)));
}

TBitField  TBitField::operator|(const TBitField& bf) {
	int len;
	TBitField A = bf;
	if (BitLen > A.BitLen) {
		for (int i = 0; i < A.MemLen; i++)
			pMem[i] |= A.pMem[i];
		return(*this);
	}
	else {
		for (int i = 0; i < MemLen; i++)
			A.pMem[i] |= pMem[i];
		return(A);
	}
}

TBitField  TBitField::operator&(const TBitField& bf) {
	int len;
	TBitField A = bf;
	if (BitLen > A.BitLen) {
		for (int i = 0; i < A.MemLen; i++)
			pMem[i] &= A.pMem[i];
		return(*this);
	}
	else {
		for (int i = 0; i < MemLen; i++)
			A.pMem[i] &= pMem[i];
		return(A);
	}
}

TBitField  TBitField::operator~(void) {
	for (int i = 0; i < MemLen; i++)
		pMem[i] = ~pMem[i];
	return(*this);
}

int  TBitField::GetMemIndex(const int n) const {
	if ((n < 0) || (n >= BitLen))
		throw out_of_range("Неверное значение бита!");
	else
		return(n / P_SIZE);
}

ostream& operator<<(ostream& ostr, const TBitField& bf) {
	for (int i = 0; i < bf.BitLen; i++)
		cout << bf.GetBit(i);
	return(ostr);
}

istream& operator>>(istream& istr, TBitField& bf) {
	for (int i = 0; (i < bf.BitLen) && (cin.peek() != '\n'); i++) {
		int add;
		cin >> add;
		if ((add != 0) && (add != 1))
			throw out_of_range("Неверное значение бита!");
		else {
			if (add)
				bf.SetBit(i);
			else
				bf.ClrBit(i);
		}
	}
	return(istr);
}
