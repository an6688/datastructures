#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "Pair.h"
#include "Array.h"
#include "ArrayStack.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(ArrayStackTest)
	{
	public:
		const int KEY = 1;
		const string VALUE = "something";

		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(ArrayStackPopTest_PopValueShouldEqualLoopCounter)
		{
			CrtCheckMemory check; 
			ArrayStack<int>stack(10); 
			for (auto i = 0; i < 10; ++i) 
				stack.Push(i); 
			for (auto i = 9; i >= 0; --i) 
				Assert::AreEqual(i, stack.Pop());
		}

		TEST_METHOD(ArrayStackCopyCtorTest)
		{
			CrtCheckMemory check;
			ArrayStack<int>stack(10);

			for (auto i = 0; i < 10; ++i)
				stack.Push(i);

			ArrayStack<int> stack_copy(stack); 

			for (auto i = 9; i >= 0; --i)
				Assert::AreEqual(i, stack_copy.Pop());
		}

		TEST_METHOD(ArrayStackMoveCtorTest)
		{
			CrtCheckMemory check;
			ArrayStack<int>stack(10);

			for (auto i = 0; i < 10; ++i)
				stack.Push(i);

			ArrayStack<int> stack_copy(std::move(stack));

			for (auto i = 9; i >= 0; --i)
				Assert::AreEqual(i, stack_copy.Pop());
		}

		TEST_METHOD(ArrayStackPopEmptyStackTest)
		{
			CrtCheckMemory check;
			ArrayStack<int>stack(10);

			const auto should_throw = [&stack]
			{
				stack.Pop(); 
			};

			Assert::ExpectException<AdtException>(should_throw); 
		}

		TEST_METHOD(ArrayStackFullStackPushTest)
		{
			CrtCheckMemory check;
			ArrayStack<int>stack(10);

			for (auto i = 0; i < 10; ++i)
				stack.Push(i);

			const auto should_throw = [&stack]
			{
				stack.Push(420);
			};

			Assert::ExpectException<AdtException>(should_throw);
		}
	};

}