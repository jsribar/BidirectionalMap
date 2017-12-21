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
		
		TEST_METHOD(IntStringBidirectionalMap_emplaceAddsNewKeyValuePair)
		{
			IntStringBidirectionalMap bm;
			Assert::AreEqual(size_t(0), bm.size());
			std::string val = "hello";
			bm.emplace(1, val);
			Assert::AreEqual(val, bm[1]);
			Assert::AreEqual(1, bm[val]);
			Assert::AreEqual(size_t(1), bm.size());
		}

		TEST_METHOD(IntStringBidirectionalMap_multipleEmplaceAddMultipleKeyValuePairs)
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
				bm.emplace(item.first, item.second);
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

		TEST_METHOD(IntStringBidirectionalMap_clearErasesAllItems)
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
				bm.emplace(item.first, item.second);
			}

			bm.clear();
			Assert::AreEqual(size_t(0), bm.size());
		}

		//TEST_METHOD(IntStringBidirectionalMap_indexOperatorChangesTheValueOfExistingKey)
		//{
		//	std::vector<std::pair<int, std::string>> entries =
		//	{
		//		{ 5, "hello" },
		//		{ 2, "world" },
		//		{ 7, "Guten Tag" }
		//	};

		//	IntStringBidirectionalMap bm;
		//	for (const auto& item : entries)
		//	{
		//		bm.emplace(item.first, item.second);
		//	}

		//	bm[5] = "X";
		//	Assert::AreEqual(std::string("X"), bm[5]);
		//}

		//TEST_METHOD(IntStringBidirectionalMap_indexOperatorChangesTheKeyForExistingValue)
		//{
		//	std::vector<std::pair<int, std::string>> entries =
		//	{
		//		{ 5, "hello" },
		//		{ 2, "world" },
		//		{ 7, "Guten Tag" }
		//	};

		//	IntStringBidirectionalMap bm;
		//	for (const auto& item : entries)
		//	{
		//		bm.emplace(item.first, item.second);
		//	}

		//	bm["world"] = 3;
		//	Assert::AreEqual(3, bm["world"]);
		//}

		//TEST_METHOD(IntStringBidirectionalMap_indexOperatorInsertsNewEntryForNonExistingKey)
		//{
		//	std::vector<std::pair<int, std::string>> entries =
		//	{
		//		{ 5, "hello" },
		//		{ 2, "world" },
		//		{ 7, "Guten Tag" }
		//	};

		//	IntStringBidirectionalMap bm;
		//	for (const auto& item : entries)
		//	{
		//		bm.emplace(item.first, item.second);
		//	}

		//	bm[3] = "Good morning";
		//	Assert::AreEqual(size_t(4), bm.size());
		//	Assert::AreEqual(std::string("Good morning"), bm[3]);
		//	Assert::AreEqual(3, bm["Good morning"]);
		//}

		//TEST_METHOD(IntStringBidirectionalMap_indexOperatorInsertsNewEntryForNonExistingValue)
		//{
		//	std::vector<std::pair<int, std::string>> entries =
		//	{
		//		{ 5, "hello" },
		//		{ 2, "world" },
		//		{ 7, "Guten Tag" }
		//	};

		//	IntStringBidirectionalMap bm;
		//	for (const auto& item : entries)
		//	{
		//		bm.emplace(item.first, item.second);
		//	}

		//	bm["Good morning"] = 4;
		//	Assert::AreEqual(size_t(4), bm.size());
		//	Assert::AreEqual(4, bm["Good morning"]);
		//	Assert::AreEqual(std::string("Good morning"), bm[4]);
		//}


	};
}