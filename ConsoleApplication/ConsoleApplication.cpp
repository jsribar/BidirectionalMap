// ConsoleApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BidirectionalMap/BidirectionalMap.h"
#include "../BidirectionalMap/Person.h"
#include "../BidirectionalMap/RandomStringGenerator.h"
#include <vector>
#include <string>
#include <set>
#include <chrono>
#include <iostream>

void TestCopyAssignmentAccess()
{
	BidirectionalMap<int, Person> bm;

	Person dora("Dora", "Sribar");
	bm.Insert(1, dora);
	bm.Insert(2, Person("Matej", "Sribar"));

	bm.Change(1, Person("Mihovil", "Spalj"));
	bm.Change(2, dora);
}

std::vector<std::string> GenerateRandomStrings(size_t number)
{
	std::default_random_engine random;
	RandomStringGenerator generator(random, 4, 12);
	std::set<std::string> stringSet;
	while (stringSet.size() < number)
	{
		stringSet.emplace(generator());
	}
	return std::vector<std::string>(stringSet.begin(), stringSet.end());
}

BidirectionalMap<int, std::string> GenarateBiMap(const std::vector<std::string>& strings)
{
	BidirectionalMap<int, std::string> map;
	for (size_t i = 0; i < strings.size(); ++i)
		map.Insert(i, strings[i]);
	return map;
}

std::map<int, std::string> GenarateMap(const std::vector<std::string>& strings)
{
	std::map<int, std::string> map;
	for (size_t i = 0; i < strings.size(); ++i)
		map.emplace(i, strings[i]);
	return map;
}

void CompareMapBiMapAccess()
{
	constexpr int numOfItems = 50000;

	std::default_random_engine random;
	auto strings = GenerateRandomStrings(numOfItems);

	std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> times;
	std::chrono::high_resolution_clock clock;

	times.emplace_back(clock.now());

	// evaluate bidirectional map generation
	auto biMap = GenarateBiMap(strings);

	times.emplace_back(clock.now());

	// evaluate ordinary map generation
	auto map = GenarateMap(strings);

	times.emplace_back(clock.now());

	// evaluate bidirectional map access
	size_t totalLength{ 0 };
	for (int i = 0; i < numOfItems; ++i)
		totalLength += biMap[i].size();

	times.emplace_back(clock.now());

	// evaluate ordinary map access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += map[i].size();

	times.emplace_back(clock.now());

	// evaluate bidirectional map reverse access
	totalLength =  0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += biMap[strings[i]];

	times.emplace_back(clock.now());

	// evaluate bidirectional map reverse access
	totalLength = 0;
	for (int i = 0; i < numOfItems; ++i)
		totalLength += std::find_if(map.cbegin(), map.cend(), [&](const std::pair<int, std::string>& item) { return item.second == strings[i]; })->first;

	times.emplace_back(clock.now());

	std::cout << totalLength << std::endl << std::endl;

	for (size_t i = 1; i < times.size(); ++i)
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(times[i] - times[i - 1]).count() << std::endl;
}

int main()
{
	CompareMapBiMapAccess();

	std::cout << "Finished" << std::endl;
	char ch;
	std::cin >> ch;
	return 0;
}

