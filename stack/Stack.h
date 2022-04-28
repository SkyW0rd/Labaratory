#pragma once
#include <iostream>
#include "StackImplementation.h"
#include "VectorStack.h"
#include "ListStack.h"

using ValueType = double;

enum class StackContainer{
  Vector = 0,
  List,
};

class IStackImplementation;

class Stack
{
  public:

    Stack(StackContainer container = StackContainer::Vector);
    Stack(const ValueType* ValueArray, const size_t arraySize, StackContainer container = StackContainer::Vector);

    explicit Stack(const Stack& copyStack);
    Stack& operator=(const Stack& copyStack);

    Stack(Stack&& moveStack) noexcept;
    Stack& operator=(Stack&& moveStack) noexcept;

    ~Stack();

    void push(const ValueType& value);
    void pop();
    size_t size() const;
    bool isEmpty() const;
    const ValueType& top() const;

  private:
    IStackImplementation* _pimpl = nullptr;
    StackContainer _containerType;
};
