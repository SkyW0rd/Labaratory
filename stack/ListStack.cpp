#include "ListStack.h"
ListStack::ListStack()
{
}
void ListStack::push(const ValueType& value)
{
    _l.push_back(value);
}
void ListStack::pop()
{
    if (_l.size() != 0)
    {
        _l.pop_back();
    }
}
const ValueType& ListStack::top() const
{
    if (_l.size() != 0)
    {
        return _l.back();
    }
    else
    {
        return -1;
    }
}
bool ListStack::isEmpty() const
{
    if (_l.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
size_t ListStack::size() const
{
    return _l.size();
}
ListStack::~ListStack()
{
    _l.clear();
}
