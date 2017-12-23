#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <utility>
#include "../BidirectionalMap/BidirectionalMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(BidirectionalMapTest)
	{
	public:

		TEST_METHOD(BidirectionalMap_InsertMethodAddsNewPair)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalMap_InsertMethodReturnsTrueIfPairHasBeenAddedSuccessfully)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			Assert::IsTrue(bm.Insert(1, "hello"));
			Assert::AreEqual(size_t(1), bm.Size());
		}

		TEST_METHOD(BidirectionalMap_InsertMethodCreatesMultiplePairsForEachCompletelyDifferentPairs)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" }
			};

			BidirectionalMap<int, std::string> bm;
			for (const auto& item : entries)
			{
				bm.Insert(item.first, item.second);
			}

			Assert::AreEqual(entries.size(), bm.Size());

			size_t i = entries.size();
			while (i-- > 0)
			{
				const auto& entry = entries[i];
				Assert::AreEqual(entry.first, bm[entry.second]);
				Assert::AreEqual(entry.second, bm[entry.first]);
			}
		}

		TEST_METHOD(BidirectionalMap_InsertMethodDoesNotAddPairIfFirstValueAlreadyExists)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);
			bm.Insert(first, "world");

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalMap_InsertMethodDoesNotAddPairIfSecondValueAlreadyExists)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);
			bm.Insert(2, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalMap_InsertMethodReturnsFalseIfPairHasNotBeenAddedSuccessfully)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			bm.Insert(1, "hello");
			Assert::IsFalse(bm.Insert(1, "hello"));
			Assert::IsFalse(bm.Insert(2, "hello"));
			Assert::IsFalse(bm.Insert(1, "world"));
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodChangesFirstValueForExistingPairThatHasSameSecondValue)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			int newFirst = 5;
			bm.Change(newFirst, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newFirst, bm[second]);
			Assert::AreEqual(second, bm[newFirst]);
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodChangesSecondValueForExistingPairThatHasSameFirstValue)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			std::string newSecond = "world";
			bm.Change(first, newSecond);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newSecond, bm[first]);
			Assert::AreEqual(first, bm[newSecond]);
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodDoesNotAddNewPairIfNoPairHasSameFirstOrSecondValue)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Insert(1, "hello");

			bm.Change(2, "world");
			Assert::AreEqual(size_t(1), bm.Size());
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodReturnsTrueIfExistingPairHasBeenModified)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Insert(1, "hello");

			Assert::IsTrue(bm.Change(1, "world"));
			Assert::IsTrue(bm.Change(2, "world"));
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodReturnsFalseForAlreadyExistingPair)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			Assert::IsFalse(bm.Change(first, second));
		}

		TEST_METHOD(BidirectionalMap_ClearMethodErasesAllItems)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" }
			};

			BidirectionalMap<int, std::string> bm;
			for (const auto& item : entries)
			{
				bm.Insert(item.first, item.second);
			}

			bm.Clear();
			Assert::AreEqual(size_t(0), bm.Size());
		}

		TEST_METHOD(BidirectionalMap_RemoveMethodRemovesPairContainingProvidedValue)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" },
				{ 8, "Dobar dan" }
			};

			BidirectionalMap<int, std::string> bm;
			for (const auto& item : entries)
			{
				bm.Insert(item.first, item.second);
			}

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

		TEST_METHOD(BidirectionalMap_ExistsReturnsTrueIfAPairWithValueProvidedExists)
		{
			int first = 1;
			std::string second = "hello";

			BidirectionalMap<int, std::string> bm;
			Assert::IsFalse(bm.FirstExists(first));
			Assert::IsFalse(bm.SecondExists(second));

			bm.Insert(first, second);

			Assert::IsTrue(bm.FirstExists(first));
			Assert::IsTrue(bm.SecondExists(second));
		}

		TEST_METHOD(BidirectionalMap_ExistsReturnsFalseIfNoPairWithValueProvidedExists)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Insert(1, "hello");

			Assert::IsFalse(bm.FirstExists(2));
			Assert::IsFalse(bm.SecondExists("world"));
		}
	};
}