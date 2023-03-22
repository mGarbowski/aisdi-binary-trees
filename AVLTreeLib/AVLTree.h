#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>

template<typename KeyType, typename ValueType>
class AVLNode {
public:
    KeyType key;
    ValueType *value;
    int balanceCoefficient;
    AVLNode *leftChild;
    AVLNode *rightChild;
    AVLNode *parent;

    AVLNode(KeyType key, const ValueType &value);

    AVLNode(KeyType key, const ValueType &value, AVLNode *parent);

    std::string toString() const;
};

template<typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType>::AVLNode(KeyType key, const ValueType &value) {
    this->key = key;
    auto* valuePtr = new ValueType();
    *valuePtr = value;
    this->value = valuePtr;
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
    balanceCoefficient = 0;
}

template<typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType>::AVLNode(KeyType key, const ValueType &value, AVLNode *parent) {
    this->key = key;
    auto* valuePtr = new ValueType();
    *valuePtr = value;
    this->value = valuePtr;
    this->parent = parent;
    leftChild = nullptr;
    rightChild = nullptr;
    balanceCoefficient = 0;
}

template<typename KeyType, typename ValueType>
std::string AVLNode<KeyType, ValueType>::toString() const {
    std::ostringstream stringStream;
    stringStream << "[" << key << "," << *value << "]";
    return stringStream.str();
}


template<typename KeyType, typename ValueType>
class AVLTree {
private:
    AVLNode<KeyType, ValueType> *root;

    AVLTree<KeyType, ValueType> leftSubtree() const;

    AVLTree<KeyType, ValueType> rightSubtree() const;

public:
    AVLTree();

    explicit AVLTree(AVLNode<KeyType, ValueType> *root);

    size_t size() const;

    void insert(KeyType const &key, ValueType const &value);  // Should not calculate height

    ValueType *find(KeyType const &key);

    std::string toString() const;

    template<typename StreamType>
    void print(StreamType &stream) const;
};


template<typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::AVLTree() {
    root = nullptr;
}

template<typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::AVLTree(AVLNode<KeyType, ValueType> *root) {
    this->root = root;
}

template<typename KeyType, typename ValueType>
size_t AVLTree<KeyType, ValueType>::size() const {
    return 0;
}

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    // Insert into empty list
    if (root == nullptr) {
        root = new AVLNode<KeyType, ValueType>(key, value);
        return;
    }

    // Replace key
    if (key == root->key) {
        auto v = root->value;
        *v = value;

    } else if (key < root->key) {
        if (root->leftChild == nullptr) {
            root->leftChild = new AVLNode<KeyType, ValueType>(key, value, root);
        } else {
            this->leftSubtree().insert(key, value);
        }
        root->balanceCoefficient++;

    } else {
        if (root->rightChild == nullptr) {
            root->rightChild = new AVLNode<KeyType, ValueType>(key, value, root);
        } else {
            this->rightSubtree().insert(key, value);
        }
        root->balanceCoefficient--;
    }
}

template<typename KeyType, typename ValueType>
ValueType *AVLTree<KeyType, ValueType>::find(const KeyType &key) {
    if (root == nullptr) {
        return nullptr;
    }

    if (key == root->key) {
        return root->value;
    } else if (key < root->key) {
        return this->leftSubtree().find(key);
    } else {
        return this->rightSubtree().find(key);
    }
}

template<typename KeyType, typename ValueType>
std::string AVLTree<KeyType, ValueType>::toString() const {
    if (root == nullptr) {
        return "";
    }
    std::ostringstream stringStream;
    auto visit = root->toString();
    auto left = this->leftSubtree().toString();
    auto right = this->rightSubtree().toString();
    stringStream << "(" << visit << "," << left << "," << right << ")";
    return stringStream.str();
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void AVLTree<KeyType, ValueType>::print(StreamType &stream) const {

}

template<typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType> AVLTree<KeyType, ValueType>::leftSubtree() const {
    return AVLTree<KeyType, ValueType>(root->leftChild);
}

template<typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType> AVLTree<KeyType, ValueType>::rightSubtree() const {
    return AVLTree<KeyType, ValueType>(root->rightChild);
}


template<typename KeyType, typename ValueType>
std::ostream &operator<<(std::ostream &stream, AVLTree<KeyType, ValueType> const &tree) {
    tree.print(stream);
    return stream;
}
