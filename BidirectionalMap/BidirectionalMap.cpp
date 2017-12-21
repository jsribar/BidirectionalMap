// BidirectionalMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <utility>
#include <string>
#include <list>
#include <map>

class BidirectionalMap
{
	template<typename T> struct PointerComparator
	{
		inline bool operator()(const T* t1, const T* t2) const noexcept { return *t1 < *t2; }
	};

	using Item = std::pair<int, std::string>;

public:
	void emplace(int key, std::string val)
	{
		items.emplace_back(key, val);
		Item& item = items.back();
		map1.emplace(&(item.first), &item);
		map2.emplace(&(item.second), &item);
	}

	//const std::string& operator[](const int& key) const noexcept
	//{
	//	return map1.find(&key)->second->second;
	//}

	std::string& operator[](const int& key) noexcept
	{
		return map1[&key]->second;
	}

	std::string& operator[](int&& key) noexcept
	{
		if (map1.find(&key) == map1.end())
			emplace(key, "");
		return map1[&key]->second;
	}

	//const int operator[](const std::string& key) const noexcept
	//{
	//	return map2.find(&key)->second->first;
	//}

	int operator[](const std::string& key) noexcept
	{
		return map2[&key]->first;
	}

	int operator[](std::string&& key) noexcept
	{
		return map2[&key]->first;
	}

private:
	std::list<Item> items;
	std::map<const int*, Item*, PointerComparator<int>> map1;
	std::map<const std::string*, Item*, PointerComparator<std::string>> map2;
};

int main()
{
	BidirectionalMap bm;
	bm.emplace(5, "hello");
	bm.emplace(6, "world");
	bm.emplace(10, "pozdrav");
	std::string value = bm[5];
	int i = bm["hello"];
	bm[5] = "Dobar dan";
	i = bm["Dobar dan"];
	
	bm[4] = "Guten Tag";
	i = bm["world"];
	i = bm["pozdrav"];

	//SneakyBimap<int, std::string> sb;
	//sb.emplace(10, "banana");
	//sb["banana"] = 25;
	//sb["banana"] = 15;
	//sb[15] = "melon";
	//sb.emplace(10, "cucumber");
	//sb.clear();

    return 0;
}

