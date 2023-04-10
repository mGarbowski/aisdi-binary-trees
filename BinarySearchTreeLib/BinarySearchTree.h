#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>


template<typename KeyType, typename ValueType>
class BinarySearchTree
{
public:
    class Node
    {
    public:
        Node *leftChild;
        Node *rightChild;
        ValueType value;
        KeyType key;


        Node(KeyType key, ValueType value);

        ~Node();

        std::string toString(std::string separator = "") const;

    };

private:
    BinarySearchTree<KeyType, ValueType>::Node *root;

    static const auto PRINT_NEST_INDENT = 4;

    static BinarySearchTree<KeyType, ValueType>::Node *
    findNode(KeyType const &key, BinarySearchTree<KeyType, ValueType>::Node *subRoot);

    Node **findClosest(KeyType const &key, BinarySearchTree<KeyType, ValueType>::Node **starting_point);

    static std::string subTreeToString(BinarySearchTree<KeyType, ValueType>::Node *subRoot);

    template<typename StreamType>
    static void printSubtree(StreamType &stream, BinarySearchTree<KeyType, ValueType>::Node *subRoot, int indent,
                             std::string const &prefix);

    static std::string indentWhitespace(int width);

    size_t sizeOfSubtree(BinarySearchTree<KeyType, ValueType>::Node *subRoot) const;

public:

    BinarySearchTree();

    ~BinarySearchTree();

    size_t size() const;

    void insert(KeyType const &key, ValueType const &value);

    ValueType *find(KeyType const &key);

    std::string toString() const;

    template<typename StreamType>
    void print(StreamType &stream) const;

    KeyType findClosestTester(KeyType &key);

    void remove(KeyType const &key);
};

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::remove(const KeyType &key)
{
    if (root == nullptr)
        return;

    BinarySearchTree<KeyType, ValueType>::Node** rootptr = &root;
    BinarySearchTree<KeyType, ValueType>::Node** closest = findClosest(key, rootptr);

    if ((*closest)->key != key)
        return;

    if ((*closest)->rightChild == nullptr && (*closest)->leftChild == nullptr)
    {
        auto removedNode = *closest;
        *closest = nullptr;
        delete removedNode;
    }

    else if ((*closest)->rightChild == nullptr && (*closest)->leftChild != nullptr)
    {
        auto removedNode = *closest;
        *closest = (*closest)->leftChild;
        delete removedNode;
    }

    else if ((*closest)->leftChild == nullptr && (*closest)->rightChild != nullptr)
    {
        auto removedNode = *closest;
        *closest = (*closest)->rightChild;
        delete removedNode;
    }

    else
    {
        return;
    }
}

template<typename KeyType, typename ValueType>
KeyType BinarySearchTree<KeyType, ValueType>::findClosestTester(KeyType &key)
{
    BinarySearchTree<KeyType, ValueType>::Node **rootptr = &root;
    auto closest = findClosest(key, rootptr);
    int k = (*closest)->key;
    return k;
}

template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node **
BinarySearchTree<KeyType, ValueType>::findClosest(const KeyType &key,
                                                  BinarySearchTree<KeyType, ValueType>::Node **starting_point)
{
    Node **current_closest = starting_point;

    if ((*current_closest)->key == key)
    {
        return current_closest;
    } else if ((*current_closest)->key > key && (*current_closest)->leftChild != nullptr)
    {
        current_closest = &((*current_closest)->leftChild);
        return findClosest(key, current_closest);
    } else if ((*current_closest)->key < key && (*current_closest)->rightChild != nullptr)
    {
        current_closest = &((*current_closest)->rightChild);
        return findClosest(key, current_closest);
    } else
        return current_closest;
}

template<typename KeyType, typename ValueType>
size_t BinarySearchTree<KeyType, ValueType>::sizeOfSubtree(BinarySearchTree<KeyType, ValueType>::Node *subRoot) const
{
    if (subRoot == nullptr)
        return 0;

    auto left = sizeOfSubtree(subRoot->leftChild);
    auto right = sizeOfSubtree(subRoot->rightChild);
    return left + right + 1;
}

template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::~BinarySearchTree()
{
    delete root;
}

template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::Node::~Node()
{
    delete leftChild;
    delete rightChild;
}

template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::BinarySearchTree()
{
    root = nullptr;
}


template<typename KeyType, typename ValueType>
std::string BinarySearchTree<KeyType, ValueType>::Node::toString(std::string separator) const
{
    std::stringstream ss;
    ss << "[" << key << "," << separator << value << "]";
    return ss.str();
}

template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::Node::Node(KeyType key, ValueType value)
{
    this->key = key;
    this->value = value;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}


template<typename KeyType, typename ValueType>
template<typename StreamType>
void BinarySearchTree<KeyType, ValueType>::print(StreamType &stream) const
{
    printSubtree(stream, root, 0, "");
}

template<typename KeyType, typename ValueType>
std::string BinarySearchTree<KeyType, ValueType>::indentWhitespace(int width)
{
    return std::string(width, ' ');
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void BinarySearchTree<KeyType, ValueType>::printSubtree(StreamType &stream,
                                                        BinarySearchTree<KeyType, ValueType>::Node *subRoot,
                                                        const int indent, const std::string &prefix)
{
    if (subRoot == nullptr)
        return;

    stream << indentWhitespace(indent) << prefix << subRoot->toString(" ") << '\n';

    if (subRoot->leftChild != nullptr)
        printSubtree(stream, subRoot->leftChild, indent + PRINT_NEST_INDENT, "L: ");
    if (subRoot->rightChild != nullptr)
        printSubtree(stream, subRoot->rightChild, indent + PRINT_NEST_INDENT, "R: ");
}

template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node *
BinarySearchTree<KeyType, ValueType>::findNode(const KeyType &key, BinarySearchTree<KeyType, ValueType>::Node *subRoot)
{
    if (subRoot == nullptr || subRoot->key == key)
        return subRoot;
    else if (subRoot->key < key)
        return findNode(key, subRoot->rightChild);
    else
        return findNode(key, subRoot->leftChild);
}


template<typename KeyType, typename ValueType>
ValueType *BinarySearchTree<KeyType, ValueType>::find(const KeyType &key)
{
    if (root == nullptr)
        return nullptr;

    BinarySearchTree<KeyType, ValueType>::Node **rootptr = &root;
    auto closest = findClosest(key, rootptr);
    if ((*closest)->key == key)
    {
        auto valptr = new ValueType;
        *valptr = (*closest)->value;
        return valptr;
    }
    return nullptr;
}

template<typename KeyType, typename ValueType>
std::string BinarySearchTree<KeyType, ValueType>::subTreeToString(BinarySearchTree<KeyType, ValueType>::Node *subRoot)
{
    if (subRoot == nullptr)
        return "";

    auto left = subTreeToString(subRoot->leftChild);
    auto right = subTreeToString(subRoot->rightChild);

    std::stringstream ss;
    ss << "(" << subRoot->toString() << "," << left << "," << right << ")";
    return ss.str();
}

template<typename KeyType, typename ValueType>
std::string BinarySearchTree<KeyType, ValueType>::toString() const
{
    return subTreeToString(root);
}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value)
{
    if (root == nullptr)
    {
        root = new BinarySearchTree<KeyType, ValueType>::Node(key, value);
        return;
    }

    BinarySearchTree<KeyType, ValueType>::Node **rootptr = &root;
    BinarySearchTree<KeyType, ValueType>::Node **closest = findClosest(key, rootptr);

    if ((*closest)->key == key)
        (*closest)->value = value;

    else if ((*closest)->key > key)
        (*closest)->leftChild = new BinarySearchTree<KeyType, ValueType>::Node(key, value);

    else
        (*closest)->rightChild = new BinarySearchTree<KeyType, ValueType>::Node(key, value);

}

template<typename KeyType, typename ValueType>
size_t BinarySearchTree<KeyType, ValueType>::size() const
{
    return sizeOfSubtree(root);
}

template<typename KeyType, typename ValueType>
std::ostream &operator<<(std::ostream &stream, BinarySearchTree<KeyType, ValueType> const &tree)
{
    tree.print(stream);
    return stream;
}
