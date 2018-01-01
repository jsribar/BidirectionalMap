#include "stdafx.h"
#include "CppUnitTest.h"
#include <utility>
#include "../BidirectionalMap/BidirectionalMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MapSpecial;

namespace UnitTests
{
	TEST_CLASS(BidirectionalMapTest)
	{
	public:

		TEST_METHOD(BidirectionalMap_InsertMethodAddsNewKeyPair)
		{
			BidirectionalMap<int, std::string> bm;
			Assert::AreEqual(size_t(0), bm.Size());
			int first = 1;
			std::string second = "hello";

			bm.Insert(first, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm.AtFirst(first));
			Assert::AreEqual(first, bm.AtSecond(second));
		}

		TEST_METHOD(BidirectionalMap_InsertMethodReturnsTrueIfKeyPairHasBeenAddedSuccessfully)
		{
			BidirectionalMap<int, std::string> bm;

			Assert::IsTrue(bm.Insert(1, "hello"));
		}

		TEST_METHOD(BidirectionalMap_InsertMethodCreatesMultipleKeyPairsForEveryUniqueKeyPair)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" }
			};
			BidirectionalMap<int, std::string> bm;

			for (const auto& item : entries)
				bm.Insert(item.first, item.second);

			Assert::AreEqual(entries.size(), bm.Size());
			size_t i = entries.size();
			while (i-- > 0)
			{
				const auto& entry = entries[i];
				Assert::AreEqual(entry.first, bm.AtSecond(entry.second));
				Assert::AreEqual(entry.second, bm.AtFirst(entry.first));
			}
		}

		TEST_METHOD(BidirectionalMap_InsertMethodDoesNotAddKeyPairIfIdenticalKeyPairAlreadyExists)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			bm.Insert(first, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm.AtFirst(first));
			Assert::AreEqual(first, bm.AtSecond(second));
		}

		TEST_METHOD(BidirectionalMap_InsertMethodReturnsFalseIfIdenticalKeyPairAlreadyExists)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Insert(1, "hello");

			Assert::IsFalse(bm.Insert(1, "hello"));
		}

		TEST_METHOD(BidirectionalMap_InsertMethodThrows_invalid_argument_ExceptionIfOneOfKeysAlreadyExists)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			try
			{
				bm.Insert(2, second);
				Assert::Fail();
			}
			catch (const std::invalid_argument&)
			{
			}

			try
			{
				bm.Insert(first, "world");
				Assert::Fail();
			}
			catch (const std::invalid_argument&)
			{
			}

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(second, bm.AtFirst(first));
			Assert::AreEqual(first, bm.AtSecond(second));
		}

		TEST_METHOD(BidirectionalMap_ChangeFirstMethodChangesFirstKeyInExistingKeyPairThatHasGivenSecondKey)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			int newFirst = 5;
			bm.ChangeFirst(newFirst, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newFirst, bm.AtSecond(second));
			Assert::AreEqual(second, bm.AtFirst(newFirst));
		}

		TEST_METHOD(BidirectionalMap_ChangeFirstMethodThrows_out_of_range_ExceptionIfSecondKeyDoesNotExistInTheMap)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			try
			{
				int newFirst = 5;
				std::string newSecond = "world";
				bm.ChangeFirst(newFirst, newSecond);
				Assert::Fail();
			}
			catch (const std::out_of_range&)
			{
			}
			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(first, bm.AtSecond(second));
			Assert::AreEqual(second, bm.AtFirst(first));
		}

		TEST_METHOD(BidirectionalMap_ChangeFirstMethodThrows_invalid_argument_ExceptionIfIdenticalFirstKeyIsAlreadyAssignedToAnotherSecondKey)
		{
			BidirectionalMap<int, std::string> bm;
			int first1 = 1;
			std::string second1 = "hello";
			bm.Insert(first1, second1);
			int first2 = 2;
			std::string second2 = "world";
			bm.Insert(first2, second2);

			try
			{
				bm.ChangeFirst(first1, second2);
				Assert::Fail();
			}
			catch (const std::invalid_argument&)
			{
			}
			Assert::AreEqual(size_t(2), bm.Size());
			Assert::AreEqual(first1, bm.AtSecond(second1));
			Assert::AreEqual(first2, bm.AtSecond(second2));
		}

		TEST_METHOD(BidirectionalMap_ChangeSecondMethodChangesSecondKeyInExistingKeyPairThatHasGivenFirstKey)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			std::string newSecond = "world";
			bm.ChangeSecond(first, newSecond);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(first, bm.AtSecond(newSecond));
			Assert::AreEqual(newSecond, bm.AtFirst(first));
		}

		TEST_METHOD(BidirectionalMap_ChangeSecondMethodThrows_out_of_range_ExceptionIfFirstKeyDoesNotExistInTheMap)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			try
			{
				int newFirst = 5;
				std::string newSecond = "world";
				bm.ChangeSecond(newFirst, newSecond);
				Assert::Fail();
			}
			catch (const std::out_of_range&)
			{
			}
			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(first, bm.AtSecond(second));
			Assert::AreEqual(second, bm.AtFirst(first));
		}

		TEST_METHOD(BidirectionalMap_ChangeSecondMethodThrows_invalid_argument_ExceptionIfSecondKeyIsAlreadyAssignedToOtherFirstKey)
		{
			BidirectionalMap<int, std::string> bm;
			int first1 = 1;
			std::string second1 = "hello";
			bm.Insert(first1, second1);
			int first2 = 2;
			std::string second2 = "world";
			bm.Insert(first2, second2);

			try
			{
				bm.ChangeSecond(first1, second2);
				Assert::Fail();
			}
			catch (const std::invalid_argument&)
			{
			}
			Assert::AreEqual(size_t(2), bm.Size());
			Assert::AreEqual(first1, bm.AtSecond(second1));
			Assert::AreEqual(first2, bm.AtSecond(second2));
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodChangesFirstKeyForExistingKeyPairThatHasGivenSecondKey)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			int newFirst = 5;
			bm.Change(newFirst, second);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newFirst, bm.AtSecond(second));
			Assert::AreEqual(second, bm.AtFirst(newFirst));
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodChangesSecondKeyForExistingKeyPairThatHasGivenFirstKey)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			std::string newSecond = "world";
			bm.Change(first, newSecond);

			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(newSecond, bm.AtFirst(first));
			Assert::AreEqual(first, bm.AtSecond(newSecond));
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodThrows_out_of_range_ExceptionIfNoKeyPairHasSameFirstOrSecondKey)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Insert(1, "hello");

			try
			{
				bm.Change(2, "world");
				Assert::Fail();
			}
			catch (const std::out_of_range&)
			{
			}
			Assert::AreEqual(size_t(1), bm.Size());
			Assert::AreEqual(std::string("hello"), bm.AtFirst(1));
			Assert::AreEqual(1, bm.AtSecond("hello"));
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodReturnsTrueIfExistingKeyPairHasBeenModified)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Insert(1, "hello");

			Assert::IsTrue(bm.Change(1, "world"));
			Assert::IsTrue(bm.Change(2, "world"));
		}

		TEST_METHOD(BidirectionalMap_ChangeMethodReturnsFalseForAlreadyExistingKeyPair)
		{
			BidirectionalMap<int, std::string> bm;
			int first = 1;
			std::string second = "hello";
			bm.Insert(first, second);

			Assert::IsFalse(bm.Change(first, second));
		}

		TEST_METHOD(BidirectionalMap_ClearMethodErasesAllKeyPairs)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" }
			};
			BidirectionalMap<int, std::string> bm;
			for (const auto& item : entries)
				bm.Insert(item.first, item.second);

			bm.Clear();

			Assert::AreEqual(size_t(0), bm.Size());
		}

		TEST_METHOD(BidirectionalMap_RemoveMethodRemovesKeyPairContainingProvidedKey)
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
				bm.Insert(item.first, item.second);

			bm.RemoveFirst(5);

			Assert::AreEqual(size_t(3), bm.Size());
			Assert::IsFalse(bm.FirstExists(5));
			Assert::IsFalse(bm.SecondExists("hello"));
			Assert::AreEqual(2, bm.AtSecond("world"));
			Assert::AreEqual(7, bm.AtSecond("Guten Tag"));

			bm.RemoveSecond("Guten Tag");

			Assert::AreEqual(size_t(2), bm.Size());
			Assert::IsFalse(bm.SecondExists("Guten Tag"));
			Assert::IsFalse(bm.FirstExists(7));
			Assert::AreEqual(2, bm.AtSecond("world"));
			Assert::AreEqual(8, bm.AtSecond("Dobar dan"));
		}

		TEST_METHOD(BidirectionalMap_ExistsReturnsTrueIfAKeyPairWithGivenKeyExists)
		{
			int first = 1;
			std::string second = "hello";
			BidirectionalMap<int, std::string> bm;
			bm.Insert(first, second);

			Assert::IsTrue(bm.FirstExists(first));
			Assert::IsTrue(bm.SecondExists(second));
		}

		TEST_METHOD(BidirectionalMap_ExistsReturnsFalseIfNoKeyPairWithGivenKeyExists)
		{
			BidirectionalMap<int, std::string> bm;
			bm.Insert(1, "hello");

			Assert::IsFalse(bm.FirstExists(2));
			Assert::IsFalse(bm.SecondExists("world"));
		}

		TEST_METHOD(BidirectionalMap_CopyConstructorCreatesNewMap)
		{
			std::vector<std::pair<int, std::string>> entries =
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" },
				{ 8, "Dobar dan" }
			};
			BidirectionalMap<int, std::string> bm1;
			for (const auto& item : entries)
				bm1.Insert(item.first, item.second);

			BidirectionalMap<int, std::string> bm2(bm1);

			Assert::AreEqual(size_t(4), bm2.Size());
			Assert::IsTrue(bm2.FirstExists(5));
			Assert::IsTrue(bm2.FirstExists(2));
			Assert::IsTrue(bm2.FirstExists(7));
			Assert::IsTrue(bm2.FirstExists(8));
			Assert::IsTrue(bm2.SecondExists("hello"));
			Assert::IsTrue(bm2.SecondExists("world"));
			Assert::IsTrue(bm2.SecondExists("Guten Tag"));
			Assert::IsTrue(bm2.SecondExists("Dobar dan"));
			Assert::AreEqual(2, bm2.AtSecond("world"));
			Assert::AreEqual(5, bm2.AtSecond("hello"));
			Assert::AreEqual(7, bm2.AtSecond("Guten Tag"));
			Assert::AreEqual(8, bm2.AtSecond("Dobar dan"));
		}

		BidirectionalMap<int, std::string> CreateMap()
		{
			BidirectionalMap<int, std::string> result;
			result.Insert(5, "hello");
			result.Insert(2, "world");
			result.Insert(7, "Guten Tag");
			result.Insert(8, "Dobar dan");
			return result;
		}

		TEST_METHOD(BidirectionalMap_MoveConstructorCreatesNewMap)
		{
			BidirectionalMap<int, std::string> bm = CreateMap();

			Assert::AreEqual(size_t(4), bm.Size());
			Assert::IsTrue(bm.FirstExists(5));
			Assert::IsTrue(bm.FirstExists(2));
			Assert::IsTrue(bm.FirstExists(7));
			Assert::IsTrue(bm.FirstExists(8));
			Assert::IsTrue(bm.SecondExists("hello"));
			Assert::IsTrue(bm.SecondExists("world"));
			Assert::IsTrue(bm.SecondExists("Guten Tag"));
			Assert::IsTrue(bm.SecondExists("Dobar dan"));
			Assert::AreEqual(2, bm.AtSecond("world"));
			Assert::AreEqual(5, bm.AtSecond("hello"));
			Assert::AreEqual(7, bm.AtSecond("Guten Tag"));
			Assert::AreEqual(8, bm.AtSecond("Dobar dan"));
		}

		TEST_METHOD(BidirectionalMap_MoveAssignmentMovesMapData)
		{
			BidirectionalMap<int, std::string> bm;
			bm = CreateMap();

			Assert::AreEqual(size_t(4), bm.Size());
			Assert::IsTrue(bm.FirstExists(5));
			Assert::IsTrue(bm.FirstExists(2));
			Assert::IsTrue(bm.FirstExists(7));
			Assert::IsTrue(bm.FirstExists(8));
			Assert::IsTrue(bm.SecondExists("hello"));
			Assert::IsTrue(bm.SecondExists("world"));
			Assert::IsTrue(bm.SecondExists("Guten Tag"));
			Assert::IsTrue(bm.SecondExists("Dobar dan"));
			Assert::AreEqual(2, bm.AtSecond("world"));
			Assert::AreEqual(5, bm.AtSecond("hello"));
			Assert::AreEqual(7, bm.AtSecond("Guten Tag"));
			Assert::AreEqual(8, bm.AtSecond("Dobar dan"));
		}

		TEST_METHOD(BidirectionalMap_InitializerListConstructorCreatesNewMap)
		{
			BidirectionalMap<int, std::string> bm
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
			Assert::AreEqual(2, bm.AtSecond("world"));
			Assert::AreEqual(5, bm.AtSecond("hello"));
			Assert::AreEqual(7, bm.AtSecond("Guten Tag"));
			Assert::AreEqual(8, bm.AtSecond("Dobar dan"));
		}

		TEST_METHOD(BidirectionalMap_ForDifferentTypesIndexOperatorWithFirstKeyReturnsCorrespondingSecondKey)
		{
			BidirectionalMap<int, std::string> bm
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" },
				{ 8, "Dobar dan" }
			};

			Assert::AreEqual(bm.AtFirst(5), bm[5]);
			Assert::AreEqual(bm.AtFirst(2), bm[2]);
			Assert::AreEqual(bm.AtFirst(7), bm[7]);
			Assert::AreEqual(bm.AtFirst(8), bm[8]);
		}

		TEST_METHOD(BidirectionalMap_ForDifferentTypesIndexOperatorWithSecondKeyReturnsCorrespondingFirstKey)
		{
			BidirectionalMap<int, std::string> bm
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" },
				{ 8, "Dobar dan" }
			};

			Assert::AreEqual(bm.AtSecond("hello"), bm["hello"]);
			Assert::AreEqual(bm.AtSecond("world"), bm["world"]);
			Assert::AreEqual(bm.AtSecond("Guten Tag"), bm["Guten Tag"]);
			Assert::AreEqual(bm.AtSecond("Dobar dan"), bm["Dobar dan"]);
		}

		TEST_METHOD(BidirectionalMap_AtFirstThrows_out_of_range_ExceptionForNonExistentFirstKey)
		{
			BidirectionalMap<int, int> bm
			{
				{ 5, 505 },
				{ 2, 202 },
			};

			Assert::AreEqual(505, bm.AtFirst(5));

			try
			{
				bm.AtFirst(6);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
			}
		}

		TEST_METHOD(BidirectionalMap_AtSecondThrows_out_of_range_ExceptionForNonExistentSecondKey)
		{
			BidirectionalMap<int, int> bm
			{
				{ 5, 505 },
				{ 2, 202 },
			};

			Assert::AreEqual(2, bm.AtSecond(202));

			try
			{
				bm.AtSecond(101);
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
			}
			Assert::AreEqual(2, bm.AtSecond(202));
			Assert::AreEqual(5, bm.AtSecond(505));
		}

		TEST_METHOD(BidirectionalMap_IndexOperatorThrows_out_of_range_ExceptionForNonExistentKey)
		{
			BidirectionalMap<int, std::string> bm
			{
				{ 5, "hello" },
				{ 2, "world" },
			};

			try
			{
				bm[6];
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
			}

			try
			{
				bm["Guten Tag"];
				Assert::Fail();
			}
			catch (std::out_of_range&)
			{
			}
			Assert::AreEqual(5, bm.AtSecond("hello"));
			Assert::AreEqual(2, bm.AtSecond("world"));
		}

		TEST_METHOD(BidirectionalMap_ForDifferentTypesRemoveMethodCanBeCalledWithEitherFirstOrSecondKey)
		{
			BidirectionalMap<int, std::string> bm
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 7, "Guten Tag" },
				{ 8, "Dobar dan" }
			};

			bm.Remove("Guten Tag");

			Assert::IsFalse(bm.SecondExists("Guten Tag"));

			bm.Remove(8);

			Assert::IsFalse(bm.FirstExists(8));
		}

		TEST_METHOD(BidirectionalMap_ForDifferentTypesExistsMethodCanBeCalledWithEitherFirstOrSecondKey)
		{
			BidirectionalMap<int, std::string> bm
			{
				{ 5, "hello" },
				{ 2, "world" },
				{ 8, "Dobar dan" }
			};

			Assert::AreEqual(bm.SecondExists("Guten Tag"), bm.Exists("Guten Tag"));
			Assert::AreEqual(bm.FirstExists(7), bm.Exists(7));
			Assert::AreEqual(bm.SecondExists("hello"), bm.Exists("hello"));
			Assert::AreEqual(bm.FirstExists(5), bm.Exists(5));
		}
	};
}