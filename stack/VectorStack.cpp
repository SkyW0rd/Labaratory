#include "VectorStack.h"
VectorStack::VectorStack()
{
}

void VectorStack::push(const ValueType& value)
{
    _v.push_back(value);
}
void VectorStack::pop()
{
    if (_v.size() != 0)
    {
        _v.pop_back();
    }
}
const ValueType& VectorStack::top() const
{
    if(_v.size() != 0)
    {
        return _v.back();
    }
    else
    {
        return -1;
    }
}
bool VectorStack::isEmpty() const
{
    if (_v.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
size_t VectorStack::size() const
{
    return _v.size();
}
VectorStack::~VectorStack()
{
    _v.clear();
}
