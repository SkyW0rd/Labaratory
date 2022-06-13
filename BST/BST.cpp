#include "BST.hpp"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------
template <typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::Iterator::operator*()
{
  return *_node->keyValuePair;
}
template <typename Key, typename Value>
const std::pair<Key, Value>& BinarySearchTree<Key, Value>::Iterator::operator*() const
{
  return *_node->keyValuePair;
}
template <typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::Iterator::operator->()
{
  return _node->keyValuePair;
}
template <typename Key, typename Value>
const std::pair<Key, Value>* BinarySearchTree<Key, Value>::Iterator::operator->() const
{
  return _node->keyValuePair;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++()
{
  _node = _node->right;
  return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++(int idx)
{
  for(size_t i = 0; i < idx; i++)
  {
    _node = _node->right;
  }
  return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--()
{
  _node = _node->left;
  return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--(int idx)
{
  for(size_t i = 0; i < idx; i++)
  {
  _node = _node->left;
  }
  return *this;
}
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator==(const Iterator& other) const
{
  return *this == other;
}
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator!=(const Iterator& other) const
{
  return !(*this == other);
}
//----------------------------------------------------------------------------------------------------------------
template <typename Key, typename Value>
const std::pair<Key, Value>& BinarySearchTree<Key, Value>::ConstIterator::operator*() const
{
  return *_node->keyValuePair;
}
template <typename Key, typename Value>
const std::pair<Key, Value>* BinarySearchTree<Key, Value>::ConstIterator::operator->() const
{
  return _node->keyValuePair;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++()
{
  _node = _node->right;
  return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++(int idx)
{
  for(size_t i = 0; i < idx; i++)
  {
    _node = _node->right;
  }
  return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--()
{
  _node = _node->left;
  return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--(int idx)
{
  for(size_t i = 0; i < idx; i++)
  {
  _node = _node->left;
  }
  return *this;
}
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator==(const Iterator& other) const
{
  return *this == other;
}
template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator!=(const Iterator& other) const
{
  return !(*this == other);
}
//----------------------------------------------------------------------------------------------------------------
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(const BinarySearchTree& other)
{
  _size = other.size();
  _root = other._root;
}
template <typename Key, typename Value>
BinarySearchTree<Key, Value>& BinarySearchTree<Key, Value>::operator=(const BinarySearchTree& other)
{
  if(this == &other)
  {
    return *this;
  }
  _size = other.size();
  _root = other._root;
  return *this;
}
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(BinarySearchTree&& other) noexcept
{
  _size = std::move(other.size());
  _root = std::move(other._root);
  other.size() = 0;
  other._root = nullptr;
}
template <typename Key, typename Value>
BinarySearchTree<Key, Value>& BinarySearchTree<Key, Value>::operator=(BinarySearchTree&& other) noexcept
{
  if(this == &other)
  {
    return *this;
  }
  _size = std::move(other.size());
  _root = std::move(other._root);
  other.size() = 0;
  other._root = nullptr;
  return *this;
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const Key& key, const Value& value)
{   
    Node* current = nullptr;
    current->keyValuePair = make_pair(key, value);
    if (_root == nullptr)
    {
        _root = current;
        std::cout << "is added" << std::endl;
    }
    else
    {
        add(_root, current);
    }
  _size++;
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::add(Node* pref, Node* current)
{
    if (current->keyValuePair->first > pref->keyValuePair->first)
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
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::erase(const Key& key)
{
  _erase(_root, key);
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::_erase(Node* pref, Key& key)
{
  if (_root == nullptr)
  {
    if(key < pref->keyValuePair->first)
    {
      _erase(pref->left, key);
    }
    else if (key > pref->keyValuePair->first)
    {
      _erase(pref->right, key);
    }
    else
    {
      if(pref->left == nullptr && pref->right == nullptr)
      {
        if(pref->parent->left == pref)
        {
          pref->parent->left = nullptr;
        }
        else
        {
          pref->parent->right = nullptr;
        }
        delete pref;
      }
      else
      {
        Node* current = nullptr;
        if(pref->left != nullptr)
        {
          current = rightbranch(pref->left);
        }
        else
        {
          current = leftbranch(pref->right);
        }
        current->parent = pref->parent;
        current->right = pref->right;
        current->left = pref->left;
        delete pref;
      }
    }
  }
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::leftbranch(Node* node)
{
  if(node == nullptr)
  {
    return nullptr;
  }
  if(node->left != nullptr)
  {
    return leftbranch(node->left);
  }
  return node;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::rightbranch(Node* node)
{
  if(node == nullptr)
  {
    return nullptr;
  }
  if(node->right != nullptr)
  {
    return rightranch(node->right);
  }
  return node;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
  return find(key);
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::find(const Key& key)
{
    Node* current = _root;
    while (current != nullptr || current->keyValuePair->first != key)
    {
        current = current->key > key ? current->right : current->left;
    }
    if (current == nullptr)
    {
        throw std::runtime_error("Not found");
    }
    return current;
}
// найти все элементы, у которых ключ равен key
// первый итератор пары - первый элемент в дереве, равный key
// второй итератор пары - первый элемент в дереве больший, чем key
// [pair.first, pair.second) - полуинтервал, содержащий все элементы с ключем key
template <typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::Iterator, typename BinarySearchTree<Key, Value>::Iterator> BinarySearchTree<Key, Value>::equalRange(const Key& key)
{
  
}
template <typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::ConstIterator, typename BinarySearchTree<Key, Value>::ConstIterator> BinarySearchTree<Key, Value>::equalRange(const Key& key) const
{
  equalRange(key);
}
// получить итератор на минимальное значение в дереве
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::min(const Key& key) const
{
    Node* current = _root;
    while (current != nullptr || (current->left->keyValuePair->first != key && current->right->keyValuePair->first != key && current->keyValuePair->first == key))
    {
        current = current->keyValuePair->first >= key ? current->right : current->left;
    }
    if (current == nullptr)
    {
        throw std::runtime_error("Not found");
    }
    return current;
}
// получить итератор на максимальное значение в дереве
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::max(const Key& key) const
{
    Node* current = _root;
    while (current != nullptr || (current->left->keyValuePair->first != key && current->right->keyValuePair->first != key && current->keyValuePair->first == key))
    {
        current = current->keyValuePair->first >= key ? current->right : current->left;
    }
    if (current == nullptr)
    {
        throw std::runtime_error("Not found");
    }
    return current;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::begin()
{
  return _root;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::end()
{
    Node* current = _root;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cbegin() const
{
  return _root;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cend() const
{
  Node* current = _root;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}
template <typename Key, typename Value>
size_t BinarySearchTree<Key, Value>::size() const
{
  return _size;
}
//-------------------------------------------------------------------------------------------------------------
template <typename Key, typename Value>
Map<Key, Value>::Map(const Map& other)
{
  _tree = other._tree;
}
template <typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(const Map& other)
{
  if(this == &other)
  {
    return *this;
  }
  _tree = other._tree;
  return *this;
}
template <typename Key, typename Value>
Map<Key, Value>::Map(Map&& other) noexcept
{
  _tree = std::move(other._tree);
}
template <typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(Map&& other) noexcept
{
  if(this == &other)
  {
    return *this;
  }
  _tree = std::move(other._tree);
  return *this;
}
// вставить элемент с ключем key и значением value
// если узел с ключем key уже представлен, то заменить его значение на value
template <typename Key, typename Value>
void Map<Key, Value>::insert(const Key& key, const Value& value)
{
  _tree.insert(key, value);
}
// удалить элемент с ключем key
template <typename Key, typename Value>
void Map<Key, Value>::erase(const Key& key)
{
  _tree.erase(key);
}
// найти элемент, равный ключу key
template <typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::find(const Key& key) const
{
  _tree.find(key);
}
template <typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::find(const Key& key)
{
  _tree.find(key);
}
// доступ к элементу по ключу
// если в момент обращения элемента не существует, создать его, 
// ключ равен key, value равно дефолтному значению для типа Value
template <typename Key, typename Value>
const Value& Map<Key, Value>::operator[](const Key& key) const
{
  return _tree[key];
}
template <typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key& key)
{
  return _tree[key];
}
template <typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::begin()
{
  _tree.begin();
}
template <typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::end()
{
  _tree.end();
}
template <typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::cbegin() const
{
  _tree.cbegin();
}
template <typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::cend() const
{
  _tree.cend;
}
template <typename Key, typename Value>
size_t Map<Key, Value>::size() const
{
  return _tree.size();
}
//-------------------------------------------------------------------------------
template <typename Value>
Set<Value>::Set(const Set& other)
{
  _map = other._map;
}
template <typename Value>
Set<Value>& Set<Value>::operator=(const Set& other)
{
  if(this == &other)
  {
    return *this;
  }
  _map = other._map;
  return *this;
}
template <typename Value>
Set<Value>::Set(Set&& other) noexcept
{
  _map = std::move(other._map);
}
template <typename Value>
Set<Value>& Set<Value>::operator=(Set&& other) noexcept
{
  if(this == &other)
  {
    return *this;
  }
  _map = std::move(other._map);
  return *this;
}
template <typename Value>
void Set<Value>::insert(const Value& value)
{
  _map.insert(value);
}
template <typename Value>
void Set<Value>::erase(const Value& value)
{
  _map.erase(value);
}
template <typename Value>
typename Set<Value>::ConstSetIterator Set<Value>::find(const Value& value) const
{
  _map.find(value);
}
template <typename Value>
typename Set<Value>::SetIterator Set<Value>::find(const Value& key)
{
  _map.find(key);
}
template <typename Value>
bool Set<Value>::contains(const Value& value) const
{
  
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::print()
{
  _print(_root, 0);
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::_print(Node* pref, int level)
{
  if(pref != nullptr)
  {
    _print(pref->left, level + 1);
    for(int i = 0; i < level; i++)
    {
      std::cout << "   ";
    }
    std::cout << pref->keyValuePair->first << " " << pref->keyValuePair->second << std::endl;
    print(pref->right, level + 1);
  }
}
