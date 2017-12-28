#pragma once
#include "GenerateRandomStrings.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>

template<template<typename, typename> class TBiMap, typename TKey, typename TValue>
TBiMap<TKey, TValue> GenerateBiMap(const std::vector<std::pair<TKey, TValue>>& pairs)
{
	TBiMap<TKey, TValue> map;
	for (const auto& pair : pairs)
		map.Insert(pair.first, pair.second);
	return map;
}

template<template<typename... Args> class TMap, typename TKey, typename TValue>
TMap<TKey, TValue> GenerateMap(const std::vector<std::pair<TKey, TValue>>& pairs)
{
	TMap<TKey, TValue> map;
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

template<template<typename... Args> class TBiMap, template<typename... Args> class TMap>
void CompareMapBidirectionalMapAccess()
{
	constexpr int numOfItems = 5000;

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

	std::cout << "*** int-string ***" << std::endl;

	auto now1 = clock.now();

	// evaluate bidirectional map generation
	auto biMap = GenerateBiMap<TBiMap>(intStringPairs);

	auto now2 = clock.now();
	OutputDuration("Generate bidirectional map                ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map generation
	auto map = GenerateMap<TMap>(intStringPairs);

	now2 = clock.now();
	OutputDuration("Generate map                              ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map access
	for (int i = 0; i < numOfItems; ++i)
		biMap[i];

	now2 = clock.now();
	OutputDuration("Access bidirectional map members by int   ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map access
	for (int i = 0; i < numOfItems; ++i)
		map[i];

	now2 = clock.now();
	OutputDuration("Access map members by int                 ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	for (const auto& s : strings)
		biMap[s];

	now2 = clock.now();
	OutputDuration("Access bidirectional map members by string", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	for (const auto& s : strings)
		std::find_if(map.cbegin(), map.cend(), [&s](const std::pair<int, std::string>& item) { return item.second == s; })->first;

	now2 = clock.now();
	OutputDuration("Access map members by string              ", now1, now2);


	std::cout << "*** string-int ***" << std::endl;

	now1 = clock.now();

	// evaluate bidirectional map generation
	auto biMap2 = GenerateBiMap<TBiMap>(stringIntPairs);

	now2 = clock.now();
	OutputDuration("Generate bidirectional map                ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map generation
	auto map2 = GenerateMap<TMap>(stringIntPairs);

	now2 = clock.now();
	OutputDuration("Generate map                              ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map access
	for (const auto& s : strings)
		biMap2[s];

	now2 = clock.now();
	OutputDuration("Access bidirectional map members by string", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map access
	for (const auto& s : strings)
		map2[s];

	now2 = clock.now();
	OutputDuration("Access map members by string              ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	for (int i = 0; i < numOfItems; ++i)
		biMap2[i];

	now2 = clock.now();
	OutputDuration("Access bidirectional map members by int   ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	for (int i = 0; i < numOfItems; ++i)
		std::find_if(map2.cbegin(), map2.cend(), [&](const std::pair<std::string, int>& item) { return item.second == i; })->first;

	now2 = clock.now();
	OutputDuration("Access map members by int                 ", now1, now2);
}
