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

	bool Set(int key, const std::string& val)
	{
		bool keyExists = map1.find(&key) != map1.end();
		bool valueExists = map2.find(&val) != map2.end();
		if (keyExists == valueExists)
			return false;
		if (keyExists)
		{
			auto item = map1.find(&key);
			map2.erase(&(item->second->second));
			item->second->second = val;
			map2.emplace(&val, item->second);
		}
		else if (valueExists)
		{
			auto item = map2.find(&val);
			map1.erase(&(item->second->first));
			item->second->first = key;
			map1.emplace(&key, item->second);
		}
		return true;
	}

	void Clear()
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

	const std::string& operator[](const int& key) const noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		const auto& item = map1.at(&key);
		return item->second;
	}

	const int& operator[](const std::string& key) const noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		const auto& item = map2.at(&key);
		return item->first;
	}

private:
	std::list<Item> items;
	std::map<const int*, Item*, PointerComparator<int>> map1;
	std::map<const std::string*, Item*, PointerComparator<std::string>> map2;
};

