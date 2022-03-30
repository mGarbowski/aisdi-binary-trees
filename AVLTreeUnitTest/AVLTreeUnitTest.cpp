#include "CppUnitTest.h"
#include "../AVLTreeLib/AVLTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AVLTreeUnitTest
{
	TEST_CLASS(AVLTreeUnitTest)
	{
	public:
		TEST_METHOD(leftRootRotationAfterInsert)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 10);
			tree.insert(20, 20);
			std::string expected = "([10,10],,([20,20],,))";
			Assert::AreEqual(expected, tree.toString());
			tree.insert(30, 30);
			expected = "([20,20],([10,10],,),([30,30],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(leftRotationAfterInsert)
		{
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
			Assert::AreEqual(expected, tree.toString());
			tree.insert(50, 50);
			expected = "([60,60],([30,30],([20,20],([10,10],,),([25,25],,)),([40,40],,([50,50],,))),([70,70],,([80,80],,)))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(rightLeftRootRotationAfterInsert)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 10);
			tree.insert(30, 30);
			std::string expected = "([10,10],,([30,30],,))";
			Assert::AreEqual(expected, tree.toString());
			tree.insert(20, 20);
			expected = "([20,20],([10,10],,),([30,30],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(rightLeftRotationAfterInsert)
		{
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
			Assert::AreEqual(expected, tree.toString());
			tree.insert(22, 22);
			expected = "([60,60],([25,25],([20,20],([10,10],,),([22,22],,)),([30,30],,([40,40],,))),([70,70],,([80,80],,)))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(rightRootRotationAfterInsert)
		{
			AVLTree<int, int> tree;
			tree.insert(30, 30);
			tree.insert(20, 20);
			std::string expected = "([30,30],([20,20],,),)";
			Assert::AreEqual(expected, tree.toString());
			tree.insert(10, 10);
			expected = "([20,20],([10,10],,),([30,30],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(rightRotationAfterInsert)
		{
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
			Assert::AreEqual(expected, tree.toString());
			tree.insert(40, 40);
			expected = "([30,30],([20,20],([10,10],,),),([60,60],([50,50],([40,40],,),),([80,80],([70,70],,),([90,90],,))))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(leftRightRootRotationAfterInsert)
		{
			AVLTree<int, int> tree;
			tree.insert(30, 30);
			tree.insert(10, 10);
			std::string expected = "([30,30],([10,10],,),)";
			Assert::AreEqual(expected, tree.toString());
			tree.insert(20, 20);
			expected = "([20,20],([10,10],,),([30,30],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(leftRightRotationAfterInsert)
		{
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
			Assert::AreEqual(expected, tree.toString());
			tree.insert(70, 70);
			expected = "([30,30],([20,20],([10,10],,),),([60,60],([50,50],([40,40],,),),([80,80],([70,70],,),([90,90],,))))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(ConstructEmpty)
		{
			AVLTree<int, int> tree;
			std::string expected = "";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertToEmpty)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			std::string expected = "([10,100],,)";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe2LevelOnTheLeftThereIsNoRight)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			std::string expected = "([10,100],([5,50],,),)";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe2LevelOnTheRightThereIsNoLeft)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			std::string expected = "([10,100],,([20,200],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe2LevelOnTheLeftThereIsRight)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			tree.insert(5, 50);
			std::string expected = "([10,100],([5,50],,),([20,200],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe2LevelOnTheRightThereIsLeft)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(20, 200);
			std::string expected = "([10,100],([5,50],,),([20,200],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelLeftLeftThereIsNoRight)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(10, 100);
			std::string expected = "([50,500],([20,200],([10,100],,),),([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelLeftLeftThereIsRight)
		{
			AVLTree<int, int> tree;
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
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(30, 300);
			std::string expected = "([50,500],([20,200],,([30,300],,)),([80,800],,))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelLeftRightThereIsLeft)
		{
			AVLTree<int, int> tree;
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
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(70, 700);
			std::string expected = "([50,500],([20,200],,),([80,800],([70,700],,),))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelRightLeftThereIsRight)
		{
			AVLTree<int, int> tree;
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
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(90, 900);
			std::string expected = "([50,500],([20,200],,),([80,800],,([90,900],,)))";
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(insertOnThe3LevelRightRightThereIsLeft)
		{
			AVLTree<int, int> tree;
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
			Assert::AreEqual(expected, tree.toString());
		}
		TEST_METHOD(findInEmpty)
		{
			AVLTree<int, int> tree;
			Assert::IsNull(tree.find(10));
		}
		TEST_METHOD(findNotExisted)
		{
			AVLTree<int, int> tree;
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
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			Assert::AreEqual(100, *tree.find(10));
			tree.insert(5, 50);
			Assert::AreEqual(100, *tree.find(10));
			tree.insert(20, 200);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe1LevelIsLeftChild)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe1LevelIsRightChild)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe1LevelAreChildren)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(20, 200);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe2LevelOnTheLeftThereIsNoRight)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			Assert::AreEqual(50, *tree.find(5));
		}
		TEST_METHOD(findOnThe2LevelOnTheRightThereIsNoLeft)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			Assert::AreEqual(200, *tree.find(20));
		}
		TEST_METHOD(findOnThe2LevelOnTheLeftThereIsRight)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(20, 200);
			tree.insert(5, 50);
			Assert::AreEqual(50, *tree.find(5));
		}
		TEST_METHOD(findOnThe2LevelOnTheRightThereIsLeft)
		{
			AVLTree<int, int> tree;
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(20, 200);
			Assert::AreEqual(200, *tree.find(20));
		}
		TEST_METHOD(findOnThe3LevelLeftLeftThereIsNoRight)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(10, 100);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe3LevelLeftLeftThereIsRight)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(30, 300);
			tree.insert(10, 100);
			Assert::AreEqual(100, *tree.find(10));
		}
		TEST_METHOD(findOnThe3LevelLeftRightThereIsNoLeft)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(30, 300);
			Assert::AreEqual(300, *tree.find(30));
		}
		TEST_METHOD(findOnThe3LevelLeftRightThereIsLeft)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(10, 100);
			tree.insert(30, 300);
			Assert::AreEqual(300, *tree.find(30));
		}
		TEST_METHOD(findOnThe3LevelRightLeftThereIsNoRight)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(70, 700);
			Assert::AreEqual(700, *tree.find(70));
		}
		TEST_METHOD(findOnThe3LevelRightLeftThereIsRight)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(90, 900);
			tree.insert(70, 700);
			Assert::AreEqual(700, *tree.find(70));
		}
		TEST_METHOD(findOnThe3LevelRightRightThereIsNoLeft)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(90, 900);
			Assert::AreEqual(900, *tree.find(90));
		}
		TEST_METHOD(findOnThe3LevelRightRightThereIsLeft)
		{
			AVLTree<int, int> tree;
			tree.insert(50, 500);
			tree.insert(20, 200);
			tree.insert(80, 800);
			tree.insert(70, 700);
			tree.insert(90, 900);
			Assert::AreEqual(900, *tree.find(90));
		}
		TEST_METHOD(print0)
		{
			AVLTree<int, int> tree;
			std::ostringstream stream;
			tree.print(stream);
			auto s = stream.str();
			std::string s1 = "";
			Assert::AreEqual(s1, s);
		}
		TEST_METHOD(print1)
		{
			AVLTree<int, int> tree;
			tree.insert(1, 1);
			std::ostringstream stream;
			tree.print(stream);
			auto s = stream.str();
			std::string s1 = "[1, 1]\n";
			Assert::AreEqual(s1, s);
		}
		TEST_METHOD(print3)
		{
			AVLTree<int, int> tree;
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
			Assert::AreEqual(s1, s);
		}
	};
}
