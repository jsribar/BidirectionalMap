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

	const std::string& GetName() const noexcept { return name; }
	const std::string& GetFamilyName() const noexcept { return familyName; }

private:
	std::string name;
	std::string familyName;
};

inline bool operator==(const Person& lhs, const Person& rhs)
{ 
	return lhs.GetName() == rhs.GetName() && lhs.GetFamilyName() == rhs.GetFamilyName();
}

