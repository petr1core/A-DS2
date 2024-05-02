#pragma once
using namespace std;

// Каждый узел в связанном списке хранит ненулевой член многочлена, включая поля данных коэффициента и экспоненты 
#pragma once
class TMonom
{
public:
	double coef;
	int ind;
	TMonom() {
		coef = 0;
		ind = 0;
	}
	TMonom(const TMonom& m) {
		this->coef = m.coef;
		this->ind = m.ind;
	}
	TMonom(TMonom& m) {
		this->coef = m.coef;
		this->ind = m.ind;
	}

	TMonom(double _coef, int degX, int degY, int degZ) {
		coef = _coef;
		if (_coef == 0) throw  ("Coef can't be zero");
		ind = 100 * degX + 10 * degY + degZ;
	}
	
	void SetMonom(double _coef, int degX, int degY, int degZ) {
		this->coef = _coef;
		if (_coef == 0) throw  ("Coef can't be zero");
		this->ind = 100 * degX + 10 * degY + degZ;
	}

	void SetCoef(int cval) { this->coef = cval; }
	int GetCoef(void) { return this->coef; }

	void SetIndex(int ival) { this->ind = ival; }
	int GetIndex(void) { return this->ind; }


	bool operator==(const TMonom& other) {
		return this->coef == other.coef && this->ind == other.ind;
	}

	bool operator!=(const TMonom& other) {
		return this->coef != other.coef || this->ind != other.ind;
	}

	TMonom& operator=(const TMonom& other) {
		this->coef = other.coef;
		this->ind = other.ind;
		return *this;
	}

	bool operator>(const TMonom& other) {
		return this->ind > other.ind || (this->ind == other.ind && this->coef > other.coef);
	}

	bool operator<(const TMonom& other) {
		return this->ind < other.ind || (this->ind == other.ind && this->coef < other.coef);
	}



};