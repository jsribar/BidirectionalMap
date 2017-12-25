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
	name = std::move(other.name);
	familyName = std::move(other.familyName);
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

Person& Person::operator=(const Person& other)
{
	name = other.name;
	familyName = other.familyName;
	return *this;
}

Person& Person::operator=(Person&& other)
{
	name = std::move(other.name);
	familyName = std::move(other.familyName);
	return *this;
}

