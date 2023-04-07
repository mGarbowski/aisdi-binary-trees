#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>


template<typename KeyType, typename ValueType>
class BinarySearchTree
{
private:
    class Node
    {
    public:
        Node *leftChild;
        Node *rightChild;
        Node *parent;
        ValueType value;
        KeyType key;


        Node(KeyType key, ValueType value, Node *parent = nullptr);

        ~Node();

        std::string toString(std::string separator = "") const;

        int numOfChildren() const;

        /*
         * Used in the remove function to substitute the node if it has two children.
         * Returns the node with the largest key value from its left subtree.
         */

        Node *biggestNodeToTheLeft() const;

        Node *traverseRight();

    };

    BinarySearchTree<KeyType, ValueType>::Node *root;

    void removeRoot();

    static const auto PRINT_NEST_INDENT = 4;

    static BinarySearchTree<KeyType, ValueType>::Node *
    findNode(KeyType const &key, BinarySearchTree<KeyType, ValueType>::Node *subRoot);

    static void
    insertIntoSubtree(KeyType const &key, ValueType const &value, BinarySearchTree<KeyType, ValueType>::Node *subRoot);

    static std::string subTreeToString(BinarySearchTree<KeyType, ValueType>::Node *subRoot);

    static ValueType *findInSubtree(KeyType const &key, BinarySearchTree<KeyType, ValueType>::Node *subRoot);

    template<typename StreamType>
    static void printSubtree(StreamType &stream, BinarySearchTree<KeyType, ValueType>::Node *subRoot, int indent,
                             std::string const &prefix);

    static std::string indentWhitespace(int width);

    size_t sizeOfSubtree(BinarySearchTree<KeyType, ValueType>::Node *subRoot) const;

public:

    BinarySearchTree();

    ~BinarySearchTree();

    size_t size() const;

    Node **find_closest(KeyType const &key, BinarySearchTree<KeyType, ValueType>::Node **starting_point);

    void insert(KeyType const &key, ValueType const &value);

    void remove(KeyType const &key);

    ValueType *find(KeyType const &key);

    std::string toString() const;

    template<typename StreamType>
    void print(StreamType &stream) const;
};

template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::Node **BinarySearchTree<KeyType, ValueType>::find_closest(const KeyType &key,
                                                                                                BinarySearchTree<KeyType, ValueType>::Node **starting_point)
{
    Node **current_closest = starting_point;

    if (*current_closest->key == key)
    {
        return current_closest;
    }
    else if (*current_closest->key > key && *current_closest->leftChild != nullptr)
    {
            *current_closest = *current_closest->leftChild;
            return find_closest(key, current_closest);
    }
    else if (*current_closest->key < key && *current_closest->rightChild != nullptr)
        {
            *current_closest = *current_closest->rightChild;
            return find_closest(key, current_closest);
        }
    else
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
typename BinarySearchTree<KeyType, ValueType>::Node *BinarySearchTree<KeyType, ValueType>::Node::traverseRight()
{
    if (rightChild == nullptr)
        return this;
    return rightChild->traverseRight();
}

template<typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node *
BinarySearchTree<KeyType, ValueType>::Node::biggestNodeToTheLeft() const
{
    return leftChild->traverseRight();
}

template<typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::Node::numOfChildren() const
{
    int notNullChildren = 0;
    if (rightChild != nullptr)
        notNullChildren++;
    if (leftChild != nullptr)
        notNullChildren++;

    return notNullChildren;
}

template<typename KeyType, typename ValueType>
std::string BinarySearchTree<KeyType, ValueType>::Node::toString(std::string separator) const
{
    std::stringstream ss;
    ss << "[" << key << "," << separator << value << "]";
    return ss.str();
}

template<typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::Node::Node(KeyType key, ValueType value, Node *parent)
{
    this->key = key;
    this->value = value;
    this->parent = parent;
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
void BinarySearchTree<KeyType, ValueType>::removeRoot()
{
    if (root->numOfChildren() == 0)
    {
        delete root;
        root = nullptr;
    } else if (root->numOfChildren() == 1)
    {
        if (root->rightChild != nullptr)
        {
            auto newRoot = root->rightChild;
            root->rightChild = nullptr;
            delete root;
            newRoot->parent = nullptr;
            root = newRoot;
        } else
        {
            auto newRoot = root->leftChild;
            root->leftChild = nullptr;
            delete root;
            newRoot->parent = nullptr;
            root = newRoot;
        }

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
        newRoot->parent = nullptr;
        root = newRoot;
    }

}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::remove(const KeyType &key)
{
    auto nodeToRemove = findNode(key, root);

    if (nodeToRemove == nullptr)
        return;


    if (nodeToRemove->parent == nullptr)
    {
        removeRoot();
        return;
    }

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
            } else
            {
                // subcase - the successor is on the left
                auto nonNullChild = nodeToRemove->leftChild;
                nodeToRemove->leftChild = nullptr;
                nonNullChild->parent = parentOfRemovedNode;
                parentOfRemovedNode->rightChild = nonNullChild;
            }
        } else
        {
            // case - the node to be removed is the left child of its parent
            if (nodeToRemove->rightChild != nullptr)
            {
                // successor on the right
                auto nonNullChild = nodeToRemove->rightChild;
                nodeToRemove->rightChild = nullptr;
                nonNullChild->parent = parentOfRemovedNode;
                parentOfRemovedNode->leftChild = nonNullChild;
            } else
            {
                // succesor on the left
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
    return findInSubtree(key, root);
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
ValueType *BinarySearchTree<KeyType, ValueType>::findInSubtree(const KeyType &key,
                                                               BinarySearchTree<KeyType, ValueType>::Node *subRoot)
{
    if (subRoot == nullptr)
    {
        return nullptr;
    }
    if (subRoot->key == key)
    {
        auto valPtr = new ValueType;
        *valPtr = subRoot->value;
        return valPtr;
    }

    if (subRoot->key > key)
    {
        return findInSubtree(key, subRoot->leftChild);
    } else
    {
        return findInSubtree(key, subRoot->rightChild);
    }
}

template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::insertIntoSubtree(const KeyType &key, const ValueType &value,
                                                             BinarySearchTree<KeyType, ValueType>::Node *subRoot)
{
    if (subRoot->key == key)
    {
        subRoot->value = value;
    } else if (subRoot->key < key)
    {
        if (subRoot->rightChild == nullptr)
            subRoot->rightChild = new BinarySearchTree<KeyType, ValueType>::Node(key, value, subRoot);
        else
            insertIntoSubtree(key, value, subRoot->rightChild);
    } else
    {
        if (subRoot->leftChild == nullptr)
            subRoot->leftChild = new BinarySearchTree<KeyType, ValueType>::Node(key, value, subRoot);
        else
            insertIntoSubtree(key, value, subRoot->leftChild);
    }
}


template<typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value)
{
    if (root == nullptr)
    {
        root = new BinarySearchTree<KeyType, ValueType>::Node(key, value);
        return;
    }
    insertIntoSubtree(key, value, root);
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
