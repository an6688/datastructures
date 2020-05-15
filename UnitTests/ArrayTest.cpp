#include "stdafx.h"
#include "CppUnitTest.h"
#include "crtdbg.h"
#include "CrtCheckMemory.h"

#include "Pair.h"
#include "Array.h"
#include "Array2D.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTests
{
	TEST_CLASS(arrayTest)
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
		TEST_METHOD(ArrayParameterizedConstructor_ArrayLengthShouldBeFive)
		{
			CrtCheckMemory check;

			Array<int> array(5, -3);

			Assert::AreEqual(static_cast<size_t>(5), array.GetLength());
		}

		TEST_METHOD(ArrayParameterizedConstructor_StartIndexShouldBeNegativeThree)
		{
			CrtCheckMemory check;

			Array<int> negativeArray(5, -3);

			Assert::AreEqual(-3, negativeArray.GetStartIndex());
		}

		TEST_METHOD(ArrayNegativeLengthConstructorTest_ShouldThrowException)
		{
			CrtCheckMemory check;

			const auto should_throw = [] {Array<int> negative_length_array(-12, 0); };
			Assert::ExpectException<AdtException>(should_throw);
		}

		TEST_METHOD(DefaultConstructorMemLeak_ShouldPass)
		{
			// ARRANGE
			CrtCheckMemory check; 
			Array <string> testarray; 

			// ACT

			// ASSERT 
			Assert::IsTrue(true);
		}

		TEST_METHOD(OOBIndexHigh_ShouldPass)
		{
			CrtCheckMemory check;

			Array<int> OOB_array(0, 0);
			auto const should_throw = [&OOB_array]
			{
				OOB_array[7];
				
			};
			Assert::ExpectException<AdtException>(should_throw); 
		}

		TEST_METHOD(OOBIndexLow_ShouldFail)
		{
			CrtCheckMemory check;

			Array<int> OOB_array(7, 0);
			auto const should_throw = [&OOB_array]
			{
				OOB_array[7];

			};
			Assert::ExpectException<AdtException>(should_throw);
		}
		TEST_METHOD(WithinBounds_ShouldPass)
		{
			CrtCheckMemory check;

			Array<int> OOB_array(7, 0);
			OOB_array[4];

		}

		TEST_METHOD(MoveAssignmentChecker_ShouldPass)
		{
			// Arrange & Act
			CrtCheckMemory check;
			auto name = Array <string> (10, 0); 
			auto name1 = Array <string>(10, 0);

			// Assert
			name1 = std::move(name); 
		}

		TEST_METHOD (MoveCtorCheck_ShouldPass)
		{
			// Arrange & Act
			CrtCheckMemory check;
			auto string_array = Array<string>(5, 0);

			//Assert
			auto stringArray2(std::move(string_array));
		}
		TEST_METHOD(SetLength_ShouldPass)
		{
			// Arrange & Act
			CrtCheckMemory check;
			auto string_array = Array<string>(5, 0);

			//Assert
			auto stringArray2(std::move(string_array));
		}

		TEST_METHOD(SetLengthShorter_ShouldPass)
		{
			// Arrange & Act
			CrtCheckMemory check;
			auto array = Array<int>(5, 0);
			for (size_t i {0}; i < array.GetLength(); ++i )
			{
				array[i] = i * i;
			}
			array.SetLength(3);
			for (size_t i{ 0 }; i < array.GetLength(); ++i)
			{
				int j = i * i; 
				Assert::AreEqual(j, array[i], L"shortened array values do not match!");
			}
			//Assert

		}

		TEST_METHOD(SetLengthLonger_ShouldPass)
		{
			CrtCheckMemory check;
			auto array = Array<int>(5, 0);

			for (size_t i{ 0 }; i < array.GetLength(); ++i)
			{
				array[i] = i * i;
			}

			array.SetLength(9);

			for (size_t i{ 0 }; i < 5; ++i)
			{
				int j = i * i;
				Assert::AreEqual(j, array[i], L"expanded array values do not match!");
			}
		}

		TEST_METHOD(ConstArrayIndex_ShouldPass)
		{
			// Arrange & Act
			CrtCheckMemory check;

			const auto string_array = Array<string>(5, 0);
			const auto const_string = Array<string>(string_array);

			auto test = const_string[3];

			// Assert
		}

		TEST_METHOD(CopyCtorTest_ShouldPass)
		{
			string const zero = "zero";
			string const one = "one";
			string const two = "two";

			CrtCheckMemory check;
			auto string_array = Array<string>(3, 0);

			string_array[0] = zero;
			string_array[1] = one;
			string_array[2] = two;

			auto string_array2(string_array);

			Assert::AreEqual(string_array2[0], zero, L"index not equal");
			Assert::AreEqual(string_array2[1], one, L"index not equal");
			Assert::AreEqual(string_array2[2], two, L"index not equal");
		}

		TEST_METHOD(CopyAssignmentTest_ShouldPass)
		{
			string const zero = "zero";
			string const one = "one";
			string const two = "two";

			CrtCheckMemory check;
			auto string_array = Array<string>(3, 0);

			string_array[0] = zero;
			string_array[1] = one;
			string_array[2] = two;

			auto string_array2 = string_array;

			Assert::AreEqual(string_array2[0], zero, L"index not equal");
			Assert::AreEqual(string_array2[1], one, L"index not equal");
			Assert::AreEqual(string_array2[2], two, L"index not equal");
		}

		TEST_METHOD(AccessUpBoundMax_NoThrow)
		{
			CrtCheckMemory check;

			auto string_array = Array <string>(10, -5);
			string_array[4];

			Assert::IsTrue(true);
		}

		TEST_METHOD(AccessOutsideUpBoundMax_Throw)
		{
			CrtCheckMemory check;
			Array <string>string_array(10, -5);

			auto const should_throw = [&string_array]
			{
				string_array[5];
			};

			Assert::ExpectException<AdtException>(should_throw);
		}
	};
}