#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#include <stdexcept>

Stack::Stack(StackContainer container): _containerType(container)
{
    switch (container)
    {
    case StackContainer::List: 
    {
        _pimpl = static_cast<IStackImplementation*>(new ListStack());
        break;
    }
    case StackContainer::Vector: 
    {
        _pimpl = static_cast<IStackImplementation*>(new VectorStack());
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
}
Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container): _containerType(container)
{
    for (size_t i = 0; i < arraySize; i++)
    {
        _pimpl->push(valueArray[i]);
    }
}

Stack::Stack(const Stack& copyStack): _containerType(copyStack._containerType)
{
    switch (_containerType)
    {
    case StackContainer::List: {
        _pimpl = dynamic_cast<IStackImplementation*>(new ListStack());
        break;
    }
    case StackContainer::Vector: {
        _pimpl = dynamic_cast<IStackImplementation*>(new VectorStack());
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
    Stack buffer;
    while (copyStack._pimpl->size() != 0)
    {
        buffer._pimpl->push(copyStack._pimpl->top());
        copyStack._pimpl->pop();
    }
    for (size_t i = 0; buffer._pimpl->size() != 0; i++)
    {
        _pimpl->push(buffer._pimpl->top());
        copyStack._pimpl->push(buffer._pimpl->top());
        buffer._pimpl->pop();
    } 
}

Stack& Stack::operator=(const Stack& copyStack)
{
    if (this == &copyStack)
    {
      return *this;
    }
    delete _pimpl;
    _containerType = copyStack._containerType;
    switch (_containerType)
    {
    case StackContainer::List: {
        _pimpl = dynamic_cast<IStackImplementation*>(new ListStack());
        break;
    }
    case StackContainer::Vector: {
        _pimpl = dynamic_cast<IStackImplementation*>(new VectorStack());
        break;
    }
    default:
        throw std::runtime_error("Неизвестный тип контейнера");
    }
    Stack buffer;
    while (copyStack._pimpl->size() != 0)
      {
          buffer._pimpl->push(copyStack._pimpl->top());
          copyStack._pimpl->pop();
      }
    for (size_t i = 0; buffer._pimpl->size() != 0; i++)
    {
        _pimpl->push(buffer._pimpl->top());
        copyStack._pimpl->push(buffer._pimpl->top());
        buffer._pimpl->pop();
    } 
    return *this;
}
Stack::Stack(Stack&& moveStack) noexcept
{
    _containerType = std::move(moveStack._containerType);
    _pimpl = std::move(moveStack._pimpl);

    moveStack._pimpl = nullptr;
}
Stack& Stack::operator=(Stack&& moveStack) noexcept
{
    if (this == &moveStack)
    {
        return *this;
    }
    _containerType = std::move(moveStack._containerType);
    _pimpl = std::move(moveStack._pimpl);
    return *this;
}

Stack::~Stack()
{
    delete _pimpl;
}

void Stack::push(const ValueType& value)
{
    _pimpl->push(value);
}

void Stack::pop()
{
    _pimpl->pop();
}

const ValueType& Stack::top() const
{
    return _pimpl->top();
}

bool Stack::isEmpty() const
{
    return _pimpl->isEmpty();
}
size_t Stack::size() const
{
    return _pimpl->size();
}
