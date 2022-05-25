#include "hashTable.h"
using Key = int;
using Value = std::string;
HashTable::HashTable(const HashTable& copyTable)
{
  for(size_t i = 0; i < copyTable.hashGroup; i++)
  {
      _table[i] = copyTable._table[i];
  }
}
HashTable& HashTable::operator=(const HashTable& copyTable)
{
  if(this == &copyTable)
  {
    return *this;
  }
  for(size_t i = 0; i < copyTable.hashGroup; i++)
  {
      _table[i] = copyTable._table[i];
  }
  return *this;
}

HashTable::HashTable(HashTable&& moveTable)
{
  _table = std::move(moveTable._table);
  moveTable._table.clear();
}
HashTable& HashTable::operator=(HashTable&& moveTable)
{
  if(this == &moveTable)
  {
    return *this;
  }
  _table = std::move(moveTable._table);
  moveTable._table.clear();
  return *this;
}
bool HashTable::isEmpty() const
{
  size_t sum = 0;
  for(size_t i = 0; i < hashGroup; i++)
  {
      sum += _table[i].size();
  }
  if(sum == 0)
  {
    return true;
  }
  return false;
}
Key HashTable::func(Key key)
{
  return key % hashGroup;
}
void HashTable::insert(Key key, Value value)
{
  Key hashValue = func(key);
  if(_table.size() == 0)
  {
    _table.resize(10);
  }
  _table[hashValue].push_back(std::make_pair(key, value));
  return;
}
void HashTable::remove(Key key)
{
  Key hashValue = func(key);
  bool keyFlag = false;
  auto& cell = _table[hashValue];
  auto path = begin(cell);
  for(; path != end(cell); path++)
  {
    if(path->first == key)
    {
      keyFlag = true;
      path = cell.erase(path);
      std::cout<<"Pair removed"<<std::endl;
      break;
    }
  }
  if(!keyFlag)
  {
    std::cout<<"Key not found"<<std::endl;
  }
  return;
}
void HashTable::search(Key key)
{
  Key hashValue = func(key);
  bool keyFlag = false;
  for(auto item: _table[hashValue])
  {
    if(item.first == key)
    {
      keyFlag = true;
      std::cout << item.second << std::endl;
      break;
    }
  }
  if(!keyFlag)
  {
    std::cout<<"not found key"<<std::endl;
  }
  return;
}
void HashTable::print()
{
  if(_table.size() != 0)
  {
    return;
  }
  for(size_t i = 0; i < _table.size(); i++)
  {
    if(_table[i].size() == 0) continue;
    for(auto item: _table[i])
    {
      std::cout<<"Key: "<<item.first <<  item.second <<std::endl;
    }
  }
  return;
}
HashTable::~HashTable()
{
  _table.clear();
}
