#pragma once

#include <string>

class Person
{
public:
	Person(const std::string& name, const std::string& familyName);
	Person(const Person& other);
	Person(Person&& other);
	virtual ~Person() = default;

	bool operator<(const Person& other) const;

	Person& operator=(const Person& other);
	Person& operator=(Person&& other);

private:
	std::string name;
	std::string familyName;
};

