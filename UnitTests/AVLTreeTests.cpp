#include "stdafx.h"
//#include "stdafx.h"
//#include "CrtCheckMemory.h"
//#include "AdtException.h"
//#include "AVLNode.h"
//#include "AVLTree.h"
//
//using std::string;
//using std::to_string;
//using std::move;
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnitTests
//{
//	TEST_CLASS(AVLTreeTest)
//	{
//	public:
//
//		TEST_METHOD_INITIALIZE(InitializeMethod)
//		{
//			freopen("UNIT_TEST_LOG.txt", "a+", stdout);
//		}
//
//		TEST_METHOD(AVLNodeCtorTest)
//		{
//			CrtCheckMemory check;
//
//			AVLNode<int, int> test_node(15, 1);
//
//			Assert::IsTrue(true);
//		}
//
//		TEST_METHOD(AVLTreeInsertTest)
//		{
//			CrtCheckMemory check;
//
//			AVLTree<int, int> test_tree;
//
//			test_tree.Insert(10, 1);
//			test_tree.Insert(5, 1);
//			test_tree.Insert(15, 1);
//
//			Assert::IsTrue(true);
//		}
//
//		/*TEST_METHOD(AVLTreeRotateLeftTest)
//		{
//			CrtCheckMemory check;
//
//			AVLTree<int, int> test_tree;
//
//			test_tree.Insert(5, 1);
//			test_tree.Insert(10, 1);
//			test_tree.Insert(15, 1);
//
//			Assert::AreEqual(10, test_tree.GetRootKey(), L"Incorrect Root!");
//		}*/
//
//		/*TEST_METHOD(AVLTreeRotateRightTest)
//		{
//			CrtCheckMemory check;
//
//			AVLTree<int, int> test_tree;
//
//			test_tree.Insert(15, 1);
//			test_tree.Insert(10, 1);
//			test_tree.Insert(5, 1);
//
//			Assert::AreEqual(10, test_tree.GetRootKey(), L"Incorrect Root!");
//		}*/
//
//		/*TEST_METHOD(AVLTreeRotateRightLeftTest)
//		{
//			CrtCheckMemory check;
//
//			AVLTree<int, int> test_tree;
//
//			test_tree.Insert(10, 1);
//			test_tree.Insert(15, 1);
//			test_tree.Insert(13, 1);
//
//			Assert::AreEqual(13, test_tree.GetRootKey(), L"Incorrect Root!");
//		}*/
//
//		/*TEST_METHOD(AVLTreeRotateLeftRightTest)
//		{
//			CrtCheckMemory check;
//
//			AVLTree<int, int> test_tree;
//
//			test_tree.Insert(15, 1);
//			test_tree.Insert(5, 1);
//			test_tree.Insert(10, 1);
//
//			Assert::AreEqual(10, test_tree.GetRootKey(), L"Incorrect Root!");
//		}*/
//
//		TEST_METHOD(AVLTreeDeleteOneNodeTest)
//		{
//			CrtCheckMemory check;
//
//			AVLTree<int, int> test_tree;
//
//			test_tree.Insert(15, 1);
//
//			test_tree.Delete(15);
//		}
//
//		
//	};
//}
