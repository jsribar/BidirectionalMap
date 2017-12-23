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

		TEST_METHOD(BidirectionalMap_EmplaceMethodAddsNewPair)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalMap_EmplaceMethodReturnsTrueIfPairHasBeenAddedSuccessfully)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			Assert::IsTrue(bm.Emplace(1, "hello"));
			Assert::AreEqual(size_t(1), bm.Size());
		}

		TEST_METHOD(BidirectionalMap_EmplaceMethodCreatesMultiplePairsForEachCompletelyDifferentPairs)
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
				bm.Emplace(item.first, item.second);
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

		TEST_METHOD(BidirectionalMap_EmplaceMethodDoesNotAddPairIfFirstValueAlreadyExists)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);
			bm.Emplace(first, "world");

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalMap_EmplaceMethodDoesNotAddPairIfSecondValueAlreadyExists)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);
			bm.Emplace(2, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(BidirectionalMap_EmplaceMethodReturnsFalseIfPairHasNotBeenAddedSuccessfully)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());

			bm.Emplace(1, "hello");
			Assert::IsFalse(bm.Emplace(1, "hello"));
			Assert::IsFalse(bm.Emplace(2, "hello"));
			Assert::IsFalse(bm.Emplace(1, "world"));
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
				bm.Emplace(item.first, item.second);
			}

			bm.Clear();
			Assert::AreEqual(size_t(0), bm.Size());
		}

		TEST_METHOD(BidirectionalMap_SetMethodChangesFirstValueForExistingPairThatHasSameSecondValue)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);

			int newFirst = 5;
			bm.Set(newFirst, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newFirst, bm[second]);
			Assert::AreEqual(second, bm[newFirst]);
		}

		TEST_METHOD(BidirectionalMap_SetMethodChangesSecondValueForExistingPairThatHasSameFirstValue)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);

			std::string newSecond = "world";
			bm.Set(first, newSecond);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newSecond, bm[first]);
			Assert::AreEqual(first, bm[newSecond]);
		}

		TEST_METHOD(BidirectionalMap_SetMethodDoesNotAddNewPairIfNoPairHasSameFirstOrSecondValue)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Emplace(1, "hello");

			bm.Set(2, "world");
			Assert::AreEqual(size_t(1), bm.Size());
		}

		TEST_METHOD(BidirectionalMap_SetMethodReturnsTrueIfExistingPairHasBeenModified)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Emplace(1, "hello");

			Assert::IsTrue(bm.Set(1, "world"));
			Assert::IsTrue(bm.Set(2, "world"));
		}

		TEST_METHOD(BidirectionalMap_SetMethodReturnsFalseForAlreadyExistingPair)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);

			Assert::IsFalse(bm.Set(first, second));
		}

		TEST_METHOD(BidirectionalMap_ExistsReturnsTrueIfAPairWithValueProvidedExists)
		{
			int first = 1;
			std::string second = "hello";

			BidirectionalMap<int, std::string> bm;
			Assert::IsFalse(bm.FirstExists(first));
			Assert::IsFalse(bm.SecondExists(second));

			bm.Emplace(first, second);

			Assert::IsTrue(bm.FirstExists(first));
			Assert::IsTrue(bm.SecondExists(second));
		}

		TEST_METHOD(BidirectionalMap_ExistsReturnsFalseIfNoPairWithValueProvidedExists)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Emplace(1, "hello");

			Assert::IsFalse(bm.FirstExists(2));
			Assert::IsFalse(bm.SecondExists("world"));
		}
	};
}