#include <string>
#include <gtest/gtest.h>
#include "../BinarySearchTreeLib/BinarySearchTree.h"


namespace BinarySearchTreeUnitTest
{

    TEST(BinarySearchTree, ConstructEmpty)
    {
        BinarySearchTree<int, int> tree;
        std::string expected = "";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertToEmpty)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        std::string expected = "([10,100],,)";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe2LevelOnTheLeftThereIsNoRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        std::string expected = "([10,100],([5,50],,),)";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe2LevelOnTheRightThereIsNoLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        std::string expected = "([10,100],,([20,200],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe2LevelOnTheLeftThereIsRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        tree.insert(5, 50);
        std::string expected = "([10,100],([5,50],,),([20,200],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe2LevelOnTheRightThereIsLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        tree.insert(20, 200);
        std::string expected = "([10,100],([5,50],,),([20,200],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe3LevelLeftLeftThereIsNoRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        std::string expected = "([50,500],([20,200],([10,100],,),),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe3LevelLeftLeftThereIsRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        tree.insert(10, 100);
        std::string expected = "([50,500],([20,200],([10,100],,),([30,300],,)),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe3LevelLeftRightThereIsNoLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        std::string expected = "([50,500],([20,200],,([30,300],,)),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe3LevelLeftRightThereIsLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        tree.insert(30, 300);
        std::string expected = "([50,500],([20,200],([10,100],,),([30,300],,)),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe3LevelRightLeftThereIsNoRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe3LevelRightLeftThereIsRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(90, 900);
        tree.insert(70, 700);
        std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),([90,900],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe3LevelRightRightThereIsNoLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(90, 900);
        std::string expected = "([50,500],([20,200],,),([80,800],,([90,900],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertOnThe3LevelRightRightThereIsLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        tree.insert(90, 900);
        std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),([90,900],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, insertExisting)
    {
        BinarySearchTree<int, int> tree;
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

    TEST(BinarySearchTree, removeFromEmpty)
    {
        BinarySearchTree<int, int> tree;
        tree.remove(10);
        std::string expected = "";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, removeRoot)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.remove(50);
        std::string expected = "";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, removeNotExisting)
    {
        BinarySearchTree<int, int> tree;
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
        tree.remove(25);
        std::string expected = "([50,501],([20,201],,),([80,801],([70,701],,),([90,901],,)))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, removeNodeWithoutChildren)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.remove(20);
        std::string expected = "([50,500],,([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, removeNodeWithoutLeftChild)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        tree.remove(20);
        std::string expected = "([50,500],([30,300],,),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, removeNodeWithoutRightChild)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        tree.remove(20);
        std::string expected = "([50,500],([10,100],,),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, removeNodeWithChildren)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        tree.insert(30, 300);
        tree.insert(15, 150);
        tree.insert(12, 120);
        tree.remove(20);
        std::string expected = "([50,500],([15,150],([10,100],,([12,120],,)),([30,300],,)),([80,800],,))";
        ASSERT_EQ(expected, tree.toString());
    }

    TEST(BinarySearchTree, findInEmpty)
    {
        BinarySearchTree<int, int> tree;
        ASSERT_EQ(nullptr, tree.find(10));
    }

    TEST(BinarySearchTree, findNotExisted)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        tree.insert(20, 200);
        ASSERT_EQ(nullptr, tree.find(2));
        ASSERT_EQ(nullptr, tree.find(7));
        ASSERT_EQ(nullptr, tree.find(12));
        ASSERT_EQ(nullptr, tree.find(24));
    }

    TEST(BinarySearchTree, findOnThe1LevelNoChildren)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        ASSERT_EQ(100, *tree.find(10));
        tree.insert(5, 50);
        ASSERT_EQ(100, *tree.find(10));
        tree.insert(20, 200);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(BinarySearchTree, findOnThe1LevelIsLeftChild)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(BinarySearchTree, findOnThe1LevelIsRightChild)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(BinarySearchTree, findOnThe1LevelAreChildren)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        tree.insert(20, 200);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(BinarySearchTree, findOnThe2LevelOnTheLeftThereIsNoRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        ASSERT_EQ(50, *tree.find(5));
    }

    TEST(BinarySearchTree, findOnThe2LevelOnTheRightThereIsNoLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        ASSERT_EQ(200, *tree.find(20));
    }

    TEST(BinarySearchTree, findOnThe2LevelOnTheLeftThereIsRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(20, 200);
        tree.insert(5, 50);
        ASSERT_EQ(50, *tree.find(5));
    }

    TEST(BinarySearchTree, findOnThe2LevelOnTheRightThereIsLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(10, 100);
        tree.insert(5, 50);
        tree.insert(20, 200);
        ASSERT_EQ(200, *tree.find(20));
    }

    TEST(BinarySearchTree, findOnThe3LevelLeftLeftThereIsNoRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(BinarySearchTree, findOnThe3LevelLeftLeftThereIsRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        tree.insert(10, 100);
        ASSERT_EQ(100, *tree.find(10));
    }

    TEST(BinarySearchTree, findOnThe3LevelLeftRightThereIsNoLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(30, 300);
        ASSERT_EQ(300, *tree.find(30));
    }

    TEST(BinarySearchTree, findOnThe3LevelLeftRightThereIsLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(10, 100);
        tree.insert(30, 300);
        ASSERT_EQ(300, *tree.find(30));
    }

    TEST(BinarySearchTree, findOnThe3LevelRightLeftThereIsNoRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        ASSERT_EQ(700, *tree.find(70));
    }

    TEST(BinarySearchTree, findOnThe3LevelRightLeftThereIsRight)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(90, 900);
        tree.insert(70, 700);
        ASSERT_EQ(700, *tree.find(70));
    }

    TEST(BinarySearchTree, findOnThe3LevelRightRightThereIsNoLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(90, 900);
        ASSERT_EQ(900, *tree.find(90));
    }

    TEST(BinarySearchTree, findOnThe3LevelRightRightThereIsLeft)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(50, 500);
        tree.insert(20, 200);
        tree.insert(80, 800);
        tree.insert(70, 700);
        tree.insert(90, 900);
        ASSERT_EQ(900, *tree.find(90));
    }

    TEST(BinarySearchTree, print0)
    {
        BinarySearchTree<int, int> tree;
        std::ostringstream stream;
        tree.print(stream);
        auto s = stream.str();
        std::string s1 = "";
        ASSERT_EQ(s1, s);
    }

    TEST(BinarySearchTree, print1)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(1, 1);
        std::ostringstream stream;
        tree.print(stream);
        auto s = stream.str();
        std::string s1 = "[1, 1]\n";
        ASSERT_EQ(s1, s);
    }

    TEST(BinarySearchTree, print3)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(2, 2);
        tree.insert(1, 1);
        tree.insert(3, 3);
        std::ostringstream stream;
        tree.print(stream);
        auto s = stream.str();
        std::string s1 = "[2, 2]\n    L: [1, 1]\n    R: [3, 3]\n";
        ASSERT_EQ(s1, s);
    }

    TEST(BinarySearchTree, print7)
    {
        BinarySearchTree<int, int> tree;
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

    TEST(BinarySearchTree, findclosest1)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(4, 4);
        tree.insert(2, 2);
        tree.insert(1, 1);
        tree.insert(3, 3);
        tree.insert(6, 6);
        tree.insert(5, 5);
        tree.insert(7, 7);

        int searched = 9;
        int closest = tree.findClosestTester(searched);

        ASSERT_EQ(7, closest);
    }

    TEST(BinarySearchTree, findclosest2)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(4, 4);
        tree.insert(2, 2);
        tree.insert(1, 1);
        tree.insert(3, 3);
        tree.insert(6, 6);
        tree.insert(5, 5);

        int searched = 1;
        int closest = tree.findClosestTester(searched);

        ASSERT_EQ(1, closest);
    }

    TEST(BinarySearchTree, findclosest_root)
    {
        BinarySearchTree<int, int> tree;
        tree.insert(4, 4);
        tree.insert(6, 6);
        tree.insert(5, 5);
        tree.insert(7, 7);

        int searched = 1;
        int closest = tree.findClosestTester(searched);

        ASSERT_EQ(4, closest);
    }
}
