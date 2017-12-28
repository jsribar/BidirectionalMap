// ConsoleApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BidirectionalMap/BidirectionalMap.h"
#include "Person.h"

#include <iostream>
#include <cassert>

using namespace MapSpecial;

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
	std::list<int> list1{ 1, 2, 3, 4 };
	std::list<int> list2(list1);


	MapSpecial::BidirectionalMap<int, std::string> bm;
	bm.Insert(1, "Dora");
	std::string dora = bm[1];
	int doraBroj = bm["Dora"];

	MapSpecial::BidirectionalUnorderedMap<int, std::string> bum;
	bum.Insert(1, "Dora");
	dora = bm[1];
	doraBroj = bm["Dora"];

	std::cout << "Finished" << std::endl;
	char ch;
	std::cin >> ch;
	return 0;
}

