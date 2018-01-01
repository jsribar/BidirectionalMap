// ConsoleApplication.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../BidirectionalMap/BidirectionalMap.h"

#include "Person.h"

#include <iostream>
#include <cassert>

using namespace MapSpecial;

void TestBidirectionalMapCopyMoveAssignment()
{
	BidirectionalMap<int, Person> bm;

	Person dora("Dora", "Sribar");
	bm.Insert(1, dora);
	bm.Insert(2, Person("Matej", "Sribar"));

	bm.ChangeSecond(1, Person("Mihovil", "Spalj"));
	bm.ChangeFirst(3, Person("Mihovil", "Spalj"));

	bm.ChangeSecond(3, dora);
}

void BidirectionalMapFunctionality()
{
	std::cout << "BidirectionalMap" << std::endl;

	BidirectionalMap<int, std::string> bm;

	bm.Insert(1, "Dora"); // insert a new pair
	bm.Insert(2, "Matej"); // insert a new pair

	std::cout << "[2]=" << bm[2].c_str() << std::endl; // output second value paired with first value 2
	std::cout << "[\"Dora\"]=" << bm["Dora"] << std::endl; // output first value paired with second value "Dora"

	bm.ChangeFirst(3, "Matej"); // change the first value in an existing pair that has second value "Matej"
	bm.ChangeSecond(1, "Vedran"); // change the second value in an existing pair that has first value 1

	bm.Remove("Vedran"); // remove pair that has second value "Vedran"
	bm.Remove(3); // remove pair that has first value 3

	bm.Insert(3, "Vedran");

	std::cout << "Exists(3)=" << bm.FirstExists(3) << std::endl; // check that a pair with value 3 exists
	std::cout << "Exists(\"Dora\")=" << bm.SecondExists("Dora") << std::endl; // check that a pair with value "Dora" exists

	std::cout << "Size()=" << bm.Size() << std::endl; // output the number of pairs

	bm.Clear(); // clear the container
}

void BidirectionalUnorderedMapFunctionality()
{
	std::cout << "BidirectionalUnorderedMap" << std::endl;

	BidirectionalUnorderedMap<int, std::string> bum;

	bum.Insert(1, "Dora"); // insert a new pair of values
	bum.Insert(2, "Matej"); // insert a new pair of values

	std::cout << "[2]=" << bum[2].c_str() << std::endl; // output second value paired with first value 2
	std::cout << "[\"Dora\"]=" << bum["Dora"] << std::endl; // output first value paired with second value "Dora"

	bum.ChangeFirst(3, "Matej"); // change the first value in an existing pair that has second value "Matej"
	bum.ChangeSecond(1, "Vedran"); // change the second value in an existing pair that has first value 1

	bum.Remove("Vedran"); // remove pair that has second value "Vedran"
	bum.Remove(3); // remove pair that has first value 3

	bum.Insert(3, "Vedran");

	std::cout << "Exists(3)=" << bum.FirstExists(3) << std::endl; // check that a pair with value 3 exists
	std::cout << "Exists(\"Dora\")=" << bum.SecondExists("Dora") << std::endl; // check that a pair with value "Dora" exists

	std::cout << "Size()=" << bum.Size() << std::endl; // output the number of pairs

	bum.Clear(); // clear the container
}

void BidirectionalMapOfSameTypesFunctionality()
{
	std::cout << "BidirectionalMap" << std::endl;

	BidirectionalMap<std::string, std::string> bm;

	bm.Insert("Roof", "Dach"); // insert a new pair
	bm.Insert("Home", "Heim"); // insert a new pair

    std::cout << "[\"Home\"]=" << bm["Home"].c_str() << std::endl; // output second value paired with "Home"

	bm.ChangeSecond("Home", "Haus"); // change the second value in an existing pair that has first value "Home"

	bm.RemoveFirst("Roof"); // remove pair that has first value "Roof"

	bm.Insert("Car", "Auto");

	std::cout << "FirstExists(\"Car\")=" << bm.FirstExists("Car") << std::endl; // check that a pair with first value "Car" exists
	std::cout << "SecondExists(\"Auto\")=" << bm.SecondExists("Auto") << std::endl; // check that a pair with second value "Auto" exists

	std::cout << "Size()=" << bm.Size() << std::endl; // output the number of pairs

	bm.Clear(); // clear the container
}

int main()
{
	TestBidirectionalMapCopyMoveAssignment();
	BidirectionalMapFunctionality();
	BidirectionalMapOfSameTypesFunctionality();
	BidirectionalUnorderedMapFunctionality();

	std::cout << std::endl << "Finished" << std::endl;
	char ch;
	std::cin >> ch;
	return 0;
}

