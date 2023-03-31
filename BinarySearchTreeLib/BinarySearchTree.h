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
    BSTNode *leftChild;
    BSTNode *rightChild;
    BSTNode *parent;
    ValueType value;
    KeyType key;

    BSTNode(KeyType key, ValueType value, BSTNode *parent = nullptr);

    BSTNode();

    std::string toString() const;

    int numOfChildren() const;

    /*
     * Used in the remove function to substitute the node if it has two children.
     * Returns the node with the largest key value from its left subtree.
     */
    BSTNode<KeyType, ValueType> *biggestNodeToTheLeft();

    BSTNode<KeyType, ValueType> *traverseRight();


    size_t height;
};

template<typename KeyType, typename ValueType>
BSTNode<KeyType, ValueType>::BSTNode()
{
    leftChild = nullptr;
    rightChild = nullptr;
    parent = nullptr;
}

template<typename KeyType, typename ValueType>
BSTNode<KeyType, ValueType> *BSTNode<KeyType, ValueType>::traverseRight()
{
    if (rightChild == nullptr)
        return this;
    return rightChild->traverseRight();
}

template<typename KeyType, typename ValueType>
BSTNode<KeyType, ValueType> *BSTNode<KeyType, ValueType>::biggestNodeToTheLeft()
{
    return leftChild->traverseRight();
}

template<typename KeyType, typename ValueType>
int BSTNode<KeyType, ValueType>::numOfChildren() const
{
    int notNullChildren = 0;
    if (rightChild != nullptr)
        notNullChildren++;
    if (leftChild != nullptr)
        notNullChildren++;

    return notNullChildren;
}

template<typename KeyType, typename ValueType>
std::string BSTNode<KeyType, ValueType>::toString() const
{
    std::stringstream ss;
    ss << "[" << key << "," << value << "]";
    return ss.str();
}

template<typename KeyType, typename ValueType>
BSTNode<KeyType, ValueType>::BSTNode(KeyType key, ValueType value, BSTNode *parent)
{
    this->key = key;
    this->value = value;
    this->parent = parent;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 1;
}


template<typename KeyType, typename ValueType>
class BinarySearchTree
{
public:

    explicit BinarySearchTree(BSTNode<KeyType, ValueType> *root = nullptr) : root(root)
    {};

    BSTNode<KeyType, ValueType> *root;

    size_t size(BSTNode<KeyType, ValueType> *subRoot) const;

    void insertIntoSubtree(KeyType const &key, ValueType const &value, BSTNode<KeyType, ValueType> *subRoot);

    void insert(KeyType const &key, ValueType const &value);

    void remove(KeyType const &key);

    ValueType *find(KeyType const &key);

    BSTNode<KeyType, ValueType> *findNode(KeyType const &key, BSTNode<KeyType, ValueType> *subRoot);

    ValueType *findInSubtree(KeyType const &key, BSTNode<KeyType, ValueType> *subRoot);

    std::string subTreeToString(BSTNode<KeyType, ValueType> *subRoot) const;

    std::string toString() const;

    template<typename StreamType>
    void print(StreamType &stream) const;
};

//template<typename KeyType, typename ValueType>
//template<typename StreamType>
//void BinarySearchTree<KeyType, ValueType>::print(StreamType &stream) const
//{
//
//}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::remove(const KeyType &key)
{
    auto nodeToRemove = findNode(key, root);

    if (nodeToRemove == nullptr)
        return;


    auto parentOfRemovedNode = nodeToRemove->parent;
    if (nodeToRemove->numOfChildren() == 0)
    {
        if (parentOfRemovedNode->rightChild == nodeToRemove)
            parentOfRemovedNode->rightChild = nullptr;
        else
            parentOfRemovedNode->leftChild = nullptr;

        delete nodeToRemove;
    } else if (nodeToRemove->numOfChildren() == 1)
    {
        if (parentOfRemovedNode->rightChild == nodeToRemove)
        {
            if (nodeToRemove->rightChild != nullptr)
            {
                auto nonNullChild = nodeToRemove->rightChild;
                nodeToRemove->rightChild = nullptr;
                nonNullChild->parent = parentOfRemovedNode;
                parentOfRemovedNode->rightChild = nonNullChild;
            } else
            {
                auto nonNullChild = nodeToRemove->leftChild;
                nodeToRemove->leftChild = nullptr;
                nonNullChild->parent = parentOfRemovedNode;
                parentOfRemovedNode->rightChild = nonNullChild;
            }
        }
    } else
    {
        auto substitutionNode = root->biggestNodeToTheLeft();
        substitutionNode->parent = parentOfRemovedNode;

        if (parentOfRemovedNode->rightChild == nodeToRemove)
        {
            parentOfRemovedNode->rightChild = substitutionNode;

            auto rightChildPtr = new BSTNode<KeyType, ValueType>;
            *rightChildPtr = *(nodeToRemove->rightChild);

            substitutionNode->rightChild = rightChildPtr;
            nodeToRemove->rightChild = nullptr;
            nodeToRemove->leftChild = nullptr;
            delete nodeToRemove;
        } else
        {
            parentOfRemovedNode->leftChild = substitutionNode;

            auto leftChildPtr = new BSTNode<KeyType, ValueType>;
            *leftChildPtr = *(nodeToRemove->rightChild);

            substitutionNode->leftChild = leftChildPtr;
            nodeToRemove->rightChild = nullptr;
            nodeToRemove->leftChild = nullptr;
            delete nodeToRemove;
        }
    }
}

template<typename KeyType, typename ValueType>
BSTNode<KeyType, ValueType> *
BinarySearchTree<KeyType, ValueType>::findNode(const KeyType &key, BSTNode<KeyType, ValueType> *subRoot)
{
    if (subRoot == nullptr || subRoot->key == key)
        return subRoot;
    else if (subRoot->key < key)
        return findNode(key, subRoot->rightChild);
    return findNode(key, subRoot->leftChild);
}


template<typename KeyType, typename ValueType>
ValueType *BinarySearchTree<KeyType, ValueType>::find(const KeyType &key)
{
    return findInSubtree(key, root);
}

template<typename KeyType, typename ValueType>
std::string BinarySearchTree<KeyType, ValueType>::subTreeToString(BSTNode<KeyType, ValueType> *subRoot) const
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
ValueType *BinarySearchTree<KeyType, ValueType>::findInSubtree(const KeyType &key, BSTNode<KeyType, ValueType> *subRoot)
{
    if (subRoot == nullptr)
        return nullptr;

    else if (subRoot->key == key)
    {
        auto valPtr = new ValueType;
        *valPtr = subRoot->value;
        return valPtr;
    } else if (subRoot->key > key)
        return findInSubtree(key, subRoot->leftChild);

    return findInSubtree(key, subRoot->rightChild);
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
void BinarySearchTree<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value)
{
    if (root == nullptr)
    {
        root = new BSTNode<KeyType, ValueType>(key, value);
        return;
    }
    insertIntoSubtree(key, value, root);
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
