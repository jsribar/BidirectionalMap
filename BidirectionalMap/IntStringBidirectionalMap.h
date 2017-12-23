#pragma once

#include <utility>
#include <string>
#include <list>
#include <map>
#include <cassert>
//#include <iterator>

class IntStringBidirectionalMap
{
	template<typename T> struct PointerComparator
	{
		inline bool operator()(const T* t1, const T* t2) const noexcept { return *t1 < *t2; }
	};

	using Item = std::pair<int, std::string>;
	using Container = std::list<Item>;

public:
	IntStringBidirectionalMap() = default;
	virtual ~IntStringBidirectionalMap() = default;

	bool Emplace(const int& first, const std::string& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		if (Exists(first) || Exists(second))
			return false;
		
		items.emplace_back(first, second);
		Item* pItem = &items.back();
		map1.emplace(&(pItem->first), pItem);
		map2.emplace(&(pItem->second), pItem);

		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return true;
	}

	bool Emplace(int&& first, std::string&& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		if (Exists(first) || Exists(second))
			return false;

		items.emplace_back(std::forward<int>(first), std::forward<std::string>(second));
		Item& item = items.back();
		map1.emplace(&(item.first), &item);
		map2.emplace(&(item.second), &item);

		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return true;
	}


	bool Set(const int& first, const std::string& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		auto map1Item = map1.find(&first);
		bool firstExists = map1Item != map1.end();
		auto map2Item = map2.find(&second);
		bool secondExists = map2Item != map2.end();
		// return false if both keys exist or if none exists
		if (firstExists == secondExists)
			return false;
		// if first key exists, then second will be changed. Old key must be removed from map2 and new created.
		if (firstExists)
		{
			auto pItem = map1Item->second;
			map2.erase(&(pItem->second));
			pItem->second = second;
			map2.emplace(&(pItem->second), pItem);
		}
		// if second key exists, then first will be changed. Old key must be removed from map1 and new created.
		else if (secondExists)
		{
			auto pItem = map2Item->second;
			map1.erase(&(pItem->first));
			pItem->first = first;
			map1.emplace(&(pItem->first), pItem);
		}

		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return true;
	}

	void Clear()
	{
		items.clear();
		map1.clear();
		map2.clear();

		assert(items.size() == 0);
		assert(map1.size() == 0);
		assert(map2.size() == 0);
	}

	size_t Size() const
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return items.size();
	}

	bool Exists(const int& first) const
	{
		return map1.find(&first) != map1.end();
	}

	bool Exists(const std::string& second)
	{
		return map2.find(&second) != map2.end();
	}

	const std::string& operator[](const int& first) const noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return map1.at(&first)->second;
	}

	const int& operator[](const std::string& second) const noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return map2.at(&second)->first;
	}

private:
	std::list<Item> items;
	std::map<const int*, Item*, PointerComparator<int>> map1;
	std::map<const std::string*, Item*, PointerComparator<std::string>> map2;
};

