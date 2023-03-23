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
    int height;
    AVLNode *leftChild;
    AVLNode *rightChild;
    AVLNode *parent;

    AVLNode(KeyType key, const ValueType &value);

    AVLNode(KeyType key, const ValueType &value, AVLNode *parent);

    int getBalance() const;

    std::string toString() const;

    std::string toString(std::string separator) const;

    static int nodeHeight(AVLNode<KeyType, ValueType> *node);
};

template<typename KeyType, typename ValueType>
int AVLNode<KeyType, ValueType>::nodeHeight(AVLNode<KeyType, ValueType> *node) {
    if (node == nullptr) {
        return 0;
    }

    return node->height;
}

template<typename KeyType, typename ValueType>
int AVLNode<KeyType, ValueType>::getBalance() const {
    return nodeHeight(leftChild) - nodeHeight(rightChild);
}

template<typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType>::AVLNode(KeyType key, const ValueType &value) {
    this->key = key;
    auto *valuePtr = new ValueType();
    *valuePtr = value;
    this->value = valuePtr;
    parent = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 1;
}

template<typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType>::AVLNode(KeyType key, const ValueType &value, AVLNode *parent) {
    this->key = key;
    auto *valuePtr = new ValueType();
    *valuePtr = value;
    this->value = valuePtr;
    this->parent = parent;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 1;
}

template<typename KeyType, typename ValueType>
std::string AVLNode<KeyType, ValueType>::toString() const {
    return this->toString(std::string());
}

template<typename KeyType, typename ValueType>
std::string AVLNode<KeyType, ValueType>::toString(std::string separator) const {
    std::ostringstream stringStream;
    stringStream << "[" << key << "," << separator << *value << "]";
    return stringStream.str();
}


template<typename KeyType, typename ValueType>
class AVLTree {
private:
    static const auto PRINT_NEST_INDENT = 4;

    AVLNode<KeyType, ValueType> *root;

    explicit AVLTree(AVLNode<KeyType, ValueType> *root);

    AVLTree<KeyType, ValueType> leftSubtree() const;

    AVLTree<KeyType, ValueType> rightSubtree() const;

    template<typename StreamType>
    void print(StreamType &stream, int indent, std::string prefix) const;

    static std::string indentWhitespace(int spaces);

    static AVLNode<KeyType, ValueType> *rotateRight(AVLNode<KeyType, ValueType> *rotationRoot);
    static AVLNode<KeyType, ValueType> *rotateLeft(AVLNode<KeyType, ValueType> *rotationRoot);
    void rebalance(KeyType insertedKey);

public:

    AVLTree();

    size_t size() const;

    void insert(KeyType const &key, ValueType const &value);  // Should not calculate height

    ValueType *find(KeyType const &key);

    std::string toString() const;

    template<typename StreamType>
    void print(StreamType &stream) const;
};

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::rebalance(KeyType insertedKey) {
    int balance = root->getBalance();

    if (balance > 1) {
        if (insertedKey < root->leftChild->key) {
            root = rotateRight(root);  // left-left
        } else {
            root->leftChild = rotateLeft(root->leftChild);
            root = rotateRight(root);  // left-right
        }
    }

    if (balance < -1) {
        if (insertedKey > root->rightChild->key) {
            root = rotateLeft(root);  // right-right
        } else {
            root->rightChild = rotateRight(root->rightChild);
            root = rotateLeft(root);  // right-left
        }
    }
}

template<typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::rotateLeft(AVLNode<KeyType, ValueType> *rotationRoot) {
    auto pivot = rotationRoot->rightChild;
    auto shiftedSubtree = pivot->leftChild;
    pivot->leftChild = rotationRoot;
    rotationRoot->rightChild = shiftedSubtree;
    return pivot;
}

template<typename KeyType, typename ValueType>
AVLNode<KeyType, ValueType> *AVLTree<KeyType, ValueType>::rotateRight(AVLNode<KeyType, ValueType> *rotationRoot) {
    auto pivot = rotationRoot->leftChild;  // Always not null
    auto shiftedSubtree = pivot->rightChild;
    pivot->rightChild = rotationRoot;
    rotationRoot->leftChild = shiftedSubtree;
    return pivot;
}


template<typename KeyType, typename ValueType>
std::string AVLTree<KeyType, ValueType>::indentWhitespace(int spaces) {
    std::ostringstream ss;
    for (int i = 0; i < spaces; ++i) {
        ss << " ";
    }
    return ss.str();
}

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
    if (root == nullptr) {
        return 0;
    }

    auto left = this->leftSubtree().size();
    auto right = this->rightSubtree().size();
    return left + 1 + right;
}

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    // Insert into empty list
    if (root == nullptr) {
        root = new AVLNode<KeyType, ValueType>(key, value);
        return;
    }

    // Replace existing key, no need to rebalance
    if (key == root->key) {
        auto v = root->value;
        *v = value;
        return;
    }

    // Insert recursively and rebalance if needed
    if (key < root->key) {
        if (root->leftChild == nullptr) {
            root->leftChild = new AVLNode<KeyType, ValueType>(key, value, root);
        } else {
            this->leftSubtree().insert(key, value);
        }

    } else {
        if (root->rightChild == nullptr) {
            root->rightChild = new AVLNode<KeyType, ValueType>(key, value, root);
        } else {
            this->rightSubtree().insert(key, value);
        }
    }


    root->height = 1 + std::max(
            AVLNode<KeyType, ValueType>::nodeHeight(root->leftChild),
            AVLNode<KeyType, ValueType>::nodeHeight(root->rightChild)
    );
    rebalance(key);
}

template<typename KeyType, typename ValueType>
ValueType *AVLTree<KeyType, ValueType>::find(const KeyType &key) {
    if (root == nullptr) {
        return nullptr;
    }

    if (key < root->key) {
        return this->leftSubtree().find(key);
    } else if (key > root->key) {
        return this->rightSubtree().find(key);
    } else {
        return root->value;
    }
}

template<typename KeyType, typename ValueType>
std::string AVLTree<KeyType, ValueType>::toString() const {
    if (root == nullptr) {
        return "";
    }

    auto visit = root->toString();
    auto left = this->leftSubtree().toString();
    auto right = this->rightSubtree().toString();

    std::ostringstream stringStream;
    stringStream << "(" << visit << "," << left << "," << right << ")";
    return stringStream.str();
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void AVLTree<KeyType, ValueType>::print(StreamType &stream) const {
    this->print(stream, 0, "");
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void AVLTree<KeyType, ValueType>::print(StreamType &stream, int indent, std::string prefix) const {
    if (root == nullptr) {
        return;
    }
    stream << indentWhitespace(indent) << prefix << root->toString(" ") << "\n";
    if (root->leftChild != nullptr) {
        this->leftSubtree().print(stream, indent + PRINT_NEST_INDENT, "L: ");
    }
    if (root->rightChild != nullptr) {
        this->rightSubtree().print(stream, indent + PRINT_NEST_INDENT, "R: ");
    }
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
