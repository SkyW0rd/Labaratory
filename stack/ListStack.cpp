#include "ListStack.h"

void ListStack::push(const ValueType& value)
{
  _l.push_back(value);
}
void ListStack::pop()
{
    _l.pop_back();
}
const ValueType& ListStack::top() const
{
    return _l.back();
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
