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
    ValueType value;
    KeyType key;

    BSTNode(KeyType key, ValueType value, BSTNode *parent = nullptr);
    std::string toString() const;

    size_t height;
};

template<typename KeyType, typename ValueType>
std::string BSTNode<KeyType, ValueType>::toString() const
{
    std::stringstream ss;
    ss << "[" << key << ", " << value << "]";
    return ss.str();
}

template<typename KeyType, typename ValueType>
BSTNode<KeyType, ValueType>::BSTNode(KeyType key, ValueType value, BSTNode *parent)
{
    key = key;
    value = value;
    parent = parent;
    LeftChild = nullptr;
    RightChild = nullptr;
    height = 1;
}


template<typename KeyType, typename ValueType>
class BinarySearchTree
{
public:

    BSTNode<KeyType, ValueType> *root;

    size_t size(BSTNode<KeyType, ValueType> *subRoot) const;

    void insertIntoSubtree(KeyType const &key, ValueType const &value, BSTNode<KeyType, ValueType> *subRoot);

    void insert(KeyType const &key, ValueType const &value, BSTNode<KeyType, ValueType> *subRoot);

    void remove(KeyType const &key);

    ValueType *find(KeyType const &key);

    ValueType *findInSubtree(KeyType const &key, BSTNode<KeyType, ValueType> *subRoot);

    std::string toString() const;

    template<typename StreamType>
    void print(StreamType &stream) const;
};


template<typename KeyType, typename ValueType>
ValueType *BinarySearchTree<KeyType, ValueType>::findInSubtree(const KeyType &key, BSTNode<KeyType, ValueType> *subRoot)
{
    if (subRoot == nullptr || subRoot->key == key)
        return subRoot;

    else if (subRoot->key > key)
        return findInSubtree(key, subRoot->leftChild);

    return findInSubtree(key, subRoot->rightChild);
}

template<typename KeyType, typename ValueType>
ValueType *BinarySearchTree<KeyType, ValueType>::find(const KeyType &key)
{

}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::insertIntoSubtree(const KeyType &key, const ValueType &value,
                                                             BSTNode<KeyType, ValueType> *subRoot)
{
    if (subRoot->key == key)
        subRoot->value = value;
    else if (subRoot->key < key)
    {
        if (subRoot->rightChild == nullptr)
            subRoot->rightChild = new BSTNode<KeyType, ValueType>(key, value, subRoot);
        else
            insertIntoSubtree(key, value, subRoot->rightChild);
    } else if (subRoot->leftChild == nullptr)
        subRoot->leftChild = new BSTNode<KeyType, ValueType>(key, value, subRoot);
    else
        insertIntoSubtree(key, value, subRoot->leftChild);
}


template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value,
                                                  BSTNode<KeyType, ValueType> *subRoot)
{
    if (subRoot == nullptr)
        subRoot = new BSTNode<KeyType, ValueType>(key, value);

    else if (subRoot->key < key)
        insertIntoSubtree(key, value, subRoot->rightChild);

    else
        insertIntoSubtree(key, value, subRoot->leftChild);
}

template<typename KeyType, typename ValueType>
size_t BinarySearchTree<KeyType, ValueType>::size(BSTNode<KeyType, ValueType> *subRoot) const
{
    if (subRoot == nullptr)
        return 0;

    auto left = size(subRoot->leftChild);
    auto right = size(subRoot->rightChild);
    return left + right + 1;
}

template<typename KeyType, typename ValueType>
std::ostream &operator<<(std::ostream &stream, BinarySearchTree<KeyType, ValueType> const &tree)
{
    tree.print(stream);
    return stream;
}
