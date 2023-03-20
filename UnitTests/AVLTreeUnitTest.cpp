#include <gtest/gtest.h>
#include "../AVLTreeLib/AVLTree.h"


namespace AVLTreeUnitTest {

    TEST(AVLTree, leftRootRotationAfterInsert) {
        AVLTree<int, int> tree;
        tree.insert(10, 10);
        tree.insert(20, 20);
        std::string expected = "([10,10],,([20,20],,))";
        ASSERT_EQ(expected, tree.toString());
        tree.insert(30, 30);
        expected = "([20,20],([10,10],,),([30,30],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, leftRotationAfterInsert) {
        AVLTree<int, int> tree;
        tree.insert(60, 60);
        tree.insert(20, 20);
        tree.insert(70, 70);
        tree.insert(10, 10);
        tree.insert(30, 30);
        tree.insert(80, 80);
        tree.insert(25, 25);
        tree.insert(40, 40);
        std::string expected = "([60,60],([20,20],([10,10],,),([30,30],([25,25],,),([40,40],,))),([70,70],,([80,80],,)))";
        ASSERT_EQ(expected, tree.toString());
        tree.insert(50, 50);
        expected = "([60,60],([30,30],([20,20],([10,10],,),([25,25],,)),([40,40],,([50,50],,))),([70,70],,([80,80],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, rightLeftRootRotationAfterInsert) {
        AVLTree<int, int> tree;
        tree.insert(10, 10);
        tree.insert(30, 30);
        std::string expected = "([10,10],,([30,30],,))";
        ASSERT_EQ(expected, tree.toString());
        tree.insert(20, 20);
        expected = "([20,20],([10,10],,),([30,30],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, rightLeftRotationAfterInsert) {
        AVLTree<int, int> tree;
        tree.insert(60, 60);
        tree.insert(20, 20);
        tree.insert(70, 70);
        tree.insert(10, 10);
        tree.insert(30, 30);
        tree.insert(80, 80);
        tree.insert(25, 25);
        tree.insert(40, 40);
        std::string expected = "([60,60],([20,20],([10,10],,),([30,30],([25,25],,),([40,40],,))),([70,70],,([80,80],,)))";
        ASSERT_EQ(expected, tree.toString());
        tree.insert(22, 22);
        expected = "([60,60],([25,25],([20,20],([10,10],,),([22,22],,)),([30,30],,([40,40],,))),([70,70],,([80,80],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, rightRootRotationAfterInsert) {
        AVLTree<int, int> tree;
        tree.insert(30, 30);
        tree.insert(20, 20);
        std::string expected = "([30,30],([20,20],,),)";
        ASSERT_EQ(expected, tree.toString());
        tree.insert(10, 10);
        expected = "([20,20],([10,10],,),([30,30],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, rightRotationAfterInsert) {
        AVLTree<int, int> tree;
        tree.insert(30, 30);
        tree.insert(20, 20);
        tree.insert(80, 80);
        tree.insert(10, 10);
        tree.insert(60, 60);
        tree.insert(90, 90);
        tree.insert(50, 50);
        tree.insert(70, 70);
        std::string expected = "([30,30],([20,20],([10,10],,),),([80,80],([60,60],([50,50],,),([70,70],,)),([90,90],,)))";
        ASSERT_EQ(expected, tree.toString());
        tree.insert(40, 40);
        expected = "([30,30],([20,20],([10,10],,),),([60,60],([50,50],([40,40],,),),([80,80],([70,70],,),([90,90],,))))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, leftRightRootRotationAfterInsert) {
        AVLTree<int, int> tree;
        tree.insert(30, 30);
        tree.insert(10, 10);
        std::string expected = "([30,30],([10,10],,),)";
        ASSERT_EQ(expected, tree.toString());
        tree.insert(20, 20);
        expected = "([20,20],([10,10],,),([30,30],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, leftRightRotationAfterInsert) {
        AVLTree<int, int> tree;
        tree.insert(30, 30);
        tree.insert(20, 20);
        tree.insert(80, 80);
        tree.insert(10, 10);
        tree.insert(50, 50);
        tree.insert(90, 90);
        tree.insert(40, 40);
        tree.insert(60, 60);
        std::string expected = "([30,30],([20,20],([10,10],,),),([80,80],([50,50],([40,40],,),([60,60],,)),([90,90],,)))";
        ASSERT_EQ(expected, tree.toString());
        tree.insert(70, 70);
        expected = "([30,30],([20,20],([10,10],,),),([60,60],([50,50],([40,40],,),),([80,80],([70,70],,),([90,90],,))))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, ConstructEmpty) {
        AVLTree<int, int> tree;
        std::string expected = "";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertToEmpty) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        std::string expected = "([10,100],,)";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe2LevelOnTheLeftThereIsNoRight) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        std::string expected = "([10,100],([5,50],,),)";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe2LevelOnTheRightThereIsNoLeft) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        std::string expected = "([10,100],,([20,200],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe2LevelOnTheLeftThereIsRight) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        tree.insert(5, 50);
        std::string expected = "([10,100],([5,50],,),([20,200],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe2LevelOnTheRightThereIsLeft) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        tree.insert(20, 200);
        std::string expected = "([10,100],([5,50],,),([20,200],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe3LevelLeftLeftThereIsNoRight) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        std::string expected = "([50,500],([20,200],([10,100],,),),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe3LevelLeftLeftThereIsRight) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        tree.insert(10, 100);
        std::string expected = "([50,500],([20,200],([10,100],,),([30,300],,)),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe3LevelLeftRightThereIsNoLeft) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        std::string expected = "([50,500],([20,200],,([30,300],,)),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe3LevelLeftRightThereIsLeft) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        tree.insert(30, 300);
        std::string expected = "([50,500],([20,200],([10,100],,),([30,300],,)),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe3LevelRightLeftThereIsNoRight) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe3LevelRightLeftThereIsRight) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(90, 900);
        tree.insert(70, 700);
        std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),([90,900],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe3LevelRightRightThereIsNoLeft) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(90, 900);
        std::string expected = "([50,500],([20,200],,),([80,800],,([90,900],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertOnThe3LevelRightRightThereIsLeft) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        tree.insert(90, 900);
        std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),([90,900],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, insertExisting) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        tree.insert(90, 900);
        tree.insert(50, 501);
        tree.insert(20, 201);
        tree.insert(80, 801);
        tree.insert(70, 701);
        tree.insert(90, 901);
        std::string expected = "([50,501],([20,201],,),([80,801],([70,701],,),([90,901],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(AVLTree, findInEmpty) {
        AVLTree<int, int> tree;
        ASSERT_EQ(nullptr, tree.find(10));
    }

    TEST(AVLTree, findNotExisted) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        tree.insert(20, 200);
        ASSERT_EQ(nullptr, tree.find(2));
        ASSERT_EQ(nullptr, tree.find(7));
        ASSERT_EQ(nullptr, tree.find(12));
        ASSERT_EQ(nullptr, tree.find(24));
    }

    TEST(AVLTree, findOnThe1LevelNoChildren) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        ASSERT_EQ(100, *tree.find(10));
        tree.insert(5, 50);
        ASSERT_EQ(100, *tree.find(10));
        tree.insert(20, 200);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(AVLTree, findOnThe1LevelIsLeftChild) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(AVLTree, findOnThe1LevelIsRightChild) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(AVLTree, findOnThe1LevelAreChildren) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        tree.insert(20, 200);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(AVLTree, findOnThe2LevelOnTheLeftThereIsNoRight) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        ASSERT_EQ(50, *tree.find(5));
    }

    TEST(AVLTree, findOnThe2LevelOnTheRightThereIsNoLeft) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        ASSERT_EQ(200, *tree.find(20));
    }

    TEST(AVLTree, findOnThe2LevelOnTheLeftThereIsRight) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        tree.insert(5, 50);
        ASSERT_EQ(50, *tree.find(5));
    }

    TEST(AVLTree, findOnThe2LevelOnTheRightThereIsLeft) {
        AVLTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        tree.insert(20, 200);
        ASSERT_EQ(200, *tree.find(20));
    }

    TEST(AVLTree, findOnThe3LevelLeftLeftThereIsNoRight) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(AVLTree, findOnThe3LevelLeftLeftThereIsRight) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        tree.insert(10, 100);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(AVLTree, findOnThe3LevelLeftRightThereIsNoLeft) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        ASSERT_EQ(300, *tree.find(30));
    }

    TEST(AVLTree, findOnThe3LevelLeftRightThereIsLeft) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        tree.insert(30, 300);
        ASSERT_EQ(300, *tree.find(30));
    }

    TEST(AVLTree, findOnThe3LevelRightLeftThereIsNoRight) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        ASSERT_EQ(700, *tree.find(70));
    }

    TEST(AVLTree, findOnThe3LevelRightLeftThereIsRight) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(90, 900);
        tree.insert(70, 700);
        ASSERT_EQ(700, *tree.find(70));
    }

    TEST(AVLTree, findOnThe3LevelRightRightThereIsNoLeft) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(90, 900);
        ASSERT_EQ(900, *tree.find(90));
    }

    TEST(AVLTree, findOnThe3LevelRightRightThereIsLeft) {
        AVLTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        tree.insert(90, 900);
        ASSERT_EQ(900, *tree.find(90));
    }

    TEST(AVLTree, print0) {
        AVLTree<int, int> tree;
        std::ostringstream stream;
        tree.print(stream);
        auto s = stream.str();
        std::string s1 = "";
        ASSERT_EQ(s1, s);
    }

    TEST(AVLTree, print1) {
        AVLTree<int, int> tree;
        tree.insert(1, 1);
        std::ostringstream stream;
        tree.print(stream);
        auto s = stream.str();
        std::string s1 = "[1, 1]\n";
        ASSERT_EQ(s1, s);
    }

    TEST(AVLTree, print3) {
        AVLTree<int, int> tree;
        tree.insert(2, 2);
        tree.insert(1, 1);
        tree.insert(3, 3);
        std::ostringstream stream;
        tree.print(stream);
        auto s = stream.str();
        std::string s1 = "[2, 2]\n    L: [1, 1]\n    R: [3, 3]\n";
        ASSERT_EQ(s1, s);
    }

    TEST(AVLTree, print7) {
        AVLTree<int, int> tree;
        tree.insert(4, 4);
        tree.insert(2, 2);
        tree.insert(1, 1);
        tree.insert(3, 3);
        tree.insert(6, 6);
        tree.insert(5, 5);
        tree.insert(7, 7);

        std::ostringstream stream;
        tree.print(stream);
        auto s = stream.str();
        std::string s1 = "[4, 4]\n    L: [2, 2]\n        L: [1, 1]\n        R: [3, 3]\n    R: [6, 6]\n        L: [5, 5]\n        R: [7, 7]\n";
        ASSERT_EQ(s1, s);
    }
}
