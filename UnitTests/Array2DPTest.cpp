#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "Pair.h"
#include "Array.h"
#include "Array2D.h"
#include "Array2D.h"
#include "Array2DP.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(array2DPTest)
	{
	public:
		const int KEY = 1;
		const string VALUE = "something";

		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}
		TEST_METHOD(SelectMethodTest)
		{
			// Arrange 
			CrtCheckMemory check;
			Array2DP<int> array(3, 3);

			// Act
			for (auto i{ 0 }; i < array.GetRow(); ++i)
			{
				for (auto j{ 0 }; j < array.GetColumn(); ++j)
				{
					array.Select(i, j) = i * j;
				}
			}

			// Assert
			for (auto i{ 0 }; i < array.GetRow(); ++i)
			{
				for (auto j{ 0 }; j < array.GetColumn(); ++j)
				{
					Assert::AreEqual(i * j, array.Select(i, j), L"Value Mismatch!");
				}
			}
		}

		TEST_METHOD(SelectMethodTestNegValues)
		{
			// Arrange 
			CrtCheckMemory check;

			// Act
			auto const should_throw = []
			{
				Array2DP<int> array(-3, -3);
			};

			Assert::ExpectException<AdtException>(should_throw); 
		}

	TEST_METHOD(ZeroValues)
		{
			CrtCheckMemory check;

			Array2DP<int> array(0, 0); 

			Assert::IsTrue(true);
		}
		TEST_METHOD(DefCtorLeakTest)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			Array2DP<int> array;

			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(CtorLeakTest)
		{
			// Arrange
			CrtCheckMemory check;

			// Act
			Array2DP<int> array(4,4);

			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(CopyTest) // not working 
		{
			// Arrange
			CrtCheckMemory check;

			Array2DP<int> array(4, 4);
			Array2DP<int> array1(5, 5);

			for (auto i{ 0 }; i < array.GetRow(); ++i)
			{
				for (auto j{ 0 }; j < array.GetColumn(); ++j)
				{
					array.Select(i, j) = (i + 1) * (j + 1);
				}
			}

			// Act
			array1 = array;

			// Assert
			for (auto i{ 0 }; i < array.GetRow(); ++i)
			{
				for (auto j{ 0 }; j < array.GetColumn(); ++j)
				{
					 Assert::AreEqual((i + 1) * (j + 1), array1.Select(i, j), L"Value Mismatch!");
				}
			}
		}

		TEST_METHOD(BracketTestOOBHigh)
		{
			CrtCheckMemory check;

			Array2DP<int> OOB_array(6, 6);
			auto const should_throw = [&OOB_array]
			{
				OOB_array[6][8];
			};
			Assert::ExpectException<AdtException>(should_throw);
		}

		TEST_METHOD(BracketTestOOBLow)
		{
			CrtCheckMemory check;

			Array2DP<int> OOB_array(6, 7);

			auto const should_throw = [&OOB_array]
			{
				OOB_array[-1][0];
			};
			 Assert::ExpectException<AdtException>(should_throw);
		}
	};
}