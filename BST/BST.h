#include <cstddef>
#include <iostream>
#include <utility>
#include <iosfwd>
#include <stdexcept>
/*!
    Имплементация бинарного дерева поиска
    Допускается дублирование ключей (аналог multimap)
*/
template <typename Key, typename Value>
class BinarySearchTree
{
    struct Node
    {
        Node(Key key,
            Value value,
            Node* parent = nullptr,
            Node* left = nullptr,
            Node* right = nullptr);

        std::pair<Key, Value> keyValuePair;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };
private:
    void add(Node* pref, Node* current);
    void _print(Node* pref, int level = 0);
    Node* _erase(Node* pref, const Key& key);
    Node* minVal(Node* pref) noexcept;

public:
    //! Конструктор по умолчанию
    BinarySearchTree() = default;

    //! Копирование
    explicit BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);
    //! Перемещение
    explicit BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    //! Деструктор
    ~BinarySearchTree();

    /*!
        Итератор бинарного дерева поиска

        Обходит дерево последовательно от меньшего ключа к большему
    */
    class Iterator
    {
    public:
        explicit Iterator(Node* node):_node(node){}

        std::pair<Key, Value>& operator*();
        const std::pair<Key, Value>& operator*() const;

        std::pair<Key, Value>* operator->();
        const std::pair<Key, Value>* operator->() const;

        Iterator operator++();
        Iterator operator++(int);

        Iterator operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* _node;
        void BSTreeIncrement();
        void BSTreeDicrement();
    };

    /*!
        Константный итератор
    */
    class ConstIterator
    {
    public:
        explicit ConstIterator(const Node* node):_node(node){}

        const std::pair<Key, Value>& operator*() const;

        const std::pair<Key, Value>* operator->() const;

        ConstIterator operator++();
        ConstIterator operator++(int);

        ConstIterator operator--();
        ConstIterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        const Node* _node;
        void BSTreeIncrement();
        void BSTreeDicrement();
    };

    // вставить элемент с ключем key и значением value
    void insert(const Key& key, const Value& value);

    // удалить все элементы с ключем key
    void erase(const Key& key);

    // найти первый элемент в дереве, равный ключу key
    ConstIterator find(const Key& key) const;
    Iterator find(const Key& key);

    // найти все элементы, у которых ключ равен key
    // первый итератор пары - первый элемент в дереве, равный key
    // второй итератор пары - первый элемент в дереве больший, чем key
    // [pair.first, pair.second) - полуинтервал, содержащий все элементы с ключем key
    std::pair<Iterator, Iterator> equalRange(const Key& key);
    std::pair<ConstIterator, ConstIterator> equalRange(const Key& key) const;

    // получить итератор на минимальное значение в дереве
    ConstIterator min(const Key& key) const;
    // получить итератор на максимальное значение в дереве
    ConstIterator max(const Key& key) const;

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    size_t size() const;
    void print();

private:
    size_t _size = 0;
    Node* _root = nullptr; //!< корневой узел дерева
};


/*!
    Имплементация словаря
    Не допускается дублирование ключей (аналог std::map)
*/

template <typename Key, typename Value>
class Map
{
    BinarySearchTree<Key, Value> _tree;
public:
    using MapIterator = typename BinarySearchTree<Key, Value>::Iterator;
    using ConstMapIterator = typename BinarySearchTree<Key, Value>::ConstIterator;

    Map() = default;

    explicit Map(const Map& other);
    Map& operator=(const Map& other);

    explicit Map(Map&& other) noexcept;
    Map& operator=(Map&& other) noexcept;

    ~Map() = default;

    // вставить элемент с ключем key и значением value
    // если узел с ключем key уже представлен, то заменить его значение на value
    void insert(const Key& key, const Value& value);

    // удалить элемент с ключем key
    void erase(const Key& key);

    // найти элемент, равный ключу key
    ConstMapIterator find(const Key& key) const;
    MapIterator find(const Key& key);

    // доступ к элементу по ключу
    // если в момент обращения элемента не существует, создать его, 
    // ключ равен key, value равно дефолтному значению для типа Value
    const Value& operator[](const Key& key) const;
    Value& operator[](const Key& key);

    MapIterator begin();
    MapIterator end();

    ConstMapIterator cbegin() const;
    ConstMapIterator cend() const;

    size_t size() const;
};


/*!
    Имплементация множества
    Не допускается дублирование ключей (аналог std::set)
*/
template <typename Value>
class Set
{
    Map<Value, Value> _map;
    bool _contains(Map<Value, Value>& pref, const Value& value);
public:
    using SetIterator = typename Map<Value, Value>::MapIterator;
    using ConstSetIterator = typename Map<Value, Value>::ConstMapIterator;

    Set() = default;

    explicit Set(const Set& other);
    Set& operator=(const Set& other);

    explicit Set(Set&& other) noexcept;
    Set& operator=(Set&& other) noexcept;

    ~Set() = default;

    void insert(const Value& value);

    void erase(const Value& value);

    ConstSetIterator find(const Value& value) const;
    SetIterator find(const Value& key);

    bool contains(const Value& value) const;
};
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::Node::Node(Key key, Value value, Node* parent, Node* left, Node* right)
{
    keyValuePair = std::make_pair(key, value);
    parent = parent;
    left = left;
    right = right;
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::Iterator::BSTreeIncrement()
{
    if (_node->right)
    {
        _node = _node->right;
        while (_node->left)
        {
            _node = _node->left;
        }
    }
    else
    {
        Node* pref = _node->parent;
        if (pref->right == _node)
        {
            _node = pref;
            pref = _node->parent;
        }
        if (_node->right != pref)
        {
            _node = pref;
        }
    }
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::Iterator::BSTreeDicrement()
{
    if (_node->parent->parent == _node)
    {
        _node = _node->right;
    }
    else if (_node->left)
    {
        _node = _node->left;
        while (_node->right)
        {
            _node = _node->right;
        }
    }
    else
    {
        Node* pref = _node->parent;
        if (pref->left == _node)
        {
            _node = pref;
            pref = _node->parent;
        }
        _node = pref;
    }
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::ConstIterator::BSTreeIncrement()
{
    if (_node->right)
    {
        _node = _node->right;
        while (_node->left)
        {
            _node = _node->left;
        }
    }
    else
    {
        Node* pref = _node->parent;
        if (pref->right == _node)
        {
            _node = pref;
            pref = _node->parent;
        }
        if (_node->right != pref)
        {
            _node = pref;
        }
    }
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::ConstIterator::BSTreeDicrement()
{
    if (_node->parent->parent == _node)
    {
        _node = _node->right;
    }
    else if (_node->left)
    {
        _node = _node->left;
        while (_node->right)
        {
            _node = _node->right;
        }
    }
    else
    {
        Node* pref = _node->parent;
        if (pref->left == _node)
        {
            _node = pref;
            pref = _node->parent;
        }
        _node = pref;
    }
}
//----------------------------------------------------------------------------------------------------------------
template <typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::Iterator::operator*()
{
    return _node->keyValuePair;
}
template <typename Key, typename Value>
const std::pair<Key, Value>& BinarySearchTree<Key, Value>::Iterator::operator*() const
{
    return _node->keyValuePair;
}
template <typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::Iterator::operator->()
{
    return &_node->keyValuePair;
}
template <typename Key, typename Value>
const std::pair<Key, Value>* BinarySearchTree<Key, Value>::Iterator::operator->() const
{
    return &_node->keyValuePair;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++()
{
    BSTreeIncrement();
    return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++(int idx)
{
    Iterator buf(*this);
    BSTreeIncrement();
    return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--()
{
    BSTreeDicrement();
    return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--(int idx)
{
    Iterator buf(*this);
    BSTreeDicrement();
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
    BSTreeIncrement();
    return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++(int idx)
{
    ConstIterator buf(*this);
    BSTreeIncrement();
    return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--()
{
    BSTreeDicrement();
    return *this;
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--(int idx)
{
    ConstIterator buf(*this);
    BSTreeDicrement();
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
    if (this == &other)
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
    if (this == &other)
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
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    delete[] _root;
    _size = 0;
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const Key& key, const Value& value)
{
    Node* current = new Node(key, value);
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
    if (current->keyValuePair.first >= pref->keyValuePair.first)
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
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::minVal(Node* pref) noexcept
{
    if (pref == nullptr || pref->left == nullptr)
    {
        return pref;
    }
    return minVal(pref->left);
    
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::erase(const Key& key)
{
    _erase(_root, key);
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::_erase(Node* pref, const Key& key)
{
    if (pref == nullptr)
    {
        return pref;
    }
    if (pref->keyValuePair.first > key)
    {
        pref->left = _erase(pref->left, key);
    }
    else if (pref->keyValuePair.first < key)
    {
        pref->right = _erase(pref->right, key);
    }
    else
    {
        if (pref->left == nullptr && pref->right == nullptr)
        {
            return nullptr;
        }
        else if (pref->left == nullptr)
        {
            Node* buf = pref->right;
            delete pref;
            return buf;
        }
        else if (pref->right == nullptr)
        {
            Node* buf = pref->left;
            delete pref;
            return buf;
        }
        Node* buf = minVal(pref->right);
        pref->keyValuePair.first = buf->keyValuePair.first;
        pref->keyValuePair.second = buf->keyValuePair.second;
        pref->right = _erase(pref -> right, buf->keyValuePair.first);
    }
    return pref;
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
    while (current != nullptr || current->keyValuePair.first != key)
    {
        current = current->keyValuePair.first > key ? current->right : current->left;
    }
    if (current == nullptr)
    {
        throw std::runtime_error("Not found");
    }
    return Iterator(current);
}
// найти все элементы, у которых ключ равен key
// первый итератор пары - первый элемент в дереве, равный key
// второй итератор пары - первый элемент в дереве больший, чем key
// [pair.first, pair.second) - полуинтервал, содержащий все элементы с ключем key
template <typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::Iterator, typename BinarySearchTree<Key, Value>::Iterator> BinarySearchTree<Key, Value>::equalRange(const Key& key)
{
    Node* current = find(key);
    Node* pref = current;
    while (pref->right->keyValuePair.first > key)
    {
        pref = pref->right;
    }
    return std::make_pair(static_cast<Iterator>(current), static_cast<Iterator>(pref->right));
}
template <typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::ConstIterator, typename BinarySearchTree<Key, Value>::ConstIterator> BinarySearchTree<Key, Value>::equalRange(const Key& key) const
{
    return equalRange(key);
}
// получить итератор на минимальное значение в дереве
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::min(const Key& key) const
{
    Node* current = _root;
    while (current != nullptr || (current->left->keyValuePair.first != key && current->right->keyValuePair.first != key && current->keyValuePair.first == key))
    {
        current = current->keyValuePair.first >= key ? current->right : current->left;
    }
    if (current == nullptr)
    {
        throw std::runtime_error("Not found");
    }
    return Iterator(current);
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
    return Iterator(current);
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::begin()
{
    return Iterator(minVal(_root));
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::end()
{
    return Iterator(nullptr);
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cbegin() const
{
    return Iterator(minVal(_root));
}
template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cend() const
{
    return Iterator(nullptr);
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
    if (this == &other)
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
    if (this == &other)
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
    if (this == &other)
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
    if (this == &other)
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
    return _contains(_map, value);
}
template <typename Value>
bool Set<Value>::_contains(Map<Value, Value>& pref, const Value& value)
{
    if (pref != nullptr)
    {
        if (pref->keyValuePair.second == value)
        {
            return true;
        }
        _contains(pref->left, value);
        if (pref->KeyValuePair.second == value)
        {
            return true;
        }
        _contains(pref->left, value);

    }
    return false;
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::print()
{
    _print(_root, 0);
}
template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::_print(Node* pref, int level)
{
    if (pref != nullptr)
    {
        _print(pref->left, level + 1);
        for (int i = 0; i < level; i++)
        {
            std::cout << "   ";
        }
        std::cout << pref->keyValuePair.first << " " << pref->keyValuePair.second << std::endl;
        _print(pref->right, level + 1);
    }
}
