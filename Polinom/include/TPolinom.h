#pragma once
#include "TMonom.h"
#include "HeadList.h"
#include "TDynamicVector.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

const int nonDisplayedZeros = 4;
const int precision = 4;

class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(const TPolinom& other);
	TPolinom(TPolinom& other);

	TPolinom(string str);
	TPolinom& operator=(const TPolinom& other);
	TPolinom& operator+(TPolinom& q);


	void AddMonom(TMonom newMonom);
	TPolinom MultMonom(TMonom monom);
	TPolinom& operator*(double coef);
	bool operator==(const TPolinom& other);
	bool operator!=(const TPolinom& other);
	string ToString();
	friend ostream& operator<<(ostream& os, TPolinom& p)
	{
		os << p.ToString();
		return os;
	}
};

TPolinom::TPolinom() : THeadList<TMonom>::THeadList() { }//

TPolinom::TPolinom(const TPolinom& other)//
{
	pHead = new TNode<TMonom>;
	TNode<TMonom>* h = other.pHead->pNext;
	while (h != other.pStop) {
		this->AddMonom(h->value);
		h = h->pNext;
	}
	
}
TPolinom::TPolinom( TPolinom& other)//
{
	pHead = new TNode<TMonom>;
	TNode<TMonom>* h = other.pHead->pNext;
	while (h != other.pStop) {
		this->AddMonom(h->value);
		h = h->pNext;
	}

}

TPolinom::TPolinom(string str)//
{
	size_t pos = 0;
	while (pos < str.length()) {
		double coef = 0.0;
		int degX = 0, degY = 0, degZ = 0;
		char var;
		if (isdigit(str[pos]) || str[pos] == '-' || str[pos] == '+') {
			size_t nextPos;
			coef = stod(str.substr(pos), &nextPos);
			pos += nextPos;
		}
		while (pos < str.length() && (str[pos] == 'x' || str[pos] == 'X' ||
			str[pos] == 'y' || str[pos] == 'Y' ||
			str[pos] == 'z' || str[pos] == 'Z')) {
			var = tolower(str[pos]);
			pos++;
			if (pos < str.length() && str[pos] == '^') {
				pos++;
				size_t nextPos;
				int deg = stoi(str.substr(pos), &nextPos);
				pos += nextPos;
				switch (var) {
				case 'x': degX = deg; break;
				case 'y': degY = deg; break;
				case 'z': degZ = deg; break;
				}
			}
			else {
				switch (var) {
				case 'x': degX = 1; break;
				case 'y': degY = 1; break;
				case 'z': degZ = 1; break;
				}
			}
		}
		this->AddMonom(TMonom(coef, degX, degY, degZ));
	}
}

TPolinom& TPolinom::operator=(const TPolinom& other)//
{
	if (this != &other) {
		while (!this->IsEmpty()) {
			this->DeleteFirst();
		}
		TNode<TMonom>* current = other.pHead->pNext;
		while (current != nullptr) {
			this->AddMonom(current->value);
			current = current->pNext;
		}
	}
	return *this;
}

void TPolinom::AddMonom(TMonom otherMon)//
{
	if (otherMon.coef == 0) throw invalid_argument("Cannot add monom with zero coefficient");
	this->Reset();
	bool isadd = false;
	while (!this->IsEnd()) {
		if (this->pCurrent->value.ind == otherMon.ind) {
			this->pCurrent->value.coef += otherMon.coef;
			if (fabs(this->pCurrent->value.coef) < 1e-6) {
				this->DeleteCurrent();
			}
			isadd = true;
			break;
		}
		this->GoNext();
	}
	if (!isadd) this->InsertLast(otherMon);
	pHead->pNext = this->pFirst;
}

TPolinom TPolinom::MultMonom(TMonom monom)//
{
	TPolinom res(*this);
	TNode<TMonom>* current = res.pHead->pNext;
	while (current != nullptr) {
		current->value.coef *= monom.coef;
		current->value.ind += monom.ind;
		current = current->pNext;
	}
	return res;
}

TPolinom& TPolinom::operator+(TPolinom& other)//
{
	if (other.IsEmpty()) throw invalid_argument("Cannot add an empty polynomial");
	TNode<TMonom>* current = other.pHead->pNext;
	while (current != nullptr) {
		this->AddMonom(current->value);
		current = current->pNext;
	}
	return *this;
}

TPolinom& TPolinom::operator*(double _coef)//
{
	if (this->IsEmpty()) throw invalid_argument("Cannot multiply an empty polynomial");
	TNode<TMonom>* current = this->pHead->pNext;
	while (current != nullptr) {
		current->value.coef *= _coef;
		if (current->pNext == nullptr) break;
		current = current->pNext;
	}
	return *this;
}

bool TPolinom::operator==(const TPolinom& other)//
{
	if (this->GetLength() != other.GetLength()) return false;
	TNode<TMonom>* thisCurrent = this->pHead->pNext;
	TNode<TMonom>* otherCurrent = other.pHead->pNext;
	while (thisCurrent != nullptr && otherCurrent != nullptr) {
		if (!(thisCurrent->value == otherCurrent->value)) { return false; }
		thisCurrent = thisCurrent->pNext;
		otherCurrent = otherCurrent->pNext;
	}
	return thisCurrent == otherCurrent;
}

bool TPolinom::operator!=(const TPolinom& other)
{
	if (this->GetLength() != other.GetLength()) return true;
	TPolinom otherr(other);
	this->Reset();
	otherr.Reset();
	for (int i = 0; i < this->GetLength(); i++) {
		TMonom f = this->GetCurrentItem();
		TMonom s = otherr.GetCurrentItem();
		if (f != s) return true;
		this->GoNext();
		otherr.GoNext();
	}
	return false;
}

string TPolinom::ToString()//
{
	string res;
	this->Reset();
	int size = this->GetLength();
	for (size_t i = 0; i < size; i++)
	{
		TMonom m = this->GetCurrentItem();
		double d = m.GetCoef();
		int ind = m.GetIndex();
		std::ostringstream output;
		output << setprecision(precision) << d;
		res += output.str() + "x" + to_string((ind - ind % 100) / 100);
		res += "y" + to_string(((ind % 100) - (ind % 10)) / 10);
		res += "z" + to_string(ind % 10);
		if (i != size - 1) {
			res += "+";
			this->GoNext();
		}
	}
	this->Reset();
	return res;
}