#pragma once

#include <utility>
#include <list>
#include <map>
#include <cassert>

template <typename T1, typename T2> class BidirectionalMap
{
	// static_assert(std::is_same<T1, T2>::value == false);

	template<typename T> struct PointerComparator
	{
		inline bool operator()(const T* t1, const T* t2) const noexcept { return *t1 < *t2; }
	};

	using Item = std::pair<T1, T2>;
	using Container = std::list<Item>;

public:
	BidirectionalMap() = default;

	BidirectionalMap(BidirectionalMap&& other)
		: items(std::move(other.items))
		, map1(std::move(other.map1))
		, map2(std::move(other.map2))
	{
	}

	virtual ~BidirectionalMap() = default;

	bool Insert(const T1& first, const T2& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return InsertPair(first, second);
	}

	bool Insert(T1&& first, T2&& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return InsertPair(std::forward<T1>(first), std::forward<T2>(second));
	}

	bool Insert(const T1& first, T2&& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return InsertPair(first, std::forward<T2>(second));
	}

	bool Insert(T1&& first, const T2& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return InsertPair(std::forward<T1>(first), second);
	}

	bool Change(const T1& first, const T2& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return ChangeValue(first, second);
	}

	bool Change(T1&& first, T2&& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return ChangeValue(std::forward<T1>(first), std::forward<T2>(second));
	}

	bool Change(const T1& first, T2&& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return ChangeValue(first, std::forward<T2>(second));
	}

	bool Change(T1&& first, const T2& second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return ChangeValue(std::forward<T1>(first), second);
	}

	void Clear() noexcept
	{
		items.clear();
		map1.clear();
		map2.clear();

		assert(items.size() == 0);
		assert(map1.size() == 0);
		assert(map2.size() == 0);
	}

	bool Remove(const T1& first)
	{
		const auto& key1 = map1.find(&first);
		if (key1 == map1.end())
			return false;
		const Item* pItem = key1->second;
		map2.erase(&(pItem->second));
		map1.erase(key1);
		items.remove(*pItem);
		return true;
	}

	bool Remove(const T2& second)
	{
		const auto& key2 = map2.find(&second);
		if (key2 == map2.end())
			return false;
		const Item* pItem = key2->second;
		map1.erase(&(pItem->first));
		map2.erase(key2);
		items.remove(*pItem);
		return true;
	}

	size_t Size() const noexcept
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());

		return items.size();
	}

	bool FirstExists(const T1& first) const noexcept
	{
		return map1.find(&first) != map1.end();
	}

	bool SecondExists(const T2& second) const noexcept
	{
		return map2.find(&second) != map2.end();
	}

	const T2& operator[](const T1& first) const
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return map1.at(&first)->second;
	}

	const T1& operator[](const T2& second) const
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return map2.at(&second)->first;
	}

private:
	std::list<Item> items;
	std::map<const T1*, Item*, PointerComparator<T1>> map1;
	std::map<const T2*, Item*, PointerComparator<T2>> map2;

	bool InsertPair(T1 first, T2 second)
	{
		if (FirstExists(first) || SecondExists(second))
			return false;

		items.emplace_back(std::forward<T1>(first), std::forward<T2>(second));
		Item& item = items.back();
		map1.emplace(&(item.first), &item);
		map2.emplace(&(item.second), &item);

		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return true;
	}

	bool ChangeValue(T1 first, T2 second)
	{
		// return false if both keys exist or if none exists
		if (FirstExists(first) == SecondExists(second))
			return false;
		// if first key exists, then second will be changed
		if (FirstExists(first))
			ChangeSecond(std::forward<T1>(first), std::forward<T2>(second));
		// if second key exists, then first will be changed. Old first key must be removed from map1 and new created.
		else
			ChangeFirst(std::forward<T1>(first), std::forward<T2>(second));

		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return true;
	}

	void ChangeSecond(T1 first, T2 second)
	{
		// old second key must be removed from map2 and new created
		auto item = map1.find(&first)->second;
		map2.erase(&(item->second));
		item->second = std::forward<T2>(second);
		map2.emplace(&(item->second), item);
	}

	void ChangeFirst(T1 first, T2 second)
	{
		// old first key must be removed from map1 and new created
		auto item = map2.find(&second)->second;
		map1.erase(&(item->first));
		item->first = std::forward<T1>(first);
		map1.emplace(&(item->first), item);
	}
};