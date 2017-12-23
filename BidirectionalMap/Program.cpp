// Program.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "BidirectionalMap.h"
#include "Person.h"

int main()
{
	BidirectionalMap<int, Person> bm;

	Person dora("Dora", "Sribar");
	bm.Insert(1, dora);
	bm.Insert(2, Person("Matej", "Sribar"));

	bm.Change(1, Person("Mihovil", "Spalj"));
	bm.Change(2, dora);

    return 0;
}

