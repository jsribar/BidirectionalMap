// Program.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "BidirectionalMap.h"
#include "Person.h"

int main()
{
	BidirectionalMap<int, Person> bm;

	Person p("Dora", "Sribar");
	bm.Emplace(1, p);
	bm.Emplace(2, Person("Matej", "Sribar"));

    return 0;
}

