#pragma once
#include "GenerateRandomStrings.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <boost/config.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

using Clock = std::chrono::high_resolution_clock;
using time_point = const std::chrono::time_point<Clock>;

void OutputDuration(const std::string& description, const time_point& start, const time_point& end)
{
	std::cout << description.c_str() << ": " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
}

template<template<typename... Args> class TBiMap, template<typename... Args> class TMap>
void CompareMapBidirectionalMapAccess(std::vector<std::string> strings)
{
	std::chrono::high_resolution_clock clock;

	std::cout << "*** int-string ***" << std::endl;

	auto now1 = clock.now();

	// evaluate boost bimap map generation
	typedef boost::bimap<boost::bimaps::unordered_set_of<int>, boost::bimaps::unordered_set_of<std::string>> intString_bimap;
	typedef intString_bimap::value_type positionIntString;
	intString_bimap boostBiMap;

	for (size_t i = 0; i < strings.size(); ++i)
		boostBiMap.insert(positionIntString(i, strings[i]));

	auto now2 = clock.now();
	OutputDuration("Generate boost bimap                      ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map generation
	TBiMap<int, std::string> biMap;
	for (size_t i = 0; i < strings.size(); ++i)
		biMap.Insert(i, strings[i]);

	now2 = clock.now();
	OutputDuration("Generate bidirectional map                ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map generation
	TMap<int, std::string> map;
	for (size_t i = 0; i < strings.size(); ++i)
		map.emplace(i, strings[i]);

	now2 = clock.now();
	OutputDuration("Generate map                              ", now1, now2);

	now1 = clock.now();

	// evaluate boos bidirectional map access
	for (size_t i = 0; i < strings.size(); ++i)
		boostBiMap.left.at(i);

	now2 = clock.now();
	OutputDuration("Access boost bimap members by int         ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map access
	for (size_t i = 0; i < strings.size(); ++i)
	{
		auto text = biMap.AtFirst(i);
		assert(text == strings[i]);
	}

	now2 = clock.now();
	OutputDuration("Access bidirectional map members by int   ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map access
	for (size_t i = 0; i < strings.size(); ++i)
	{
		auto text = map[i];
		assert(text == strings[i]);
	}

	now2 = clock.now();
	OutputDuration("Access map members by int                 ", now1, now2);

	now1 = clock.now();

	// evaluate boost bidirectional map reverse access
	for (size_t i = 0; i < strings.size(); ++i)
	{
		int a = boostBiMap.right.at(strings[i]);
		assert(a == i);
	}

	now2 = clock.now();
	OutputDuration("Access boost bimap members by string      ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	for (size_t i = 0; i < strings.size(); ++i)
	{
		int a = biMap.AtSecond(strings[i]);
		assert(a == i);
	}

	now2 = clock.now();
	OutputDuration("Access bidirectional map members by string", now1, now2);

	//now1 = clock.now();

	//// evaluate bidirectional map reverse access
	//for (const auto& s : strings)
	//	std::find_if(map.cbegin(), map.cend(), [&s](const std::pair<int, std::string>& item) { return item.second == s; })->first;

	//now2 = clock.now();
	//OutputDuration("Access map members by string              ", now1, now2);


	std::cout << "*** string-int ***" << std::endl;

	now1 = clock.now();

	// evaluate boost bidirectional map generation
	typedef boost::bimap<boost::bimaps::unordered_set_of<std::string>, boost::bimaps::unordered_set_of<int>> stringInt_bimap;
	typedef stringInt_bimap::value_type positionStringInt;
	stringInt_bimap boostBiMap2;

	for (size_t i = 0; i < strings.size(); ++i)
		boostBiMap2.insert(positionStringInt(strings[i], i));

	now2 = clock.now();
	OutputDuration("Generate boost bimap                      ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map generation
	TBiMap<std::string, int> biMap2;
	for (size_t i = 0; i < strings.size(); ++i)
		biMap2.Insert(strings[i], i);

	now2 = clock.now();
	OutputDuration("Generate bidirectional map                ", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map generation
	TMap<std::string, int> map2;
	for (size_t i = 0; i < strings.size(); ++i)
		map2.emplace(strings[i], i);

	now2 = clock.now();
	OutputDuration("Generate map                              ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map access
	for (size_t i = 0; i < strings.size(); ++i)
	{
		int a = boostBiMap2.left.at(strings[i]);
		assert(a == i);
	}

	now2 = clock.now();
	OutputDuration("Access boost bimap members by string      ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map access
	for (size_t i = 0; i < strings.size(); ++i)
	{
		int a = biMap2.AtFirst(strings[i]);
		assert(a == i);
	}

	now2 = clock.now();
	OutputDuration("Access bidirectional map members by string", now1, now2);

	now1 = clock.now();

	// evaluate ordinary map access
	for (size_t i = 0; i < strings.size(); ++i)
	{
		int a = map2[strings[i]];
		assert(a == i);
	}

	now2 = clock.now();
	OutputDuration("Access map members by string              ", now1, now2);

	now1 = clock.now();

	// evaluate boost bimap reverse access
	for (size_t i = 0; i < strings.size(); ++i)
		boostBiMap2.right.at(i);

	now2 = clock.now();
	OutputDuration("Access boost bimap members by int         ", now1, now2);

	now1 = clock.now();

	// evaluate bidirectional map reverse access
	for (size_t i = 0; i < strings.size(); ++i)
	{
		auto text = biMap2.AtSecond(i);
		assert(text == strings[i]);
	}

	now2 = clock.now();
	OutputDuration("Access bidirectional map members by int   ", now1, now2);

	//now1 = clock.now();

	//// evaluate bidirectional map reverse access
	//for (size_t i = 0; i < strings.size(); ++i)
	//	std::find_if(map2.cbegin(), map2.cend(), [&](const std::pair<std::string, int>& item) { return item.second == i; })->first;

	//now2 = clock.now();
	//OutputDuration("Access map members by int                 ", now1, now2);
}
