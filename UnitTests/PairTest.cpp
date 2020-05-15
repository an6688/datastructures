#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "Pair.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(PairTest)
	{
	public:
		const int KEY = 1;
		const string VALUE = "something";

		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(ConstructorTest_ShouldReturnExpectedKey)
		{
			// Arrange & Act
			CrtCheckMemory check;
			auto pair = Pair<int, string>(KEY, VALUE);

			// Assert
			Assert::IsTrue(pair.GetKey() == KEY && pair.GetValue() == VALUE, L"key or value invalid");
			/* below is similar to above
			Assert::AreEqual(KEY, pair.GetKey(), L"INVALID");
			Assert::AreEqual(VALUE, pair.GetValue(), L"INVALID");
			*/
		}
		TEST_METHOD(ConstructorTest_ShouldReturnExpectedValue)
		{
			// Arrange & Act
			CrtCheckMemory check;
			auto pair = Pair<int, string>(KEY, VALUE);

			// Assert
			Assert::IsTrue(pair.GetKey() == KEY && pair.GetValue() == VALUE, L"key or value invalid");
		};
	};
}