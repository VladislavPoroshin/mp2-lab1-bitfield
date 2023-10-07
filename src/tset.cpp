#include "tset.h"
typedef unsigned int ui;
using namespace std;

const int P_SIZE = sizeof(ui) * 8;

TSet::TSet(int mp) {
	TBitField A(mp);
	MaxPower = mp;
	BitField = A;
}

TSet::TSet(const TSet& s) {
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

TSet::TSet(const TBitField& bf) {
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField() {
	return(BitField);
}

int TSet::GetMaxPower(void) const {
	return(MaxPower);
}

void TSet::InsElem(const int Elem) {
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) {
	BitField.ClrBit(Elem);
}

int TSet::IsMember(const int Elem) const {
	if (BitField.GetBit(Elem))
		return(1);
	else
		return(0);
}

int TSet::operator==(const TSet& s) const {
	if (BitField != s.BitField)
		return(0);
	else
		return(1);
}

int TSet::operator!=(const TSet& s) const {
	if (*this == s)
		return(0);
	else
		return(1);
}

TSet& TSet::operator=(const TSet& s) {
	if (*this != s) {
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return(*this);
}

TSet TSet::operator+(const int Elem) {
	if (Elem >= MaxPower)
		throw out_of_range("Неверное значение элемента!");
	else
	{
		TSet tmp(Elem + 1);
		tmp.BitField.SetBit(Elem);
		*this = *this + tmp;
		return(*this);
	}
}

TSet TSet::operator-(const int Elem) {
	if (Elem >= MaxPower)
		throw out_of_range("Неверное значение элемента!");
	else {
		if (Elem < ((((MaxPower - 1) / P_SIZE) + 1) * P_SIZE))
			BitField.ClrBit(Elem);
		return(*this);
	}
}

TSet TSet::operator+(const TSet& s) {
	int Max_len = 0;
	if (MaxPower > s.MaxPower)
		Max_len = MaxPower;
	else
		Max_len = s.MaxPower;
	BitField = BitField | s.BitField;
	MaxPower = Max_len;
	return(*this);
}

TSet TSet::operator~(void) {
	BitField = ~(BitField);
	return(*this);
}

TSet TSet::operator*(const TSet& s) {
	int Min_len = 0;
	if (MaxPower < s.MaxPower)
		Min_len = MaxPower;
	else
		Min_len = s.MaxPower;
	TSet bf = s;
	BitField = ~((~(BitField)) | (~(bf.BitField)));
	MaxPower = Min_len;
	return(*this);
}

istream& operator>>(istream& istr, TSet& bf) {
	while (cin.peek() != '\n') {
		int add;
		cin >> add;
		if ((add < 0) || (add >= bf.MaxPower))
			throw out_of_range("Неверное значение элемента!");
		else
			bf = bf + add;
	}
	return(istr);
}

ostream& operator<<(ostream& ostr, const TSet& bf) {
	for (int i = 0; i < bf.MaxPower; i++)
		cout << bf.IsMember(i);
	return(ostr);
}