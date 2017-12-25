#pragma once

#include <cassert>
#include <list>
#include <unordered_map>
#include <utility>

template <typename T1, typename T2> class BidirectionalUnorderedMap
{
	// static_assert(std::is_same<T1, T2>::value == false);

	template<typename T> struct PointerHash
	{
		std::size_t operator()(const T* t) const noexcept { return std::hash<T>{}(*t); }
	};

	template<typename T> struct PointerComparator
	{
		inline bool operator()(const T* t1, const T* t2) const noexcept { return *t1 == *t2; }
	};


	using Item = std::pair<T1, T2>;
	using Container = std::list<Item>;

public:
	BidirectionalUnorderedMap() = default;

	BidirectionalUnorderedMap(BidirectionalUnorderedMap&& other)
		: items(std::move(other.items))
		, map1(std::move(other.map1))
		, map2(std::move(other.map2))
	{  
	}

	virtual ~BidirectionalUnorderedMap() = default;

	template <typename T1, typename T2>
	bool Insert(T1 first, T2 second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return InsertPair(std::forward<T1>(first), std::forward<T2>(second));
	}

	template <typename T1, typename T2>
	bool Change(T1 first, T2 second)
	{
		assert(items.size() == map1.size());
		assert(items.size() == map2.size());
		return ChangeValue(std::forward<T1>(first), std::forward<T2>(second));
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

private:
	std::list<Item> items;
	std::unordered_map<const T1*, Item*, PointerHash<T1>, PointerComparator<T1>> map1;
	std::unordered_map<const T2*, Item*, PointerHash<T2>, PointerComparator<T2>> map2;

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