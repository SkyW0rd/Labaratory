#include "BST.hpp"
#include <iostream>
using KeyType = std::string;
using ValueType = double;
std::pair<KeyType, ValueType>& Iterator::operator*()
{
  std::pair<KeyType, ValueType> current;
  current = std::make_pair(_ptr->key, _ptr->value);
  return current;
}
const std::pair<KeyType, ValueType>& Iterator::operator*() const
{
    std::pair<KeyType, ValueType> current;
    current = std::make_pair(_ptr->key, _ptr->value);
    return current;
}
Node* Iterator::operator->()
{
  return _ptr;
}
const Node* Iterator::operator->() const
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
    Node* bufPtr = _ptr;
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
//----------------------------------------------------------------------------------------------------------------
BST::BST(const BST& other)
{
    _root = other._root;
}
BST& BST::operator=(const BST& other)
{
    if (this == &other)
    {
        return *this;
    }
    delete _root;
    _root = other._root;
    return *this;
}
BST::BST(BST&& other) noexcept
{
    _root = other._root;
}
BST& BST::operator=(BST&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    _root = other._root;
    return *this;
}
BST::~BST()
{
    _root = nullptr;
}
ValueType& BST::find(const KeyType& key)
{
    Node* current = _root;
    while (current != nullptr)
    {
        current = current->key > key ? current->right : current->left;
    }
    if (current == nullptr)
    {
        throw std::runtime_error("Not found");
    }
    return current->value;
}
const ValueType& BST::find(const KeyType& key) const
{
    return find(key);
}

void BST::insert(KeyType key, ValueType value)
{   
    Node* current = nullptr;
    current->key = key;
    current->value = value;
    if (_root == nullptr)
    {
        _root = current;
        std::cout << "is added" << std::endl;
    }
    else
    {
        add(_root, current);
    }
}
void BST::remove(KeyType key)
{
    if (_root != nullptr)
    {
        Node* current = _root;
        while (current != nullptr || current->key != key)
        {
            current = current->key > key ? current->right : current->left;
        }
        if (current == nullptr)
        {
            throw std::runtime_error("Not found");
        }
        if (current->left == nullptr && current->right == nullptr)
        {

        }
    }
}
void BST::print()
{
    std::cout << _root->key << " " << _root->value << std::endl;
    Node* current = _root;
    while (current != nullptr)
    {
        while (current->left != nullptr)
        {
            std::cout << current->key << " " << current->value << std::endl;
            current = current->left;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------
void BST::add(Node* pref, Node* current)
{
    if (current->key > pref->key)
    {
        if (pref->right == nullptr)
        {
            pref->right = current;
        }
        else
        {
            add(pref->right, current);
        }
    }
    else
    {
        if (pref->left == nullptr)
        {
            pref->left = current;
        }
        else
        {
            add(pref->left, current);
        }
    }
}
