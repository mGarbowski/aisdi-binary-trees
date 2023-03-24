#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>


/**
 * Generic implementation of AVL tree - self balancing binary search tree with unique keys.
 *
 * Tree maintains the invariant that each node has a balance factor (left child height - right child height)
 * in range [-1, 1] inclusive
 *
 * @tparam KeyType type of the keys
 * @tparam ValueType type of the values
 */
template<typename KeyType, typename ValueType>
class AVLTree {
private:

    /**
     * Node of an AVL tree
     *
     * Stores pointer to the node's parent
     *
     * @tparam KeyType type of keys used for comparison
     * @tparam ValueType type of values
     */
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        int height;
        AVLNode *leftChild;
        AVLNode *rightChild;
        AVLNode *parent;

        AVLNode();

        /**
         * Destroy node and its children recursively
         */
        ~AVLNode();

        /**
         * Initialize node with given parent
         *
         * @param key key
         * @param value value
         * @param parent node's parent node
         */
        AVLNode(KeyType key, ValueType const &value, AVLNode *parent = nullptr);

        /**
         * Difference of subtree heights (left - right)
         *
         * Value in range [-1, 1] (inclusive) corresponds to a balanced tree
         *
         * @return node's balance factor
         */
        int getBalance() const;

        /**
         * Default string representation of a node [<key>,<value>]
         *
         * @return string representation of a node [<key>,<value>]
         */
        std::string toString() const;

        /**
         * Utility for generating string representation with given separator after (like " ")
         * @param separator
         * @return
         */
        std::string toString(std::string const &separator) const;

        /**
         * Utility for accessing node's height, null safe
         *
         * @param node root node of a tree
         * @return height of the subtree with given root (0 for nullptr)
         */
        static int nodeHeight(AVLNode const *node);
    };

    /**
     * Root node of the tree
     */
    AVLNode *root;


    /**
     * Insert given key-value pair into subtree with subRoot as its root node
     *
     * @param key key to insert
     * @param value value to insert
     * @param subRoot root of the subtree to insert into
     */
    void insertIntoSubtree(KeyType const &key, ValueType const &value, AVLNode *subRoot);

    /**
     * Find value associated with key in subtree with subRoot as its root node
     * @param key searched key
     * @param subRoot root node of the scanned subtree
     * @return pointer to value associated with key or nullptr if not found
     */
    static ValueType *findInSubtree(KeyType const &key, AVLNode const *subRoot);


    /**
     * Restore AVL property of a subtree - each node has balance factor in range [-1, 1] (inclusive)
     *
     * @param insertedKey key from the most recent insertion that may have violated AVL property
     * @param subRoot root node of the tree to rebalance
     */
    void rebalance(KeyType const &insertedKey, AVLNode *subRoot);

    /**
     * Recursively print subtree on given indentation level
     *
     * @tparam StreamType type of the output stream
     * @param stream output stream
     * @param subRoot root node of the subtree to print
     * @param indent number of spaces
     * @param prefix prefix inserted before node (Left/Right)
     */
    template<typename StreamType>
    static void
    printSubtree(StreamType &stream, AVLNode const *subRoot, int indent, std::string const &prefix);

    /**
     * Return string representation of the subtree in pre-order traversal
     *
     * @param subRoot root node of the subtree
     * @return string representation in pre-order traversal
     */
    static std::string toStringSubtree(AVLNode const *subRoot);

    /**
     * Get number of elements stored in a subtree
     *
     * @param subRoot root node of the subtree
     * @return number of nodes in the subtree
     */
    size_t sizeSubtree(AVLNode const *subRoot) const;

    /**
     * Number of spaces per nesting level when displaying tree
     */
    static const auto PRINT_NEST_INDENT = 4;

    /**
     * Get string made of given number of spaces
     * utility for displaying trees
     *
     * @param spaces number of spaces
     * @return string made of given number of spaces
     */
    static std::string indentWhitespace(int spaces);

    /**
     * Perform right rotation of a subtree around given root node
     *
     * @param rotationRoot root node of the subtree to rotate
     * @return new root node of the subtree after rotation
     */
    static AVLNode *rotateRight(AVLNode *rotationRoot);

    /**
     * Perform left rotation of a subtree aroung given root node
     *
     * @param rotationRoot root node of the subtree to rotate
     * @return new root node of the subtree after rotation
     */
    static AVLNode *rotateLeft(AVLNode *rotationRoot);


public:

    /**
     * Initialize empty tree
     */
    AVLTree();

    /**
     * Destroy tree
     *
     * Destroys all nodes recursively
     */
    ~AVLTree();

    /**
     * Get number of elements stored in the tree
     *
     * @return number of elements stored in the tree
     */
    size_t size() const;

    /**
     * Insert key-value pair into the tree
     * If the key already exists, its corresponding value gets replaced
     * Maintains AVL property - each node has a balance factor in range [-1, 1] (inclusive)
     *
     * @param key key mapping to the value
     * @param value mapped value
     */
    void insert(KeyType const &key, ValueType const &value);

    /**
     * Find value related to the given key
     *
     * @param key key mapped to searched value
     * @return pointer to the value or nullptr if not found
     */
    ValueType *find(KeyType const &key) const;

    /**
     * String representation of the tree in pre-order traversal
     * @return pre-order traversal string
     */
    std::string toString() const;

    /**
     * Display tree (pre-order traversal) to a stream
     *
     * @tparam StreamType type of output stream
     * @param stream output stream
     */
    template<typename StreamType>
    void print(StreamType &stream) const;
};

template<typename KeyType, typename ValueType>
typename AVLTree<KeyType, ValueType>::AVLNode *AVLTree<KeyType, ValueType>::rotateLeft(AVLTree::AVLNode *rotationRoot) {
    auto rootParent = rotationRoot->parent;
    auto pivot = rotationRoot->rightChild;  // Always not null
    auto shiftedSubtree = pivot->leftChild;

    pivot->leftChild = rotationRoot;
    pivot->parent = rootParent;
    rotationRoot->parent = pivot;
    rotationRoot->rightChild = shiftedSubtree;

    if (shiftedSubtree != nullptr) {
        shiftedSubtree->parent = rotationRoot;
    }

    if (rootParent != nullptr) {
        if (rotationRoot == rootParent->leftChild) {
            rootParent->leftChild = pivot;
        } else {
            rootParent->rightChild = pivot;
        }
    }

    rotationRoot->height -= 2;
    return pivot;
}


template<typename KeyType, typename ValueType>
typename AVLTree<KeyType, ValueType>::AVLNode *AVLTree<KeyType, ValueType>::rotateRight(AVLNode *rotationRoot) {
    auto rootParent = rotationRoot->parent;
    auto pivot = rotationRoot->leftChild;  // Always not null
    auto shiftedSubtree = pivot->rightChild;

    pivot->rightChild = rotationRoot;
    pivot->parent = rootParent;
    rotationRoot->parent = pivot;
    rotationRoot->leftChild = shiftedSubtree;

    if (shiftedSubtree != nullptr) {
        shiftedSubtree->parent = rotationRoot;
    }

    if (rootParent != nullptr) {
        if (rotationRoot == rootParent->leftChild) {
            rootParent->leftChild = pivot;
        } else {
            rootParent->rightChild = pivot;
        }
    }

    rotationRoot->height -= 2;
    return pivot;
}


template<typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::~AVLTree() {
    delete root;
}


template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::rebalance(KeyType const &insertedKey, AVLNode *subRoot) {
    bool isRootRotation = (subRoot == root);
    int balance = subRoot->getBalance();

    if (balance > 1) {
        if (insertedKey < subRoot->leftChild->key) {
            subRoot = rotateRight(subRoot);  // left-left
        } else {
            rotateLeft(subRoot->leftChild);
            subRoot = rotateRight(subRoot);  // left-right
        }
    }

    if (balance < -1) {
        if (insertedKey > subRoot->rightChild->key) {
            subRoot = rotateLeft(subRoot);  // right-right
        } else {
            rotateRight(subRoot->rightChild);
            subRoot = rotateLeft(subRoot);  // right-left
        }
    }

    // Update tree's root if it changed due to rotations
    if (isRootRotation) {
        root = subRoot;
    }
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
size_t AVLTree<KeyType, ValueType>::sizeSubtree(const AVLNode *subRoot) const {
    if (subRoot == nullptr) {
        return 0;
    }

    auto left = sizeSubtree(subRoot->leftChild);
    auto right = sizeSubtree(subRoot->rightChild);
    return left + 1 + right;
}

template<typename KeyType, typename ValueType>
size_t AVLTree<KeyType, ValueType>::size() const {
    return sizeSubtree(root);
}

template<typename KeyType, typename ValueType>
void
AVLTree<KeyType, ValueType>::insertIntoSubtree(KeyType const &key, ValueType const &value,
                                               AVLNode *subRoot) {
    // Replace existing key, no need to rebalance
    if (key == subRoot->key) {
        subRoot->value = value;
        return;
    }

    // Insert recursively and rebalance if needed
    if (key < subRoot->key) {
        if (subRoot->leftChild == nullptr) {
            subRoot->leftChild = new AVLNode(key, value, subRoot);
        } else {
            insertIntoSubtree(key, value, subRoot->leftChild);
        }

    } else {
        if (subRoot->rightChild == nullptr) {
            subRoot->rightChild = new AVLNode(key, value, subRoot);
        } else {
            insertIntoSubtree(key, value, subRoot->rightChild);
        }
    }


    subRoot->height = 1 + std::max(
            AVLNode::nodeHeight(subRoot->leftChild),
            AVLNode::nodeHeight(subRoot->rightChild)
    );
    rebalance(key, subRoot);
}

template<typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    // Insert into empty list
    if (root == nullptr) {
        root = new AVLNode(key, value);
        return;
    }

    insertIntoSubtree(key, value, root);
}

template<typename KeyType, typename ValueType>
ValueType *
AVLTree<KeyType, ValueType>::findInSubtree(KeyType const &key, AVLNode const *subRoot) {
    if (subRoot == nullptr) {
        return nullptr;
    }

    if (key < subRoot->key) {
        return findInSubtree(key, subRoot->leftChild);
    } else if (key > subRoot->key) {
        return findInSubtree(key, subRoot->rightChild);
    } else {
        auto valuePtr = new ValueType();
        *valuePtr = subRoot->value;
        return valuePtr;
    }
}

template<typename KeyType, typename ValueType>
ValueType *AVLTree<KeyType, ValueType>::find(const KeyType &key) const {
    return findInSubtree(key, root);
}

template<typename KeyType, typename ValueType>
std::string AVLTree<KeyType, ValueType>::toStringSubtree(AVLNode const *subRoot) {
    if (subRoot == nullptr) {
        return "";
    }

    auto visit = subRoot->toString();
    auto left = toStringSubtree(subRoot->leftChild);
    auto right = toStringSubtree(subRoot->rightChild);

    std::ostringstream stringStream;
    stringStream << "(" << visit << "," << left << "," << right << ")";
    return stringStream.str();
}

template<typename KeyType, typename ValueType>
std::string AVLTree<KeyType, ValueType>::toString() const {
    return toStringSubtree(root);
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void
AVLTree<KeyType, ValueType>::printSubtree(StreamType &stream, AVLNode const *subRoot, int indent,
                                          std::string const &prefix) {
    if (subRoot == nullptr) {
        return;
    }
    stream << indentWhitespace(indent) << prefix << subRoot->toString(" ") << "\n";
    if (subRoot->leftChild != nullptr) {
        printSubtree(stream, subRoot->leftChild, indent + PRINT_NEST_INDENT, "L: ");
    }
    if (subRoot->rightChild != nullptr) {
        printSubtree(stream, subRoot->rightChild, indent + PRINT_NEST_INDENT, "R: ");
    }
}

template<typename KeyType, typename ValueType>
template<typename StreamType>
void AVLTree<KeyType, ValueType>::print(StreamType &stream) const {
    printSubtree(stream, root, 0, "");
}


template<typename KeyType, typename ValueType>
std::ostream &operator<<(std::ostream &stream, AVLTree<KeyType, ValueType> const &tree) {
    tree.print(stream);
    return stream;
}


template<typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::AVLNode::AVLNode() {
    height = 0;
}

template<typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::AVLNode::~AVLNode() {
    delete leftChild;
    delete rightChild;
}


template<typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::AVLNode::AVLNode(KeyType key, ValueType const &value, AVLNode *parent) {
    height = 1;
    this->parent = parent;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->key = key;
    this->value = value;
}

template<typename KeyType, typename ValueType>
int AVLTree<KeyType, ValueType>::AVLNode::getBalance() const {
    return nodeHeight(leftChild) - nodeHeight(rightChild);
}

template<typename KeyType, typename ValueType>
std::string AVLTree<KeyType, ValueType>::AVLNode::toString() const {
    return this->toString(std::string());
}

template<typename KeyType, typename ValueType>
std::string AVLTree<KeyType, ValueType>::AVLNode::toString(std::string const &separator) const {
    std::ostringstream stringStream;
    stringStream << "[" << key << "," << separator << value << "]";
    return stringStream.str();
}

template<typename KeyType, typename ValueType>
int AVLTree<KeyType, ValueType>::AVLNode::nodeHeight(AVLNode const *node) {
    if (node == nullptr) {
        return 0;
    }

    return node->height;
}