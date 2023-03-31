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

    std::string toString(std::string separator = "") const;

    int numOfChildren() const;

    /*
     * Used in the remove function to substitute the node if it has two children.
     * Returns the node with the largest key value from its left subtree.
     */
    BSTNode<KeyType, ValueType> *biggestNodeToTheLeft();

    BSTNode<KeyType, ValueType> *traverseRight();

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
std::string BSTNode<KeyType, ValueType>::toString(std::string separator) const
{
    std::stringstream ss;
    ss << "[" << key << "," << separator << value << "]";
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
}


template<typename KeyType, typename ValueType>
class BinarySearchTree
{
public:

    explicit BinarySearchTree(BSTNode<KeyType, ValueType> *root = nullptr) : root(root)
    {};

    BSTNode<KeyType, ValueType> *root;

    size_t size(BSTNode<KeyType, ValueType> *subRoot) const;

    static const auto PRINT_NEST_INDENT = 4;

    void insertIntoSubtree(KeyType const &key, ValueType const &value, BSTNode<KeyType, ValueType> *subRoot);

    void insert(KeyType const &key, ValueType const &value);

    void remove(KeyType const &key);

    ValueType *find(KeyType const &key);

    BSTNode<KeyType, ValueType> *findNode(KeyType const &key, BSTNode<KeyType, ValueType> *subRoot);

    ValueType *findInSubtree(KeyType const &key, BSTNode<KeyType, ValueType> *subRoot);

    std::string subTreeToString(BSTNode<KeyType, ValueType> *subRoot) const;

    std::string toString() const;

    void removeRoot();

    template<typename StreamType>
    void
    printSubtree(StreamType &stream, BSTNode<KeyType, ValueType> *subRoot, int indent, std::string const &prefix);

    std::string indentWhitespace(int width);

    template<typename StreamType>
    void print(StreamType &stream);
};

template<typename KeyType, typename ValueType>
template<typename StreamType>
void BinarySearchTree<KeyType, ValueType>::print(StreamType &stream)
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
void BinarySearchTree<KeyType, ValueType>::printSubtree(StreamType &stream, BSTNode<KeyType, ValueType> *subRoot,
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
void BinarySearchTree<KeyType, ValueType>::removeRoot()
{
    if (root->numOfChildren() == 0)
    {
        delete root;
        root = nullptr;
    } else if (root->numOfChildren() == 1)
    {
        if (root->rightChild != nullptr)
            root = root->rightChild;
        else
            root = root->leftChild;
    } else
    {
        auto newRoot = root->biggestNodeToTheLeft();

        if (newRoot->leftChild != nullptr)
        {
            newRoot->leftChild->parent = newRoot->parent;
            newRoot->parent->rightChild = newRoot->leftChild;
        }

        auto parentOfnewRoot = newRoot->parent;

        // delete the parent-child relationship
        if (parentOfnewRoot->rightChild == newRoot)
            parentOfnewRoot->rightChild = nullptr;
        else
            parentOfnewRoot->leftChild = nullptr;

        // move the children of the node to the new node
        newRoot->rightChild = root->rightChild;
        newRoot->leftChild = root->leftChild;

        // make the new node the parent of the current node's children
        root->rightChild->parent = newRoot;
        root->leftChild->parent = newRoot;

        // finally, set the children of the current root as none to avoid deleting them and delete the current root
        root->rightChild = nullptr;
        root->leftChild = nullptr;
        delete root;
    }

}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::remove(const KeyType &key)
{
    auto nodeToRemove = findNode(key, root);

    if (nodeToRemove == nullptr)
        return;


    if (nodeToRemove->parent != nullptr) // the node to be removed is not the root
    {
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
            // case - the node to be removed is its parent's right child
            if (parentOfRemovedNode->rightChild == nodeToRemove)
            {
                // subcase - the non-null child (the successor of the removed node) is on the right
                if (nodeToRemove->rightChild != nullptr)
                {
                    auto nonNullChild = nodeToRemove->rightChild;
                    nodeToRemove->rightChild = nullptr;
                    nonNullChild->parent = parentOfRemovedNode;
                    parentOfRemovedNode->rightChild = nonNullChild;
                } else // subcase - the successor is on the left
                {
                    auto nonNullChild = nodeToRemove->leftChild;
                    nodeToRemove->leftChild = nullptr;
                    nonNullChild->parent = parentOfRemovedNode;
                    parentOfRemovedNode->leftChild = nonNullChild;
                }
            } else
                // case - the node to be removed is the left child of its parent
            {
                if (nodeToRemove->rightChild != nullptr)
                    // successor on the right
                {
                    auto nonNullChild = nodeToRemove->rightChild;
                    nodeToRemove->rightChild = nullptr;
                    nonNullChild->parent = parentOfRemovedNode;
                    parentOfRemovedNode->leftChild = nonNullChild;
                } else // succesor on the left
                {
                    auto nonNullChild = nodeToRemove->leftChild;
                    nodeToRemove->leftChild = nullptr;
                    nonNullChild->parent = parentOfRemovedNode;
                    parentOfRemovedNode->leftChild = nonNullChild;
                }
            }
        } else
        {
            auto substitutionNode = nodeToRemove->biggestNodeToTheLeft();

            if (substitutionNode->leftChild != nullptr)
            {
                // case where the biggest node in the left subtree has smaller children
                substitutionNode->leftChild->parent = substitutionNode->parent;
                substitutionNode->parent->rightChild = substitutionNode->leftChild;
            }

            substitutionNode->parent = parentOfRemovedNode;

            if (parentOfRemovedNode->rightChild == nodeToRemove)
                parentOfRemovedNode->rightChild = substitutionNode;
            else
                parentOfRemovedNode->leftChild = substitutionNode;

            substitutionNode->rightChild = nodeToRemove->rightChild;
            substitutionNode->leftChild = nodeToRemove->leftChild;
            nodeToRemove->rightChild = nullptr;
            nodeToRemove->leftChild = nullptr;
            delete nodeToRemove;
        }
    } else
        removeRoot();
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
