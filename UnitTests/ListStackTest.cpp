#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "Pair.h"
#include "Array.h"
#include "ListStack.h"
#include "ListQueue.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(ListStackTest)
	{
	public:
		const int KEY = 1;
		const string VALUE = "something";

		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(ListStackPopTest_PopValueShouldEqualLoopCounter)
		{
			CrtCheckMemory check;
			ListStack<int>stack;
			for (auto i = 0; i < 10; ++i)
				stack.Push(i);
			for (auto i = 9; i >= 0; --i)
				Assert::AreEqual(i, stack.Pop());
		}

		TEST_METHOD(ListStackCopyCtorTest)
		{
			CrtCheckMemory check;
			ListStack<int>stack;

			for (auto i = 0; i < 10; ++i)
				stack.Push(i);

			ListStack<int> stack_copy(stack);

			for (auto i = 9; i >= 0; --i)
				Assert::AreEqual(i, stack_copy.Pop());
		}

		TEST_METHOD(ListStackMoveCtorTest)
		{
			CrtCheckMemory check;
			ListStack<int>stack;

			for (auto i = 0; i < 10; ++i)
				stack.Push(i);

			ListStack<int> stack_copy(std::move(stack));

			for (auto i = 9; i >= 0; --i)
				Assert::AreEqual(i, stack_copy.Pop());
		}

		TEST_METHOD(ListQueue_EnqueueAndDequeueOrderShouldMatch)
		{
			CrtCheckMemory check;
			ListQueue<int> queue;
			for (auto i = 0; i < 10; i++)
				queue.Enqueue(i);
			for (auto i = 0; i < 10; i++)
				Assert::AreEqual(i, queue.Dequeue());
		}
	};

}