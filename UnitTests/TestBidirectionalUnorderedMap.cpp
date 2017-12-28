#include "stdafx.h"
#include "CppUnitTest.h"
#include <utility>
#include "../BidirectionalMap/BidirectionalMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MapSpecial;

namespace UnitTests
{
	TEST_CLASS(BidirectionalUnorderedMapTest)
	{
	public:

		TEST_METHOD(BidirectionalUnorderedMap_InsertMethodAddsNewPair)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());
			int first = 1;
			std::string second = "hello";

			bm.Insert(first, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalUnorderedMap_InsertMethodReturnsTrueIfPairHasBeenAddedSuccessfully)
		{
			BidirectionalUnorderedMap<int, std::string> bm;

			Assert::IsTrue(bm.Insert(1, "hello"));
		}

		TEST_METHOD(BidirectionalUnorderedMap_InsertMethodCreatesMultiplePairsForEveryCompletelyDifferentPair)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" }
			};
			BidirectionalUnorderedMap<int, std::string> bm;

			for (const auto& item : entries)
				bm.Insert(item.first, item.second);

			Assert::AreEqual(entries.size(), bm.Size());
			size_t i = entries.size();
			while (i-- > 0)
			{
				const auto& entry = entries[i];
				Assert::AreEqual(entry.first, bm[entry.second]);
				Assert::AreEqual(entry.second, bm[entry.first]);
			}
		}

		TEST_METHOD(BidirectionalUnorderedMap_InsertMethodDoesNotAddPairIfFirstValueAlreadyExists)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			bm.Insert(first, "world");

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalUnorderedMap_InsertMethodDoesNotAddPairIfSecondValueAlreadyExists)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			bm.Insert(2, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalUnorderedMap_InsertMethodReturnsFalseIfPairHasNotBeenAddedSuccessfully)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			bm.Insert(1, "hello");

			Assert::IsFalse(bm.Insert(1, "hello"));
			Assert::IsFalse(bm.Insert(2, "hello"));
			Assert::IsFalse(bm.Insert(1, "world"));
		}

		TEST_METHOD(BidirectionalUnorderedMap_ChangeMethodChangesFirstValueForExistingPairThatHasSameSecondValue)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			int newFirst = 5;
			bm.Change(newFirst, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newFirst, bm[second]);
			Assert::AreEqual(second, bm[newFirst]);
		}

		TEST_METHOD(BidirectionalUnorderedMap_ChangeMethodChangesSecondValueForExistingPairThatHasSameFirstValue)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			std::string newSecond = "world";
			bm.Change(first, newSecond);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newSecond, bm[first]);
			Assert::AreEqual(first, bm[newSecond]);
		}

		TEST_METHOD(BidirectionalUnorderedMap_ChangeMethodDoesNotAddNewPairIfNoPairHasSameFirstOrSecondValue)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			bm.Insert(1, "hello");

			bm.Change(2, "world");

			Assert::AreEqual(size_t(1), bm.Size());
		}

		TEST_METHOD(BidirectionalUnorderedMap_ChangeMethodReturnsTrueIfExistingPairHasBeenModified)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			bm.Insert(1, "hello");

			Assert::IsTrue(bm.Change(1, "world"));
			Assert::IsTrue(bm.Change(2, "world"));
		}

		TEST_METHOD(BidirectionalUnorderedMap_ChangeMethodReturnsFalseForAlreadyExistingPair)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			Assert::IsFalse(bm.Change(first, second));
		}

		TEST_METHOD(BidirectionalUnorderedMap_ClearMethodErasesAllItems)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" }
			};
			BidirectionalUnorderedMap<int, std::string> bm;
			for (const auto& item : entries)
				bm.Insert(item.first, item.second);

			bm.Clear();

			Assert::AreEqual(size_t(0), bm.Size());
		}

		TEST_METHOD(BidirectionalUnorderedMap_RemoveMethodRemovesPairContainingProvidedValue)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" },
				{ 8, "Dobar dan" }
			};
			BidirectionalUnorderedMap<int, std::string> bm;
			for (const auto& item : entries)
				bm.Insert(item.first, item.second);

			bm.Remove(5);

			Assert::AreEqual(size_t(3), bm.Size());
			Assert::IsFalse(bm.FirstExists(5));
			Assert::IsFalse(bm.SecondExists("hello"));
			Assert::AreEqual(2, bm["world"]);
			Assert::AreEqual(7, bm["Guten Tag"]);

			bm.Remove("Guten Tag");

			Assert::AreEqual(size_t(2), bm.Size());
			Assert::IsFalse(bm.SecondExists("Guten Tag"));
			Assert::IsFalse(bm.FirstExists(7));
			Assert::AreEqual(2, bm["world"]);
			Assert::AreEqual(8, bm["Dobar dan"]);
		}

		TEST_METHOD(BidirectionalUnorderedMap_ExistsReturnsTrueIfAPairWithValueProvidedExists)
		{
			int first = 1;
			std::string second = "hello";
			BidirectionalUnorderedMap<int, std::string> bm;
			bm.Insert(first, second);

			Assert::IsTrue(bm.FirstExists(first));
			Assert::IsTrue(bm.SecondExists(second));
		}

		TEST_METHOD(BidirectionalUnorderedMap_ExistsReturnsFalseIfNoPairWithValueProvidedExists)
		{
			BidirectionalUnorderedMap<int, std::string> bm;
			bm.Insert(1, "hello");

			Assert::IsFalse(bm.FirstExists(2));
			Assert::IsFalse(bm.SecondExists("world"));
		}

		BidirectionalUnorderedMap<int, std::string> CreateMap()
		{
			BidirectionalUnorderedMap<int, std::string> result;
			result.Insert(5, "hello");
			result.Insert(2, "world");
			result.Insert(7, "Guten Tag");
			result.Insert(8, "Dobar dan");
			return result;
		}

		TEST_METHOD(BidirectionalUnorderedMap_MoveConstructorCreatesNewMap)
		{
			BidirectionalUnorderedMap<int, std::string> bm = CreateMap();

			Assert::AreEqual(size_t(4), bm.Size());
			Assert::IsTrue(bm.FirstExists(5));
			Assert::IsTrue(bm.FirstExists(2));
			Assert::IsTrue(bm.FirstExists(7));
			Assert::IsTrue(bm.FirstExists(8));
			Assert::IsTrue(bm.SecondExists("hello"));
			Assert::IsTrue(bm.SecondExists("world"));
			Assert::IsTrue(bm.SecondExists("Guten Tag"));
			Assert::IsTrue(bm.SecondExists("Dobar dan"));
			Assert::AreEqual(2, bm["world"]);
			Assert::AreEqual(5, bm["hello"]);
			Assert::AreEqual(7, bm["Guten Tag"]);
			Assert::AreEqual(8, bm["Dobar dan"]);
		}

		TEST_METHOD(BidirectionalUnorderedMap_CopyConstructorCreatesNewMap)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" },
				{ 8, "Dobar dan" }
			};
			BidirectionalUnorderedMap<int, std::string> bm1;
			for (const auto& item : entries)
				bm1.Insert(item.first, item.second);

			BidirectionalUnorderedMap<int, std::string> bm2(bm1);

			Assert::AreEqual(size_t(4), bm2.Size());
			Assert::IsTrue(bm2.FirstExists(5));
			Assert::IsTrue(bm2.FirstExists(2));
			Assert::IsTrue(bm2.FirstExists(7));
			Assert::IsTrue(bm2.FirstExists(8));
			Assert::IsTrue(bm2.SecondExists("hello"));
			Assert::IsTrue(bm2.SecondExists("world"));
			Assert::IsTrue(bm2.SecondExists("Guten Tag"));
			Assert::IsTrue(bm2.SecondExists("Dobar dan"));
			Assert::AreEqual(2, bm2["world"]);
			Assert::AreEqual(5, bm2["hello"]);
			Assert::AreEqual(7, bm2["Guten Tag"]);
			Assert::AreEqual(8, bm2["Dobar dan"]);
		}

		TEST_METHOD(BidirectionalUnorderedMap_InitializerListConstructorCreatesNewMap)
		{
			BidirectionalUnorderedMap<int, std::string> bm
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" },
				{ 8, "Dobar dan" }
			};

			Assert::AreEqual(size_t(4), bm.Size());
			Assert::IsTrue(bm.FirstExists(5));
			Assert::IsTrue(bm.FirstExists(2));
			Assert::IsTrue(bm.FirstExists(7));
			Assert::IsTrue(bm.FirstExists(8));
			Assert::IsTrue(bm.SecondExists("hello"));
			Assert::IsTrue(bm.SecondExists("world"));
			Assert::IsTrue(bm.SecondExists("Guten Tag"));
			Assert::IsTrue(bm.SecondExists("Dobar dan"));
			Assert::AreEqual(2, bm["world"]);
			Assert::AreEqual(5, bm["hello"]);
			Assert::AreEqual(7, bm["Guten Tag"]);
			Assert::AreEqual(8, bm["Dobar dan"]);
		}
	};
}