#include "../ListLinearTable/include/TableBase.h"
#include "../ListLinearTable/include/List.h"
#include <vector>
using namespace std;

template<class Key, class Value>
class LinearListTable : public Table<Key, Value>
{
protected:
    struct Row {
        Key key;
        Value value;
    };
    TList<Row> arr;
	
public:
	Value* Find(Key _key) override;
	int Insert(Key _key, Value _val) override;
	int Delete(Key _key) override;

	void Reset(void) override;
	bool IsTabEnded(void) const override;
	int GoNext(void) override;

	Key GetKey(void) const override;
	Value* GetValuePtr(void) override;	//	(=1 first el, if called on last cell of table)				
};

template<class Key, class Value>
Value* LinearListTable<Key, Value>::Find(Key _key)
{
	for (arr.Reset(); !arr.IsEnd(); arr.GoNext()) {
		if ((*arr.GetCurrentItemPtr()).key == _key) {
			return &(*arr.GetCurrentItemPtr()).value;
		}
	}
	return nullptr;
}

template<class Key, class Value>
int LinearListTable<Key, Value>::Insert(Key _key, Value _val)
{
	if (this->IsFull()) return -1;
	if (this->Find(_key) == nullptr)
		arr.InsertLast({ _key,_val });
	else return -1; // already exists
	this->size++;
	return 0;
}

template<class Key, class Value>
int LinearListTable<Key, Value>::Delete(Key _key)
{
	Value* f = Find(_key);
	if (f != nullptr) {
		arr.DeleteCurrent();
		return 0;
	}
	return -1;
}

template<class Key, class Value>
void LinearListTable<Key, Value>::Reset(void) 
{
	arr.Reset();
}

template<class Key, class Value>
bool LinearListTable<Key, Value>::IsTabEnded(void) const
{
	return arr.IsEnd();
}

template<class Key, class Value>
int LinearListTable<Key, Value>::GoNext(void)
{
	arr.GoNext();
	return 0;
}

template<class Key, class Value>
Key LinearListTable<Key, Value>::GetKey(void) const
{
	return (*arr.GetCurrentItemPtr()).key;
}

template<class Key, class Value>
Value* LinearListTable<Key, Value>::GetValuePtr(void)
{
	//return &(this->curs->value).value;
	return &(*arr.GetCurrentItemPtr()).value;
}
