#include <string>
#include "CppUnitTest.h"
#include "..\BinarySearchTreeLib\BinarySearchTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinarySearchTreeUnitTest
{
	TEST_CLASS(BinarySearchTreeUnitTest)
	{
	public:
		TEST_METHOD(ConstructEmpty)
		{
			BinarySearchTree<int, int> tree;
			std::string expected = "";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertToEmpty)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			std::string expected = "([10,100],,)";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe2LevelOnTheLeftThereIsNoRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			std::string expected = "([10,100],([5,50],,),)";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe2LevelOnTheRightThereIsNoLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			std::string expected = "([10,100],,([20,200],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe2LevelOnTheLeftThereIsRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			tree.insert(5, 50);
			std::string expected = "([10,100],([5,50],,),([20,200],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe2LevelOnTheRightThereIsLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(20, 200);
			std::string expected = "([10,100],([5,50],,),([20,200],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelLeftLeftThereIsNoRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(10, 100);
			std::string expected = "([50,500],([20,200],([10,100],,),),([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelLeftLeftThereIsRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(30, 300);
			tree.insert(10, 100);
			std::string expected = "([50,500],([20,200],([10,100],,),([30,300],,)),([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelLeftRightThereIsNoLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(30, 300);
			std::string expected = "([50,500],([20,200],,([30,300],,)),([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelLeftRightThereIsLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(10, 100);
			tree.insert(30, 300);
			std::string expected = "([50,500],([20,200],([10,100],,),([30,300],,)),([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelRightLeftThereIsNoRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(70, 700);
			std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelRightLeftThereIsRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(90, 900);
			tree.insert(70, 700);
			std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),([90,900],,)))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelRightRightThereIsNoLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(90, 900);
			std::string expected = "([50,500],([20,200],,),([80,800],,([90,900],,)))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelRightRightThereIsLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(70, 700);
			tree.insert(90, 900);
			std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),([90,900],,)))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertExisting)
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
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(removeFromEmpty)
		{
			BinarySearchTree<int, int> tree;
			tree.remove(10);
			std::string expected = "";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(removeRoot)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.remove(50);
			std::string expected = "";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(removeNotExisting)
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
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(removeNodeWithoutChildren)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.remove(20);
			std::string expected = "([50,500],,([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(removeNodeWithoutLeftChild)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(30, 300);
			tree.remove(20);
			std::string expected = "([50,500],([30,300],,),([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(removeNodeWithoutRightChild)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(10, 100);
			tree.remove(20);
			std::string expected = "([50,500],([10,100],,),([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(removeNodeWithChildren)
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
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(findInEmpty)
		{
			BinarySearchTree<int, int> tree;
			Assert::IsNull(tree.find(10));
		}
		TEST_METHOD(findNotExisted)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(20, 200);
			Assert::IsNull(tree.find(2));
			Assert::IsNull(tree.find(7));
			Assert::IsNull(tree.find(12));
			Assert::IsNull(tree.find(24));
		}
		TEST_METHOD(findOnThe1LevelNoChildren)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			Assert::AreEqual(100, *tree.find(10));
			tree.insert(5, 50);
			Assert::AreEqual(100, *tree.find(10));
			tree.insert(20, 200);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe1LevelIsLeftChild)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe1LevelIsRightChild)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe1LevelAreChildren)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(20, 200);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe2LevelOnTheLeftThereIsNoRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			Assert::AreEqual(50, *tree.find(5));
		}
		TEST_METHOD(findOnThe2LevelOnTheRightThereIsNoLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			Assert::AreEqual(200, *tree.find(20));
		}
		TEST_METHOD(findOnThe2LevelOnTheLeftThereIsRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			tree.insert(5, 50);
			Assert::AreEqual(50, *tree.find(5));
		}
		TEST_METHOD(findOnThe2LevelOnTheRightThereIsLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(20, 200);
			Assert::AreEqual(200, *tree.find(20));
		}
		TEST_METHOD(findOnThe3LevelLeftLeftThereIsNoRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(10, 100);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe3LevelLeftLeftThereIsRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(30, 300);
			tree.insert(10, 100);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe3LevelLeftRightThereIsNoLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(30, 300);
			Assert::AreEqual(300, *tree.find(30));
		}
		TEST_METHOD(findOnThe3LevelLeftRightThereIsLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(10, 100);
			tree.insert(30, 300);
			Assert::AreEqual(300, *tree.find(30));
		}
		TEST_METHOD(findOnThe3LevelRightLeftThereIsNoRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(70, 700);
			Assert::AreEqual(700, *tree.find(70));
		}
		TEST_METHOD(findOnThe3LevelRightLeftThereIsRight)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(90, 900);
			tree.insert(70, 700);
			Assert::AreEqual(700, *tree.find(70));
		}
		TEST_METHOD(findOnThe3LevelRightRightThereIsNoLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(90, 900);
			Assert::AreEqual(900, *tree.find(90));
		}
		TEST_METHOD(findOnThe3LevelRightRightThereIsLeft)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(70, 700);
			tree.insert(90, 900);
			Assert::AreEqual(900, *tree.find(90));
		}
		TEST_METHOD(print0)
		{
			BinarySearchTree<int, int> tree;
			std::ostringstream stream;
			tree.print(stream);
			auto s = stream.str();
			std::string s1 = "";
			Assert::AreEqual(s1, s);
		}
		TEST_METHOD(print1)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(1, 1);
			std::ostringstream stream;
			tree.print(stream);
			auto s = stream.str();
			std::string s1 = "[1, 1]\n";
			Assert::AreEqual(s1, s);
		}
		TEST_METHOD(print3)
		{
			BinarySearchTree<int, int> tree;
			tree.insert(2, 2);
			tree.insert(1, 1);
			tree.insert(3, 3);
			std::ostringstream stream;
			tree.print(stream);
			auto s = stream.str();
			std::string s1 = "[2, 2]\n    L: [1, 1]\n    R: [3, 3]\n";
			Assert::AreEqual(s1, s);
		}

		TEST_METHOD(print7)
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
			Assert::AreEqual(s1, s);
		}
	};
}
