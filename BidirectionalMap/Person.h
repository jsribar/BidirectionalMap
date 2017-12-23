#pragma once

#include <string>

class Person
{
public:
	Person(const std::string& name, const std::string& familyName);
	Person(const Person& other);
	Person(Person&& other);
	virtual ~Person();

	bool operator<(const Person& other) const;

private:
	std::string name;
	std::string familyName;
};

