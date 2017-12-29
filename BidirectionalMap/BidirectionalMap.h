#pragma once

/*
Copyright(c) 2017 Julijan Šribar

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software.If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include <utility>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <cassert>

namespace MapSpecial
{

	template<typename T> struct DereferencedPointerComparator
	{
		bool operator()(const T* t1, const T* t2) const noexcept { return *t1 < *t2; }
	};

	template<typename T> struct DereferencedPointerHash
	{
		std::size_t operator()(const T* t) const noexcept { return std::hash<T>{}(*t); }
	};

	template<typename T> struct DereferencedPointerEquality
	{
		bool operator()(const T* t1, const T* t2) const noexcept { return *t1 == *t2; }
	};


	template<typename T1, typename T2, template<typename TKey, typename TValue, typename ...Args> class TMap, template<typename T> class ...TMapArgs>
	class BidirectionalMapBase
	{
	protected:
		using value_type = std::pair<T1, T2>;
		using Container = std::forward_list<value_type>;

	public:
		BidirectionalMapBase() = default;

		BidirectionalMapBase(const BidirectionalMapBase& other)
			: items(other.items)
		{
			BuildMaps();
		}

		BidirectionalMapBase(BidirectionalMapBase&& other)
			: items(std::move(other.items))
			, map1(std::move(other.map1))
			, map2(std::move(other.map2))
		{
		}

		BidirectionalMapBase(std::initializer_list<value_type> il)
			: items{ il }
		{
			BuildMaps();
		}

		virtual ~BidirectionalMapBase() = default;

		BidirectionalMapBase& operator=(const BidirectionalMapBase& other)
		{
			items = items.other;
			BuildMaps();
			return *this;
		}

		BidirectionalMapBase& operator=(BidirectionalMapBase&& other)
		{
			items = std::move(other.items);
			map1 = std::move(other.map1);
			map2 = std::move(other.map2);
			return *this;
		}

		template <typename T1, typename T2>
		bool Insert(T1 first, T2 second)
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			// do not perform insertion if any key already exists
			if (FirstExists(first) || SecondExists(second))
				return false;
			return InsertPair(std::forward<T1>(first), std::forward<T2>(second));
		}

		template <typename T1, typename T2>
		bool Change(T1 first, T2 second)
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			// return false if both keys exist or if none exists
			if (FirstExists(first) == SecondExists(second))
				return false;
			return ChangeValue(std::forward<T1>(first), std::forward<T2>(second));
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

		bool RemoveFirst(const T1& first)
		{
			const auto& key1 = map1.find(&first);
			if (key1 == map1.end())
				return false;
			const value_type* pItem = key1->second;
			map2.erase(&(pItem->second));
			map1.erase(key1);
			items.remove(*pItem);
			return true;
		}

		bool RemoveSecond(const T2& second)
		{
			const auto& key2 = map2.find(&second);
			if (key2 == map2.end())
				return false;
			const value_type* pItem = key2->second;
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

		const T2& AtFirst(const T1& first) const
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			return map1.at(&first)->second;
		}

		const T1& AtSecond(const T2& second) const
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			return map2.at(&second)->first;
		}

		// methods and operators available only when T1 and T2 are different types

		typename std::enable_if<!std::is_same<T1, T2>::value, const T2&>::type
		operator[](const T1& first) const
		{
			return AtFirst(first);
		}

		typename std::enable_if<!std::is_same<T1, T2>::value, const T1&>::type
		operator[](const T2& second) const
		{
			return AtSecond(second);
		}

		typename std::enable_if<!std::is_same<T1, T2>::value, bool>::type
		Remove(const T1& first)
		{
			return RemoveFirst(first);
		}

		typename std::enable_if<!std::is_same<T1, T2>::value, bool>::type
		Remove(const T2& second)
		{
			return RemoveSecond(second);
		}

		typename std::enable_if<!std::is_same<T1, T2>::value, bool>::type
		Exists(const T1& first) const noexcept
		{
			return FirstExists(first);
		}

		typename std::enable_if<!std::is_same<T1, T2>::value, bool>::type
		Exists(const T2& second) const noexcept
		{
			return SecondExists(second);
		}

	private:
		std::list<value_type> items;
		TMap<const T1*, value_type*, TMapArgs<T1>...> map1;
		TMap<const T2*, value_type*, TMapArgs<T2>...> map2;

		void BuildMaps()
		{
			for (value_type& item : items)
			{
				map1.emplace(&(item.first), &item);
				map2.emplace(&(item.second), &item);
			}
		}

		template <typename T1, typename T2>
		bool InsertPair(T1 first, T2 second)
		{
			items.emplace_back(std::forward<T1>(first), std::forward<T2>(second));
			value_type& item = items.back();
			map1.emplace(&(item.first), &item);
			map2.emplace(&(item.second), &item);

			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			return true;
		}

		template <typename T1, typename T2>
		bool ChangeValue(T1 first, T2 second)
		{
			// if first key already exists, then second will be changed
			if (FirstExists(first))
				ChangeSecond(std::forward<T1>(first), std::forward<T2>(second));
			// if second key already exists, then first will be changed
			else
				ChangeFirst(std::forward<T1>(first), std::forward<T2>(second));

			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			return true;
		}

		void ChangeSecond(T1 first, T2 second)
		{
			auto item = map1.find(&first)->second;
			// current second key must be removed from map2
			map2.erase(&(item->second));
			// change second value in the pair
			item->second = std::forward<T2>(second);
			// new second key must be created
			map2.emplace(&(item->second), item);
		}

		void ChangeFirst(T1 first, T2 second)
		{
			auto item = map2.find(&second)->second;
			// current first key must be removed from map1 
			map1.erase(&(item->first));
			// change first value in the pair
			item->first = std::forward<T1>(first);
			// new first key must be created
			map1.emplace(&(item->first), item);
		}
	}; // class BidirectionalMapBase

	// specialization for std::map
	template <typename T1, typename T2>
	class BidirectionalMap : public BidirectionalMapBase<T1, T2, std::map, DereferencedPointerComparator>
	{
	public:
		// Inherit all constructors from base class
		using BidirectionalMapBase<T1, T2, std::map, DereferencedPointerComparator>::BidirectionalMapBase;
	};

	// specialization for std::unordered_map
	template <typename T1, typename T2>
	class BidirectionalUnorderedMap : public BidirectionalMapBase<T1, T2, std::unordered_map, DereferencedPointerHash, DereferencedPointerEquality>
	{
	public:
		// Inherit all constructors from base class
		using BidirectionalMapBase<T1, T2, std::unordered_map, DereferencedPointerHash, DereferencedPointerEquality>::BidirectionalMapBase;
	};

} // namespace MapSpecial