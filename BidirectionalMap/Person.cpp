#include "stdafx.h"
#include "Person.h"
#include <utility>


Person::Person(const std::string& name, const std::string& familyName)
	: name(name)
	, familyName(familyName)
{
}

Person::Person(const Person& other)
	: name(other.name)
	, familyName(other.familyName)
{
}

Person::Person(Person&& other)
{
	std::exchange(name, other.name);
	std::exchange(familyName, other.familyName);
}

Person::~Person()
{
}


bool Person::operator<(const Person& other) const
{
	int result = familyName.compare(other.familyName);
	if (result == 0)
		result = name.compare(other.name);
	return result < 0;
}

