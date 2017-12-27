// ConsoleApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BidirectionalMap/BidirectionalMap.h"
#include "../BidirectionalMap/BidirectionalUnorderedMap.h"
#include "../BidirectionalMap/BidirectionalTMap.h"
#include "Person.h"

#include <iostream>
#include <cassert>

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

	//TestBiUnorderedMapCopyAssignmentAccess();

	BidirectionalMap1<int, std::string> bm;
	bm.Insert(1, "Dora");
	std::string dora = bm[1];
	int doraBroj = bm["Dora"];

	BidirectionalUnorderedMap1<int, std::string> bum;
	bum.Insert(1, "Dora");
	dora = bm[1];
	doraBroj = bm["Dora"];

	std::cout << "Finished" << std::endl;
	char ch;
	std::cin >> ch;
	return 0;
}

