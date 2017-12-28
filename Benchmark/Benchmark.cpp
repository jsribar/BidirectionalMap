// Benchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BidirectionalMap/BidirectionalMap.h"
#include "CompareMapBimapAccess.h"
#include <map>
#include <unordered_map>

using namespace MapSpecial;

int main()
{
	std::cout << "BidirectionalMap vs. std::map" << std::endl;
	CompareMapBiMapAccess<BidirectionalMap, std::map>();
	std::cout << std::endl << "BidirectionalUnorderedMap vs. std::unordered_map" << std::endl;
	CompareMapBiMapAccess<BidirectionalUnorderedMap, std::unordered_map>();

	std::cout << std::endl << "FINISHED" << std::endl;
	char ch;
	std::cin >> ch;
	return 0;
}

