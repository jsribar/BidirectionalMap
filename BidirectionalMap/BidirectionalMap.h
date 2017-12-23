#pragma once

#include <utility>
#include <list>
#include <map>
#include <cassert>

template <typename T1, typename T2> class BidirectionalMap
{
	template<typename T> struct PointerComparator
	{
		inline bool operator()(const T* t1, const T* t2) const noexcept { return *t1 < *t2; }
	};

	using Item = std::pair<T1, T2>;
	using Container = std::list<Item>;

public:
	BidirectionalMap() = default;
	virtual ~BidirectionalMap() = default;

	bool Emplace(const T1& first, const T2& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		if (FirstExists(first) || SecondExists(second))
			return false;

		items.emplace_back(first, second);
		Item& item = items.back();
		map1.emplace(&(item.first), &item);
		map2.emplace(&(item.second), &item);

		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return true;
	}

	//bool Emplace(T1&& first, T2&& second)
	//{
	//	assert(items.size() == map1.size());
	//	assert(items.size() == map2.size());

	//	if (FirstExists(first) || SecondExists(second))
	//		return false;

	//	items.emplace_back(std::forward<T1>(first), std::forward<T1>(second));
	//	Item& item = items.back();
	//	map1.emplace(&(item.first), &item);
	//	map2.emplace(&(item.second), &item);

	//	assert(items.size() == map1.size());
	//	assert(items.size() == map2.size());

	//	return true;
	//}

	bool Set(const T1& first, const T2& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		// return false if both keys exist or if none exists
		if (FirstExists(first) == SecondExists(second))
			return false;
		// if first key exists, then second will be changed. Old key must be removed from map2 and new created.
		if (FirstExists(first))
		{
			auto item = map1.find(&first)->second;
			map2.erase(&(item->second));
			item->second = second;
			map2.emplace(&(item->second), item);
		}
		// if second key exists, then first will be changed. Old key must be removed from map1 and new created.
		else if (SecondExists(second))
		{
			auto item = map2.find(&second)->second;
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

	bool FirstExists(const T1& first) const
	{
		return map1.find(&first) != map1.end();
	}

	bool SecondExists(const T2& second) const
	{
		return map2.find(&second) != map2.end();
	}

	const T2& operator[](const T1& first) const noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return map1.at(&first)->second;
	}

	const T1& operator[](const T2& second) const noexcept
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