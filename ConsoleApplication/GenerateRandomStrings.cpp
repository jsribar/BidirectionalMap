#include "stdafx.h"
#include "GenerateRandomStrings.h"
#include "RandomStringGenerator.h"
#include <random>
#include <set>

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

