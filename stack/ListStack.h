#pragma once
#include <list>
#include <iostream>
#include "StackImplementation.h"

using ValueType = double;

class ListStack: public IStackImplementation
{
  public:
    
    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;

    ~ListStack();

  private:
    std::list<ValueType> _l;
};
