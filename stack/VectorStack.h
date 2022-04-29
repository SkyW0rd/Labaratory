#pragma once
#include <vector>
#include <iostream>
#include "StackImplementation.h"

using ValueType = double;

class VectorStack: public IStackImplementation
{
  public:
    void push(const ValueType& value) override;
    void pop() override;
    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;

    ~VectorStack();
  private:
    std::vector<ValueType> _v;
};
