// ConsoleApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CompareMapBimapAccess.h"
#include "../BidirectionalMap/BidirectionalMap.h"
#include "../BidirectionalMap/BidirectionalUnorderedMap.h"
#include "Person.h"

#include <iostream>
#include <cassert>
#include <map>
#include <unordered_map>

void TestBiMapCopyAssignmentAccess()
{
	BidirectionalMap<int, Person> bm;

	Person dora("Dora", "Sribar");
	bm.Insert(1, dora);
	bm.Insert(2, Person("Matej", "Sribar"));

	bm.Change(1, Person("Mihovil", "Spalj"));
	bm.Change(2, dora);
}

void TestBiUnorderedMapCopyAssignmentAccess()
{
	BidirectionalUnorderedMap<int, std::string> bum;

	bum.Insert(1, "Dora");
	bum.Insert(2, "Matej");

	assert(bum[2] == "Matej");

}

int main()
{
	//TestBiMapCopyAssignmentAccess();

	std::cout << "BidirectionalMap vs. std::map" << std::endl;
	CompareMapBiMapAccess<BidirectionalMap, std::map>();
	std::cout << std::endl << "BidirectionalUnorderedMap vs. std::unordered_map" << std::endl;
	CompareMapBiMapAccess<BidirectionalUnorderedMap, std::unordered_map>();

	//TestBiUnorderedMapCopyAssignmentAccess();

	std::cout << "Finished" << std::endl;
	char ch;
	std::cin >> ch;
	return 0;
}

