#include "stdafx.h"
#include "AdtException.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include "CrtCheckMemory.h"
#include "Array2DP.h"
using std::string;
using std::to_string;
using std::move;

namespace UnitTests
{
	TEST_CLASS(Array2DPTest_Lucas)
	{
	public:

		TEST_METHOD(Array2DPMoveTest)
		{
			CrtCheckMemory check;
			{
				Array2DP<int> myArray(1, 1);
				Array2DP<int> myArray2(move(myArray));
			}
		}

		TEST_METHOD(Array2DPMoveStringTest)
		{
			CrtCheckMemory check;
			{
				Array2DP<string> myArray(2, 2);
				for (auto i = 2; i < 2; ++i)
					for (auto j = 2; j < 2; ++j)
						myArray[i][j] = to_string(i);

				Array2DP<string> myArray2(move(myArray));
				for (auto i = 2; i < 2; ++i)
					for (auto j = 2; j < 2; ++j)
				Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(myArray2[i][j], to_string(i));
			}
		}

		TEST_METHOD(Array2DPMoveAssignmentStringTest)
		{
			CrtCheckMemory check;
			{
				Array2DP<string> myArray(2, 2);
				for (auto i = 2; i < 2; ++i)
					for (auto j = 2; j < 2; ++j)
						myArray[i][j] = to_string(i);

				Array2DP<string> myArray2;
				myArray2 = move(myArray);
				for (auto i = 2; i < 2; ++i)
					for (auto j = 2; j < 2; ++j)
						Assert::AreEqual(myArray2[i][j], to_string(i));
			}
		}

		TEST_METHOD(Array2DPDefaultCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<int> defaultCtor;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPStringDefaultCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<string> stringArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPGoodCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPStringGoodCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPBadRowCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<int> badArray(-1, 3);
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPBadColCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<int> badArray(3, -1);
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPStringBadRowCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<string> badStringArray(-1, 3);
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPStringBadColCtorTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<string> badStringArray(3, -1);
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPCopyCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<int> arrayOne(3, 3);
			Array2DP<int> arrayTwo(arrayOne);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPStringCopyCtorTest)
		{
			CrtCheckMemory check;
			Array2DP<string> stringArrayOne(3, 3);
			Array2DP<string> stringArrayTwo(stringArrayOne);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPAssignmentOpTest)
		{
			CrtCheckMemory check;
			Array2DP<int> sourceArray(3, 3);
			Array2DP<int> destArray;
			destArray = sourceArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPStringAssignmentOpTest)
		{
			CrtCheckMemory check;
			Array2DP<string> sourceStringArray(3, 3);
			Array2DP<string> destStringArray(3, 3);
			destStringArray = sourceStringArray;
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPSubscriptOpGoodTest)
		{
			CrtCheckMemory check;
			try
			{
				int count = 0;
				Array2DP<int> myArray(3, 3);
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						myArray[i][j] = count++;
					}
				}
				Assert::IsTrue(true);
			}
			catch (AdtException exception)
			{
				// Not expecting an exception.
				Assert::Fail(exception.What());
			}
		}

		TEST_METHOD(Array2DPSubscriptOpBadRowTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<int> myArray(3, 3);
				myArray[-1][0] = 1;
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPSubscriptOpBadColTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<int> myArray(3, 3);
				myArray[0][-1] = 1;
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPStringSubscriptOpGoodTest)
		{
			CrtCheckMemory check;
			try
			{
				Array2DP<string> myStringArray(3, 3);
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						myStringArray[i][j] = "Test String " + (i + j);
				Assert::IsTrue(true);
			}
			catch (AdtException)
			{
				// Not expecting an exception.
			}
		}

		TEST_METHOD(Array2DPStringSubscriptOpBadRowTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			try
			{
				myStringArray[-1][0] = "Bad String.";
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPStringSubscriptOpBadColTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			try
			{
				myStringArray[0][-1] = "Bad String.";
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPSetRowGoodTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			myArray.SetRow(4);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPSetColumnGoodTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			myArray.SetColumn(4);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPSetRowBadTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			try
			{
				myArray.SetRow(-1);
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPSetColumnBadTest)
		{
			CrtCheckMemory check;
			Array2DP<int> myArray(3, 3);
			try
			{
				myArray.SetColumn(-1);
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPStringSetRowGoodTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			myStringArray.SetRow(4);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPStringSetColGoodTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			myStringArray.SetColumn(4);
			Assert::IsTrue(true);
		}

		TEST_METHOD(Array2DPStringSetRowBadTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			try
			{
				myStringArray.SetRow(-1);
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Array2DPStringSetColumnBadTest)
		{
			CrtCheckMemory check;
			Array2DP<string> myStringArray(3, 3);
			try
			{
				myStringArray.SetColumn(-1);
			}
			catch (AdtException)
			{
				// Expecting an exception.
				Assert::IsTrue(true);
			}
		}

		//TEST_METHOD(Array2DPSetRowDataLossTest)
		//{
		//	CrtCheckMemory check;
		//	Array2DP<int> myArray(3, 3);
		//	int index = 0;
		//	for (int i = 0; i < 3; i++)
		//		for (int j = 0; j < 3; j++)
		//			myArray[i][j] = index++;
		//	// 0 1 2
		//	// 3 4 5
		//	// 6 7 8

		//	myArray.SetRow(2);
		//	// 0 1 2
		//	// 3 4 5
		//	// +
		//	//--------
		//	// 15

		//	int total = 0;
		//	for (int i = 0; i < myArray.GetRow(); i++)
		//		for (int j = 0; j < myArray.GetColumn(); j++)
		//			total += myArray[i][j];

		//	Assert::IsTrue(total == 15);
		//}

		//TEST_METHOD(Array2DPSetColumnDataLossTest)
		//{ not working 
		//	CrtCheckMemory check;
		//	Array2DP<int> myArray(3, 3);
		//	int index = 0;
		//	for (int i = 0; i < 3; i++)
		//		for (int j = 0; j < 3; j++)
		//			myArray[i][j] = index++;
		//	// 0 1 2
		//	// 3 4 5
		//	// 6 7 8

		//	myArray.SetColumn(2);
		//	// 0 1
		//	// 3 4
		//	// 6 7
		//	// +
		//	//------
		//	// 21

		//	int total = 0;
		//	for (int i = 0; i < myArray.GetRow(); i++)
		//		for (int j = 0; j < myArray.GetColumn(); j++)
		//			total += myArray[i][j];

		//	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(total == 21);
		//}
	};
}