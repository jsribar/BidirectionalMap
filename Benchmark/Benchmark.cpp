// Benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BidirectionalMap/BidirectionalMap.h"
#include "CompareMapBidirectionalMapAccess.h"
#include "BidirectionalMapGeneration.h"
#include <map>
#include <unordered_map>

using namespace MapSpecial;

int main()
{
	constexpr int numOfItems = 100000;
	std::default_random_engine random;
	auto strings = GenerateRandomStrings(numOfItems);

	//std::cout << "BidirectionalMap vs. std::map" << std::endl;
	//CompareMapBidirectionalMapAccess<BidirectionalMap, std::map>(strings);
	std::cout << std::endl << "BidirectionalUnorderedMap vs. std::unordered_map" << std::endl;
	CompareMapBidirectionalMapAccess<BidirectionalUnorderedMap, std::unordered_map>(strings);

	//MeasureGeneration(strings);

	//std::cout << std::endl << "FINISHED" << std::endl;
	//char ch;
	//std::cin >> ch;
	return 0;
}

