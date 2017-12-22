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
		
		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodAddsNewKeyValuePair)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.size());

			int key = 1;
			std::string val = "hello";
			bm.Emplace(key, val);

			Assert::AreEqual(size_t(1), bm.size());
			Assert::AreEqual(val, bm[key]);
			Assert::AreEqual(key, bm[val]);
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodReturnsTrueIfKeyValuePairHasBeenAddedSuccessfully)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.size());

			int key = 1;
			std::string val = "hello";
			auto result = bm.Emplace(key, val);

			Assert::AreEqual(size_t(1), bm.size());
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodForMultipleItemsAddsMultipleKeyValuePairs)
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

			Assert::AreEqual(entries.size(), bm.size());

			size_t i = entries.size();
			while (i-- > 0)
			{
				const auto& entry = entries[i];
				Assert::AreEqual(entry.first, bm[entry.second]);
				Assert::AreEqual(entry.second, bm[entry.first]);
			}
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodDoesNotAddKeyValuePairIfKeyAlreadyExists)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.size());

			int key = 1;
			std::string val = "hello";
			bm.Emplace(key, val);
			bm.Emplace(key, "world");

			Assert::AreEqual(size_t(1), bm.size());
			Assert::AreEqual(val, bm[key]);
			Assert::AreEqual(key, bm[val]);
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodDoesNotAddKeyValuePairIfValueAlreadyExists)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.size());

			int key = 1;
			std::string val = "hello";
			bm.Emplace(key, val);
			bm.Emplace(2, val);

			Assert::AreEqual(size_t(1), bm.size());
			Assert::AreEqual(val, bm[key]);
			Assert::AreEqual(key, bm[val]);
		}

		TEST_METHOD(IntStringBidirectionalMap_EmplaceMethodReturnsFalseIfKeyValuePairHasNotBeenAddedSuccessfully)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.size());

			int key = 1;
			std::string val = "hello";
			bm.Emplace(key, val);
			auto result = bm.Emplace(key, val);

			Assert::AreEqual(false, result);
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
			Assert::AreEqual(size_t(0), bm.size());
		}

		TEST_METHOD(IntStringBidirectionalMap_SetMethodChangesValueForExistingKeyValuePair)
		{
			IntStringBidirectionalMap bm;
			int key = 1;
			std::string val = "hello";
			bm.Emplace(key, val);

			std::string newVal = "world";
			bm.Set(key, newVal);

			Assert::AreEqual(size_t(1), bm.size());
			Assert::AreEqual(key, bm[newVal]);
			Assert::AreEqual(newVal, bm[key]);
		}

		TEST_METHOD(IntStringBidirectionalMap_SetMethodChangesKeyForExistingKeyValuePair)
		{
			IntStringBidirectionalMap bm;
			int key = 1;
			std::string val = "hello";
			bm.Emplace(key, val);

			int newKey = 5;
			bm.Set(newKey, val);

			Assert::AreEqual(size_t(1), bm.size());
			Assert::AreEqual(newKey, bm[val]);
			Assert::AreEqual(val, bm[newKey]);
		}

	};
}