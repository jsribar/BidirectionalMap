#pragma once
#include <random>
#include <string>

class RandomStringGenerator
{
public:
	RandomStringGenerator(std::default_random_engine& random, size_t minLength, size_t maxLength);
	virtual ~RandomStringGenerator() = default;
	std::string operator()();

private:
	std::default_random_engine& random;
	size_t minLength;
	size_t maxLength;

	int GetNormalizedRandom(int lowerLimit, int upperLimit);
};

