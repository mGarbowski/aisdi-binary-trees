#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "../BinarySearchTreeLib/BinarySearchTree.h"

class Key {
private:
    static unsigned long long cmpCount;
    unsigned long value = 0UL;
public:
    static void resetCounter() {
        cmpCount = 0ULL;
    }

    static unsigned long long getCmpCount() {
        return cmpCount;
    }

    Key() = default;

    Key(Key const &) = default;

    Key(unsigned long v) : value(v) {
    }

    unsigned long getKey() const {
        return value;
    }

    bool operator==(Key const &v) const {
        ++cmpCount;
        return value == v.value;
    }

    bool operator!=(Key const &v) const {
        ++cmpCount;
        return value != v.value;
    }

    bool operator<(Key const &v) const {
        ++cmpCount;
        return value < v.value;
    }

    bool operator<=(Key const &v) const {
        ++cmpCount;
        return value <= v.value;
    }

    bool operator>(Key const &v) const {
        ++cmpCount;
        return value > v.value;
    }

    bool operator>=(Key const &v) const {
        ++cmpCount;
        return value >= v.value;
    }
};

unsigned long long Key::cmpCount = 0ULL;

std::ostream &operator<<(std::ostream &stream, Key const &key) {
    stream << key.getKey();
    return stream;
}

namespace std {
    std::string to_string(Key const &k) {
        return std::to_string(k.getKey());
    }
}

int main() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator((unsigned long) seed);

    size_t size;
    do {
        std::cout << "Enter size:";
        std::cin >> size;
        if (size > 0) {
            BinarySearchTree<Key, unsigned long> tree;
            while (tree.size() < size) {
                unsigned long n = generator();

                Key key(n);

                tree.insert(key, n);
            }
            if (tree.size() <= 100)
                std::cout << tree;

            Key::resetCounter();
            unsigned int i;
            for (i = 0; i < 10; ++i) {
                unsigned long n = generator();
                Key key(n);
                tree.find(Key(key));
            }
            std::cout << "Cmp count: " << Key::getCmpCount() / i << "\n";
        }
    } while (size > 0);
    return 0;
}
