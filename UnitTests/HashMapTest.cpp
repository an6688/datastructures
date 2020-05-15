#include "stdafx.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "HashMap.h"
#include "ListQueue.h"
#include <queue>

using std::queue;
using std::string;

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	struct Book
	{
		Book() = default;

		bool operator==(const Book& book) const
		{
			return (Title == book.Title &&
				Author == book.Author &&
				Pages == book.Pages);
		}

		string Title{};
		string Author{};
		int Pages{};
	};
	TEST_CLASS(HashMapTest)
	{
	public:
		static const int TABLE_SIZE = 5;

		function<int(string key)> ASCII_HASH_FUNCTION = [&](string key)
		{	auto sum = 0;
		for (auto c : key)
			sum += c;
		return sum % TABLE_SIZE;
		};

		HashMap<string, Book> HashMapFactory()
		{
			HashMap<string, Book> table(TABLE_SIZE, ASCII_HASH_FUNCTION);

			const Book book1 = { "Catcher in the Rye", "J.D. Salinger", 635 };
			table.Insert("0763757233", book1);

			const Book book2 = { "Adventures of Huckleberry Finn", "Mark Twain", 452 };
			table.Insert("7063757233", book2);

			const Book book3 = { "Caffeine Rehab?  No, No, No.", "Lucas Cordova", 1 };
			table.Insert("7063757234", book3);

			return table;
		}

		TEST_METHOD_INITIALIZE(TestInit)
		{
			freopen("TestLog.txt", "a+", stdout);
		}

		TEST_METHOD(HashMapTraverseComplexObjectTest)
		{
			CrtCheckMemory check;
			{
				const auto ascii_hash_function = [&](string key)
				{	auto sum = 0;
				for (auto c : key)
					sum += c;

				return sum % TABLE_SIZE;
				};

				HashMap<string, Book> table(TABLE_SIZE, ascii_hash_function);

				const Book book1 = { "Catcher in the Rye", "J.D. Salinger", 635 };
				table.Insert("0763757233", book1);

				const Book book2 = { "Adventures of Huckleberry Finn", "Mark Twain", 452 };
				table.Insert("7063757233", book2);

				const Book book3 = { "Caffeine Rehab?  No, No, No.", "Lucas Cordova", 1 };
				table.Insert("7063757234", book3);

				Book books[] = { book1, book2, book3 };

				queue<Book> hash_traversal;
				const auto visit = [&](Book data) { hash_traversal.emplace(data); };

				table.Traverse(visit);

				const auto size = hash_traversal.size();

				for (auto i = 0; i < size; ++i)
				{
					const auto book = hash_traversal.front();
					hash_traversal.pop();
					Assert::IsTrue(books[i] == book);
				}
			}

		}
		TEST_METHOD(HashMapInsertTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			Assert::AreEqual(hashMap[970123456].Title, book1.Title);
			Assert::AreEqual(hashMap[970123456].Author, book1.Author);
			Assert::AreEqual(hashMap[970123456].Pages, book1.Pages);
			Assert::AreEqual(hashMap[970234765].Title, book2.Title);
			Assert::AreEqual(hashMap[970666666].Title, book3.Title);
		}

		TEST_METHOD(HashMapCtorTest)
		{
			CrtCheckMemory check;
			auto hashFunc = [](int key) {
				return key % TABLE_SIZE;
			};
			HashMap<int, string> hash(TABLE_SIZE, hashFunc);
			Assert::IsTrue(true);
		}

		TEST_METHOD(HashMapCopyCtorTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			HashMap<int, Book> copyHash(hashMap);
			Assert::AreEqual(hashMap[970123456].Title, copyHash[970123456].Title);
			Assert::AreEqual(hashMap[970234765].Title, copyHash[970234765].Title);
			Assert::AreEqual(hashMap[970666666].Title, copyHash[970666666].Title);
		}
		TEST_METHOD(HashMapTraverseTest)
		{
			list<Book> books;

			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			auto visitFunc = [&books](Book book)
			{
				books.emplace_front(book);
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			hashMap.Traverse(visitFunc);
			Assert::IsTrue(books.size() == 3);
			books.clear();
		}
		TEST_METHOD(HashmapNonUniqueKeyTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, int> hash(TABLE_SIZE, hashFunc);
			hash.Insert(200, 123456);
			try
			{
				hash.Insert(200, 98765);
				Assert::Fail();
			}
			catch (AdtException)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(HashMapDifficultDeleteTest)
		{
			list<Book> books;

			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			auto visitFunc = [&books](Book book)
			{
				books.emplace_front(book);
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			Book book4 = { "Holy Bible", "God", 2000 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			hashMap.Insert(970123134, book4);
			hashMap.Traverse(visitFunc);

			if (books.size() == 4)
			{
				hashMap.Delete(970123134);
				books.clear();
				hashMap.Traverse(visitFunc);
				Assert::IsTrue(books.size() == 3);
			}
			books.clear();
		}
		TEST_METHOD(HashmapDeleteFailTestTwo)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			CrtCheckMemory check;
			HashMap<int, int> hash(TABLE_SIZE, hashFunc);
			try
			{
				hash.Delete(111111);
				Assert::Fail();
			}
			catch (AdtException)
			{
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(HashmapCollisionReturnTest)
		{
			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};
			CrtCheckMemory check;
			HashMap<int, int> hash(TABLE_SIZE, hashFunc);
			hash.Insert(10, 99);
			hash.Insert(33, 250);
			hash.Insert(79, 567);
			Assert::AreEqual(hash[10], 99);
			Assert::AreEqual(hash[33], 250);
			Assert::AreEqual(hash[79], 567);
		}

		TEST_METHOD(HashMapDeleteTest)
		{
			list<Book> books;

			auto hashFunc = [](int key)
			{
				return key % TABLE_SIZE;
			};

			auto visitFunc = [&books](Book book)
			{
				books.emplace_front(book);
			};

			CrtCheckMemory check;
			HashMap<int, Book> hashMap(TABLE_SIZE, hashFunc);
			Book book1 = { "Catcher in the Rye", "JD Salinger", 635 };
			Book book2 = { "The Lord of the Rings", "Tolkien", 1200 };
			Book book3 = { "IT", "Stephen King", 1300 };
			hashMap.Insert(970123456, book1);
			hashMap.Insert(970234765, book2);
			hashMap.Insert(970666666, book3);
			hashMap.Traverse(visitFunc);

			if (books.size() == 3)
			{
				hashMap.Delete(970123456);
				books.clear();
				hashMap.Traverse(visitFunc);
				Assert::IsTrue(books.size() == 2);
			}
			books.clear();
		}
	};
}