#pragma once
#include "../BidirectionalMap/BidirectionalMap.h"
#include "CompareMapBidirectionalMapAccess.h"
#include <chrono>
#include <iostream>

// evaluate bidirectional map generation
std::string MeasureAccess(MapSpecial::BidirectionalUnorderedMap<std::string, int>&& biMap)
{
	std::string text;
	for (size_t i = 0; i < biMap.Size(); ++i)
		text = biMap.AtSecond(i);
	return text;
}


void MeasureGeneration(const std::vector<std::string>& strings)
{
	//std::chrono::high_resolution_clock clock;

	//std::cout << "*** int-string ***" << std::endl;

	//auto now1 = clock.now();
	MapSpecial::BidirectionalUnorderedMap<std::string, int> biMap;
	for (size_t i = 0; i < strings.size(); ++i)
		biMap.Insert(strings[i], i);

	std::string text = MeasureAccess(std::move(biMap));
	//auto now2 = clock.now();
	//OutputDuration("Generate boost bimap                      ", now1, now2);
}

