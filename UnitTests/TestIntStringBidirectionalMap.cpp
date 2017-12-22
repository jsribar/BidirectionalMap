#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <utility>
#include "../BidirectionalMap/IntStringBidirectionalMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodAddsNewPair)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodReturnsTrueIfPairHasBeenAddedSuccessfully)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.Size());

			Assert::IsTrue(bm.Emplace(1, "hello"));
			Assert::AreEqual(size_t(1), bm.Size());
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodCreatesMultiplePairsForEachCompletelyDifferentPairs)
		{
			std::vector<std::pair<int, std::string>> entries = 
			{ 
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" }
			};

			IntStringBidirectionalMap bm;
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

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodDoesNotAddPairIfFirstValueAlreadyExists)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);
			bm.Emplace(first, "world");

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodDoesNotAddPairIfSecondValueAlreadyExists)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.Size());

			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);
			bm.Emplace(2, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm[first]);
			Assert::AreEqual(first, bm[second]);
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodReturnsFalseIfPairHasNotBeenAddedSuccessfully)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.Size());

			bm.Emplace(1, "hello");
			Assert::IsFalse(bm.Emplace(1, "hello"));
			Assert::IsFalse(bm.Emplace(2, "hello"));
			Assert::IsFalse(bm.Emplace(1, "world"));
		}

		TEST_METHOD(IntStringBidirectionalMap_ClearMethodErasesAllItems)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" }
			};

			IntStringBidirectionalMap bm;
			for (const auto& item : entries)
			{
				bm.Emplace(item.first, item.second);
			}

			bm.Clear();
			Assert::AreEqual(size_t(0), bm.Size());
		}

		TEST_METHOD(IntStringBidirectionalMap_SetMethodChangesFirstValueForExistingPairThatHasSameSecondValue)
		{
			IntStringBidirectionalMap bm;
			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);

			int newFirst = 5;
			bm.Set(newFirst, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newFirst, bm[second]);
			Assert::AreEqual(second, bm[newFirst]);
		}

		TEST_METHOD(IntStringBidirectionalMap_SetMethodChangesSecondValueForExistingPairThatHasSameFirstValue)
		{
			IntStringBidirectionalMap bm;
			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);

			std::string newSecond = "world";
			bm.Set(first, newSecond);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newSecond, bm[first]);
			Assert::AreEqual(first, bm[newSecond]);
		}

		TEST_METHOD(IntStringBidirectionalMap_SetMethodDoesNotAddNewPairIfNoPairHasSameFirstOrSecondValue)
		{
			IntStringBidirectionalMap bm;
			bm.Emplace(1, "hello");

			bm.Set(2, "world");
			Assert::AreEqual(size_t(1), bm.Size());
		}

		TEST_METHOD(IntStringBidirectionalMap_SetMethodReturnsTrueIfExistingPairHasBeenModified)
		{
			IntStringBidirectionalMap bm;
			bm.Emplace(1, "hello");

			Assert::IsTrue(bm.Set(1, "world"));
			Assert::IsTrue(bm.Set(2, "world"));
		}

		TEST_METHOD(IntStringBidirectionalMap_SetMethodReturnsFalseForAlreadyExistingPair)
		{
			IntStringBidirectionalMap bm;
			int first = 1;
			std::string second = "hello";
			bm.Emplace(first, second);

			Assert::IsFalse(bm.Set(first, second));
		}

		TEST_METHOD(IntStringBidirectionalMap_ExistsReturnsTrueIfAPairWithValueProvidedExists)
		{
			int first = 1;
			std::string second = "hello";

			IntStringBidirectionalMap bm;
			Assert::IsFalse(bm.Exists(first));
			Assert::IsFalse(bm.Exists(second));
			
			bm.Emplace(first, second);

			Assert::IsTrue(bm.Exists(first));
			Assert::IsTrue(bm.Exists(second));
		}

		TEST_METHOD(IntStringBidirectionalMap_ExistsReturnsFalseIfNoPairWithValueProvidedExists)
		{
			IntStringBidirectionalMap bm;
			bm.Emplace(1, "hello");

			Assert::IsFalse(bm.Exists(2));
			Assert::IsFalse(bm.Exists("world"));
		}
	};
}