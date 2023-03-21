#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>


template<typename KeyType, typename ValueType>
class BSTNode
{
public:
    BSTNode *LeftChild;
    BSTNode *RightChild;
    BSTNode *Parent;
    ValueType *value;
    KeyType key;
    BSTNode(KeyType key, ValueType value, BSTNode* parent);
};


template<typename KeyType, typename ValueType>
class BinarySearchTree {
public:

    BSTNode<KeyType, ValueType> *root;

    size_t size() const;

    void insert(KeyType const &key, ValueType const &value);

    void remove(KeyType const &key);

    ValueType *find(KeyType const &key);

    std::string toString() const;

    template<typename StreamType>
    void print(StreamType &stream) const;
};

template<typename KeyType, typename ValueType>
std::ostream &operator<<(std::ostream &stream, BinarySearchTree<KeyType, ValueType> const &tree) {
    tree.print(stream);
    return stream;
}
