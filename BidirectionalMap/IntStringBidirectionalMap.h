#pragma once

#include <utility>
#include <string>
#include <list>
#include <map>
#include <cassert>

class IntStringBidirectionalMap
{
	template<typename T> struct PointerComparator
	{
		inline bool operator()(const T* t1, const T* t2) const noexcept { return *t1 < *t2; }
	};

	using Item = std::pair<int, std::string>;

public:
	IntStringBidirectionalMap() = default;
	virtual ~IntStringBidirectionalMap() = default;

	void emplace(int key, std::string val)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		items.emplace_back(key, val);
		Item& item = items.back();
		map1.emplace(&(item.first), &item);
		map2.emplace(&(item.second), &item);

		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
	}

	void clear()
	{
		items.clear();
		map1.clear();
		map2.clear();
	}

	size_t size() const
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return items.size();
	}

	std::string& operator[](const int& key) noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		if (map1.find(&key) == map1.end())
			emplace(key, "");
		return map1[&key]->second;
	}

	std::string& operator[](int&& key) noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		if (map1.find(&key) == map1.end())
			emplace(key, "");
		return map1[&key]->second;
	}

	int& operator[](const std::string& key) noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		if (map2.find(&key) == map2.end())
			emplace(0, key);
		return map2[&key]->first;
	}

	int& operator[](std::string&& key) noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		if (map2.find(&key) == map2.end())
			emplace(0, key);
		return map2[&key]->first;
	}

private:
	std::list<Item> items;
	std::map<const int*, Item*, PointerComparator<int>> map1;
	std::map<const std::string*, Item*, PointerComparator<std::string>> map2;


};

