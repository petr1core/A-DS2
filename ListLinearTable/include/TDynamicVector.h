// Динамический вектор - 
// шаблонный вектор на динамической памяти
#pragma once

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz <= 0 || sz >= MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero and less than MAX_VECTOR_SIZE");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (arr == nullptr) throw "TDynamicVector ctor requires non-nullptr arg";
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector<T>& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + v.sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = nullptr;
        std::swap(pMem, v.pMem);
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr)
			delete[] pMem;

		pMem = nullptr;
		sz = 0;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        if (sz != v.sz)
        {
            if (pMem != nullptr)
                delete[] pMem;
            sz = v.sz;
            pMem = new T[sz];
        }
        std::copy(v.pMem, v.pMem + v.sz, pMem);

        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this == &v) return *this;
        if (pMem != nullptr) {
            delete[] pMem;
            //sz = v.sz;
            pMem = nullptr;
        }
        sz = v.sz;
        std::swap(pMem, v.pMem);
        return *this;
    }
    size_t size() const noexcept { return sz; }
    // индексация
    T& operator[](size_t ind)
    {
        if (ind < 0 || ind >= sz) throw out_of_range("Index out of range!");
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < 0 || ind >= sz) throw out_of_range("Index out of range!");
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0 || ind >= sz) throw out_of_range("Index out of range!");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind < 0 || ind >= sz) throw out_of_range("Index out of range!");
        return pMem[ind];
    }
    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) return false;
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return true;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) return true;   // если хотябы один отличается, то, значит что матрицы разные
        }
        return false;
    }
    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] += val;
        }
        return res;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] -= val;
        }
        return res;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] *= val;
        }
        return res;
    }
    TDynamicVector operator/(T val)
    {
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = res.pMem[i] / val;
        }
        return res;
    }
    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator+=(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        for (size_t i = 0; i < sz; i++) {
            pMem[i] += v.pMem[i];
        }
        return *this;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-=(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        for (size_t i = 0; i < sz; i++) {
            pMem[i] -= v.pMem[i];
        }
        return *this;
    }
    TDynamicVector operator/(const TDynamicVector& v) {
        if (sz != v.sz) throw "Different dimensions";
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] / v.pMem[i];
        }
        return res;
    } 
    TDynamicVector operator*(const TDynamicVector& v) {
        if (sz != v.sz) throw "Different dimensions";
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] * v.pMem[i];
        }
        return res;
    }
    /*T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        T res = new T();
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] += pMem[i] * v.pMem[i];
        }
        return res;
    }*/
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор >> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz-1; i++)
            ostr << v.pMem[i] << ", "; // требуется оператор<< для типа T
        ostr << v.pMem[v.sz - 1];
        return ostr;
    }
};