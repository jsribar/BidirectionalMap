// Benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BidirectionalMap/BidirectionalMap.h"
#include "CompareMapBidirectionalMapAccess.h"
#include <map>
#include <unordered_map>

using namespace MapSpecial;

int main()
{
	std::cout << "BidirectionalMap vs. std::map" << std::endl;
	CompareMapBidirectionalMapAccess<BidirectionalMap, std::map>();
	std::cout << std::endl << "BidirectionalUnorderedMap vs. std::unordered_map" << std::endl;
	CompareMapBidirectionalMapAccess<BidirectionalUnorderedMap, std::unordered_map>();

	std::cout << std::endl << "FINISHED" << std::endl;
	char ch;
	std::cin >> ch;
	return 0;
}

