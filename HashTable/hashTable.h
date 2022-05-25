#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>

using Key = int;
using Value = std::string;

class HashTable 
{
  public:
    HashTable() = default;
    
    explicit HashTable(const HashTable& copyTable);
    HashTable& operator=(const HashTable& copyTable);

    HashTable(HashTable&& moveTable);
    HashTable& operator=(HashTable&& moveTable);

    bool isEmpty() const;
    void insert(Key key, Value value);
    void remove(Key key);
    void search(Key key);
    void print();
    ~HashTable();
    Key func(Key key);
  private:
    static const Key hashGroup = 10;
    std::vector<std::list<std::pair<Key, Value>>> _table;
};
