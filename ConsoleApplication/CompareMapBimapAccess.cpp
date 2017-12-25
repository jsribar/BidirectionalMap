#include "stdafx.h"
#include "CompareMapBimapAccess.h"
#include "GenerateRandomStrings.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>

template<typename TKey, typename TValue>
BidirectionalMap<TKey, TValue> GenarateBiMap(const std::vector<std::pair<TKey, TValue>>& pairs)
{
	BidirectionalMap<TKey, TValue> map;
	for (const auto& pair : pairs)
		map.Insert(pair.first, pair.second);
	return map;
}

template<typename TKey, typename TValue>
std::map<TKey, TValue> GenarateMap(const std::vector<std::pair<TKey, TValue>>& pairs)
{
	std::map<TKey, TValue> map;
	for (const auto& pair : pairs)
		map.emplace(pair.first, pair.second);
	return map;
}

using Clock = std::chrono::high_resolution_clock;
using time_point = const std::chrono::time_point<Clock>;

void OutputDuration(const std::string& description, const time_point& start, const time_point& end)
{
	std::cout << description.c_str() << ": " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
}

void CompareMapBiMapAccess()
{
	constexpr int numOfItems = 50000;

	std::default_random_engine random;
	auto strings = GenerateRandomStrings(numOfItems);
	int i = 0;
	std::vector<std::pair<int, std::string>> intStringPairs;
	for (const auto& s : strings)
		intStringPairs.emplace_back(i++, s);

	i = 0;
	std::vector<std::pair<std::string, int>> stringIntPairs;
	for (const auto& s : strings)
		stringIntPairs.emplace_back(s, i++);

	std::chrono::high_resolution_clock clock;

	std::cout << "*** int-string map ***" << std::endl;

	auto now1 = clock.now();

	// evaluate bidirectional map generation
	auto biMap = GenarateBiMap(intStringPairs);

	auto now2 = clock.now();
	OutputDuration("GenarateBiMap                 ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map generation
	auto map = GenarateMap(intStringPairs);

	now2 = clock.now();
	OutputDuration("GenarateMap                   ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map access
	size_t totalLength{ 0 };
	for (int i = 0; i < numOfItems; ++i)
		totalLength += biMap[i].size();

	now2 = clock.now();
	OutputDuration("AccessBiMapValuesByFirstIndex ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += map[i].size();

	now2 = clock.now();
	OutputDuration("AccessMapValuesByFirstIndex   ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += biMap[strings[i]];

	now2 = clock.now();
	OutputDuration("AccessBiMapValuesBySecondIndex", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += std::find_if(map.cbegin(), map.cend(), [&](const std::pair<int, std::string>& item) { return item.second == strings[i]; })->first;

	now2 = clock.now();
	OutputDuration("AccessMapValuesBySecondIndex  ", now1, now2);


	std::cout << "*** string-int map ***" << std::endl;

	now1 = clock.now();

	// evaluate bidirectional map generation
	auto biMap2 = GenarateBiMap(stringIntPairs);

	now2 = clock.now();
	OutputDuration("GenarateBiMap                 ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map generation
	auto map2 = GenarateMap(stringIntPairs);

	now2 = clock.now();
	OutputDuration("GenarateMap                   ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += biMap2[strings[i]];

	now2 = clock.now();
	OutputDuration("AccessBiMapValuesByFirstIndex ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += map2[strings[i]];

	now2 = clock.now();
	OutputDuration("AccessMapValuesByFirstIndex   ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += biMap2[i].size();

	now2 = clock.now();
	OutputDuration("AccessBiMapValuesBySecondIndex", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += std::find_if(map2.cbegin(), map2.cend(), [&](const std::pair<std::string, int>& item) { return item.second == i; })->second;

	now2 = clock.now();
	OutputDuration("AccessMapValuesBySecondIndex  ", now1, now2);
}
