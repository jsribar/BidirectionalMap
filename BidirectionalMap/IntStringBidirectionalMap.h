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
	using ContainerIterator = Container::iterator;

public:
	IntStringBidirectionalMap() = default;
	virtual ~IntStringBidirectionalMap() = default;

	bool Emplace(int key, const std::string& val)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		bool keyExists = map1.find(&key) != map1.end();
		bool valueExists = map2.find(&val) != map2.end();
		if (keyExists || valueExists)
			return false;
		
		items.emplace_back(key, val);
		Item& item = items.back();
		map1.emplace(&(item.first), &item);
		map2.emplace(&(item.second), &item);

		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return true;
	}

	bool Set(int first, const std::string& second)
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
			auto item = map1Item->second;
			map2.erase(&(item->second));
			item->second = second;
			map2.emplace(&(item->second), item);
		}
		// if second key exists, then first will be changed. Old key must be removed from map1 and new created.
		else if (secondExists)
		{
			auto item = map2Item->second;
			map1.erase(&(item->first));
			item->first = first;
			map1.emplace(&(item->first), item);
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

