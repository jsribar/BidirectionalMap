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
#include <list>
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
		using Container = std::list<value_type>;

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

		bool Insert(const T1& first, const T2& second)
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			// do not perform insertion if any key already exists
			if (FirstExists(first))
			{
				if (map1.find(&first)->second->second == second)
					return false;
				throw std::invalid_argument("First key already exists in the map.");
			}
			if (SecondExists(second))
			{
				if (map2.find(&second)->second->first == first)
					return false;
				throw std::invalid_argument("Second key already exists in the map.");
			}
			return InsertPair(first, second);
		}

		// change the first value paired to existing second value
		bool ChangeFirst(const T1& first, const T2& second)
		{
			if (!SecondExists(second))
				throw std::out_of_range("The second key must exist in the map.");
			return ChangeFirstValue(first, second);
		}

		// change the second value paired to existing first value
		bool ChangeSecond(const T1& first, const T2& second)
		{
			if (!FirstExists(first))
				throw std::out_of_range("The first key must exist in the map.");
			return ChangeSecondValue(first, second);
		}

		template <typename Q, typename R>
		bool Change(Q first, R second)
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			// throw exception if neither first nor second value exist
			if (!FirstExists(first) && !SecondExists(second))
				throw std::out_of_range("At least one key provided must exist already in the map.");
			// if first key already exists, then second has to be changed
			if (FirstExists(first))
				return ChangeSecondValue(std::forward<Q>(first), std::forward<R>(second));
			// if second key already exists, then first will be changed
			return ChangeFirstValue(std::forward<Q>(first), std::forward<R>(second));
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
			const auto& itKey1 = map1.find(&first);
			if (itKey1 == map1.end())
				return false;
			const value_type* pItem = itKey1->second;
			map2.erase(&(pItem->second));
			map1.erase(itKey1);
			items.remove(*pItem);
			return true;
		}

		bool RemoveSecond(const T2& second)
		{
			const auto& itKey2 = map2.find(&second);
			if (itKey2 == map2.cend())
				return false;
			const value_type* pItem = itKey2->second;
			map1.erase(&(pItem->first));
			map2.erase(itKey2);
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
			return map1.find(&first) != map1.cend();
		}

		bool SecondExists(const T2& second) const noexcept
		{
			return map2.find(&second) != map2.cend();
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

		// overloaded methods and operators available only when T1 and T2 are different types

		const T2& operator[](const T1& first) const
		{
			return AtFirst(first);
		}

		template <typename Q = T1, typename R = T2>
		typename std::enable_if<std::is_same<Q, R>::value == false, const Q&>::type
		operator[](const T2& second) const
		{
			return AtSecond(second);
		}

		bool Remove(const T1& first)
		{
			return RemoveFirst(first);
		}

		template <typename Q = T1, typename R = T2>
		typename std::enable_if<!std::is_same<Q, R>::value, bool>::type
		Remove(const T2& second)
		{
			return RemoveSecond(second);
		}

		bool Exists(const T1& first) const noexcept
		{
			return FirstExists(first);
		}

		template <typename Q = T1, typename R = T2>
		typename std::enable_if<!std::is_same<Q, R>::value, bool>::type
		Exists(const T2& second) const noexcept
		{
			return SecondExists(second);
		}

	private:
		Container items;
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

		template <typename Q, typename R>
		bool InsertPair(Q first, R second)
		{
			items.emplace_back(std::forward<Q>(first), std::forward<R>(second));
			value_type& item = items.back();
			map1.emplace(&(item.first), &item);
			map2.emplace(&(item.second), &item);

			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			return true;
		}

		bool ChangeFirstValue(const T1& first, const T2& second)
		{
			value_type* item = map2.find(&second)->second;
			if (FirstExists(first))
			{
				// if value is already assigned, return false
				if (item->first == first)
					return false;
				throw std::invalid_argument("First value is already assigned to another second value.");
			}
			// current first key must be removed from map1
			map1.erase(&(item->first));
			// change first value in the pair
			item->first = first;
			// new first key must be created
			map1.emplace(&(item->first), item);
			return true;
		}

		bool ChangeSecondValue(const T1& first, const T2& second)
		{
			value_type* item = map1.find(&first)->second;
			// if nothing to change, return false
			if (SecondExists(second))
			{
				// if value is already assigned, return false
				if (item->second == second)
					return false;
				throw std::invalid_argument("Second value is already assigned to another first value.");
			}
			// current second key must be removed from map2
			map2.erase(&(item->second));
			// change second value in the pair
			item->second = second;
			// new second key must be created
			map2.emplace(&(item->second), item);
			return true;
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
