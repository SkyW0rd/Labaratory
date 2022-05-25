#pragma once

#include <utility>
#include <cstddef>
#include <iosfwd>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <stdexcept>

using KeyType = std::string;
using ValueType = double;
struct Node
{
    KeyType key;
    ValueType value;
    Node* left;
    Node* right;
    Node* parent;
};
class Iterator
{
public:
    explicit Iterator(Node* ptr): _ptr(ptr){}
    std::pair<KeyType, ValueType>& operator*();
    const std::pair<KeyType, ValueType>& operator*() const;
    Node* operator->();
    const Node* operator->() const;
    Iterator operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

private:
    Node* _ptr;
};

class BST
{
public:

    BST() = default;

    explicit BST(const BST& other);
    BST& operator=(const BST& other);

    explicit BST(BST&& other) noexcept;
    BST& operator=(BST&& other) noexcept;

    ~BST();
    
    void insert(KeyType key, ValueType value);
    void remove(KeyType key);
    ValueType& find(const KeyType& key);
    const ValueType& find(const KeyType& key) const;
    Node* min(KeyType key) const;
    Node* max(KeyType key) const;
    Iterator root();
    Iterator begin();
    Iterator end();
    size_t size() const;
    void print();
private:
    size_t _size = 0;
    Node* _root = nullptr;
    void add(Node* pref, Node* current);
};
