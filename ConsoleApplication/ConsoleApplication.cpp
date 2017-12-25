// ConsoleApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../BidirectionalMap/BidirectionalMap.h"
#include "Person.h"
#include "CompareMapBimapAccess.h"

#include <iostream>

void TestCopyAssignmentAccess()
{
	BidirectionalMap<int, Person> bm;

	Person dora("Dora", "Sribar");
	bm.Insert(1, dora);
	bm.Insert(2, Person("Matej", "Sribar"));

	bm.Change(1, Person("Mihovil", "Spalj"));
	bm.Change(2, dora);
}

int main()
{
	CompareMapBiMapAccess();

	std::cout << "Finished" << std::endl;
	char ch;
	std::cin >> ch;
	return 0;
}

