#include "Vector.h"
#include <iostream>

void Vector::_swap(size_t size, size_t pos)
{
    int count = 0;
    for (size_t i = _size - size + 1; i < _size; i++)
    {
        _data[i] = _data[pos + count];
	count++;
    }
}

void Vector::_realloc(size_t count)
{
    if (_size >= _capacity)
    {
    	if (_capacity == 0)
	{
    	    _capacity = 1;
	}
        _capacity *= _multiplicativeCoef;
        Value* buf = new Value[_capacity];
        for(size_t i = 0; i < _size - count; i++)
        {
            buf[i]=std::move(_data[i]);
        }
        delete[] _data;
        _data = &buf;
    }
}

void Vector::_memory(size_t count)
{
	Value* buf = new Value[_capacity];
        for(size_t i = 0; i < _size - count; i++)
        {
            buf[i]=std::move(_data[i]);
        }
        delete[] _data;
        _data = &buf;
}
//---------------------------------------------------------------------------
Value& Iterator::operator*()
{
    return *_ptr;
}
const Value& Iterator::operator*() const
{
    return *_ptr;
}
Value* Iterator::operator->()
{
    return _ptr;
}
const Value* Iterator::operator->() const
{
    return _ptr;
}
Iterator Iterator::operator++()
{
    ++_ptr;
    return *this;
}
Iterator Iterator::operator++(int)
{
    Value* bufPtr = _ptr;
    ++_ptr;
    return Iterator(bufPtr);
}
bool Iterator::operator==(const Iterator& other) const
{
    return _ptr == other._ptr;
}
bool Iterator::operator!=(const Iterator& other) const
{
    return !(*this == other);
}
//---------------------------------------------------------------------------
Vector::Vector(const Value* rawArray, const size_t size, float coef)
{
    _size = size;
    _data = new Value [_size];
    for ( size_t i = 0; i < _size; i++)
    {
        _data[i] = rawArray[i];
    }
    _capacity = size;
    _multiplicativeCoef = coef;
}
//---------------------------------------------------------------------------
Vector::Vector(const Vector& other)
{
    _size = other._size;
    _data = new Value [other._size];
    for ( size_t i = 0; i < _size; i++)
    {
    	_data[i] = other._data[i];
    }
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
}
//---------------------------------------------------------------------------
Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
    	return *this;
    }
    delete[] _data;
    _size = other._size;
    _data = new Value[other._size];
    for (size_t i = 0; i < _size; i++)
    {
    	_data[i] = other._data[i];
    }
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    return *this;
}
//---------------------------------------------------------------------------
Vector::Vector(Vector&& other) noexcept
{
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 2.0f;
}
//---------------------------------------------------------------------------
Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this == &other)
    {
    	return *this;
    }
    delete[] _data;
    _data = std::move(other._data);
    _size = std::move(other._size);
    _capacity = std::move(other._capacity);
    _multiplicativeCoef = std::move(other._multiplicativeCoef);
    return *this;
}
//---------------------------------------------------------------------------
Vector::~Vector()
{
    _data = nullptr;
    _size = 0;
    _capacity = 0;
    _multiplicativeCoef = 2.0f;
}
//---------------------------------------------------------------------------
void Vector::pushBack(const Value& value)
{
    _size++;
    _realloc(1);
    _data[_size] = value;
}
//---------------------------------------------------------------------------
void Vector::pushFront(const Value& value)
{
    _size++;
    _realloc(1);
    for(size_t i = _size - 1; i > 0; i--)
    {
        _data[i] = _data[i - 1];
    }
    _data[0] = value;
}
//---------------------------------------------------------------------------
void Vector::insert(const Value& value, size_t pos){
    _size += 1;
    _realloc(1);
    for (size_t i = _size - 1; i > pos; i--)
    {
        _data[i] = _data[i - 1];
    }
    _data[pos] = value;
}
//---------------------------------------------------------------------------
void Vector::insert(const Value* values, size_t size ,size_t pos)
{
    _size += size;
    while (_size >= _capacity)
    {
        _realloc(size);
    }
    _swap(size, pos);
    for (size_t i = 0; i < size; i++)
    {
    	_data[pos + i] = values[i];
    }
}
//---------------------------------------------------------------------------
void Vector::insert(const Vector& vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
}
//---------------------------------------------------------------------------
void Vector::popBack()
{
    if (_size != 0)
    {
    	_size--;
    }
    else
    {
    	throw std::out_of_range("Removal from empty vector");
    }
  
}
//---------------------------------------------------------------------------
void Vector::popFront()
{
    if (_size != 0)
    {
    	for (size_t i = 0; i < _size - 1; i++)
	{
    	    _data[i] = _data[i + 1];
	}
    	_size--;
    }
    else
    {
    	throw std::out_of_range("Removal from empty vector");
    }
}
//---------------------------------------------------------------------------
void Vector::erase(size_t pos, size_t count)
{
    if (count > _size)
    {
        _size = _size - (_size - pos);
    }
    else
    {
        for (size_t i = 0; i < count; i++)
        {
            _data[i + pos] = _data[i + pos + count];
            _size--;
        }
    }
}
//---------------------------------------------------------------------------
void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    erase(beginPos, endPos - beginPos + 1);
}
//---------------------------------------------------------------------------
size_t Vector::size() const
{
    return _size;
}
//---------------------------------------------------------------------------
size_t Vector::capacity() const
{
    return _capacity;
}
//---------------------------------------------------------------------------
double Vector::loadFactor() const
{
    return double(_size) / _capacity;
}
//---------------------------------------------------------------------------
Value& Vector::operator[](size_t idx)
{
    return _data[idx];
}
//---------------------------------------------------------------------------
const Value& Vector::operator[](size_t idx) const
{
    return _data[idx];
}
//---------------------------------------------------------------------------
long long Vector::find(const Value& value) const
{
    for(size_t i = 0; i < _size; i++)
    {
    	if (_data[i] == value)
    	{
    	    return i;
    	}
    }
    return -1;
}
//---------------------------------------------------------------------------
void Vector::reserve(size_t capacity)
{
    if (capacity != 0 && capacity > _capacity)
    {
    	_capacity = capacity;
        _memory(0);
    }
}
//---------------------------------------------------------------------------
void Vector::shrinkToFit()
{
    if (_capacity != _size)
    {
        _capacity = _size;
       _memory(0);
    }
}
//---------------------------------------------------------------------------
Iterator Vector::begin()
{
    return Iterator(&_data[0]);
}
Iterator Vector::end()
{
    return Iterator(&_data[_size]);
}
//---------------------------------------------------------------------------
