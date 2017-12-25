#include "stdafx.h"
#include "RandomStringGenerator.h"

RandomStringGenerator::RandomStringGenerator(std::default_random_engine& random, size_t minLength, size_t maxLength)
	: random(random)
	, minLength(minLength)
	, maxLength(maxLength)
{
}

std::string RandomStringGenerator::operator()()
{
	size_t length = GetNormalizedRandom(minLength, maxLength);
	std::string result{};
	while (result.size() < length)
		result.push_back(static_cast<char>(GetNormalizedRandom('a', 'z')));
	return result;
}

int RandomStringGenerator::GetNormalizedRandom(int lowerLimit, int upperLimit)
{
	return random() % (upperLimit - lowerLimit + 1) + lowerLimit;
}
