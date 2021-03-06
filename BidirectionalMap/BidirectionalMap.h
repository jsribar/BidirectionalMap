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

#include <list>
#include <map>
#include <unordered_map>
#include <utility>
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

		// copy constructor
		BidirectionalMapBase(const BidirectionalMapBase& other)
			: items(other.items)
		{
			BuildMaps();
		}

		// move constructor
		BidirectionalMapBase(BidirectionalMapBase&& other)
			: items(std::move(other.items))
			, map1(std::move(other.map1))
			, map2(std::move(other.map2))
		{
		}

		// initializer list constructor
		BidirectionalMapBase(std::initializer_list<value_type> il)
			: items{ il }
		{
			BuildMaps();
		}

		virtual ~BidirectionalMapBase() = default;

		// copy assignment
		BidirectionalMapBase& operator=(const BidirectionalMapBase& other)
		{
			items = items.other;
			BuildMaps();
			return *this;
		}

		// move assignment
		BidirectionalMapBase& operator=(BidirectionalMapBase&& other)
		{
			items = std::move(other.items);
			map1 = std::move(other.map1);
			map2 = std::move(other.map2);
			return *this;
		}

		// insert a new keypair
		template <typename Q, typename R>
		bool Insert(Q first, R second)
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			if (FirstExists(first))
			{
				// do not perform insertion if provided keypair already exists
				if (PairExists(first, second))
					return false;
				throw std::invalid_argument("First key already exists in the map.");
			}
			if (SecondExists(second))
				throw std::invalid_argument("Second key already exists in the map.");

			items.emplace_front(std::forward<Q>(first), std::forward<R>(second));
			auto it = items.begin();
			map1.emplace(&(it->first), it);
			map2.emplace(&(it->second), it);

			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			return true;
		}

		// change the first key paired to existing second key
		template <typename Q, typename R>
		bool ChangeFirst(Q first, R second)
		{
			if (!SecondExists(second))
				throw std::out_of_range("The second key must exist in the map.");
			return ChangeFirstKey(std::forward<Q>(first), std::forward<R>(second));
		}

		// change the second key paired to existing first key
		template <typename Q, typename R>
		bool ChangeSecond(Q first, R second)
		{
			if (!FirstExists(first))
				throw std::out_of_range("The first key must exist in the map.");
			return ChangeSecondKey(std::forward<Q>(first), std::forward<R>(second));
		}

		// remove a keypair which has given first key 
		void RemoveFirst(const T1& first)
		{
			auto itKey1 = map1.find(&first);
			if (itKey1 == map1.end())
				throw std::out_of_range("The first key must exist in the map.");
			auto itItem = itKey1->second;
			map2.erase(&(itItem->second));
			map1.erase(itKey1);
			items.erase(itItem);
		}

		// remove a keypair which has given second key 
		void RemoveSecond(const T2& second)
		{
			auto itKey2 = map2.find(&second);
			if (itKey2 == map2.end())
				throw std::out_of_range("The first key must exist in the map.");
			auto itItem = itKey2->second;
			map1.erase(&(itItem->first));
			map2.erase(itKey2);
			items.erase(itItem);
		}

		// clear the map
		void Clear() noexcept
		{
			items.clear();
			map1.clear();
			map2.clear();

			assert(items.size() == 0);
			assert(map1.size() == 0);
			assert(map2.size() == 0);
		}

		// get number of keypairs in the map
		size_t Size() const noexcept
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());

			return items.size();
		}

		// check if first key exists in the map
		bool FirstExists(const T1& first) const noexcept
		{
			return map1.find(&first) != map1.cend();
		}

		// check if second key exists in the map
		bool SecondExists(const T2& second) const noexcept
		{
			return map2.find(&second) != map2.cend();
		}

		// get the value assigned to given first key
		const T2& AtFirst(const T1& first) const
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			return map1.at(&first)->second;
		}

		// get the value assigned to given second key
		const T1& AtSecond(const T2& second) const
		{
			assert(items.size() == map1.size());
			assert(items.size() == map2.size());
			return map2.at(&second)->first;
		}

		// overloaded methods and operators available only when T1 and T2 are different types

		// get the value assigned to given first key using index operator
		const T2& operator[](const T1& first) const
		{
			return AtFirst(first);
		}

		// get the value assigned to given second key using index operator
		template <typename Q = T1, typename R = T2>
		typename std::enable_if<std::is_same<Q, R>::value == false, const Q&>::type
		operator[](const T2& second) const
		{
			return AtSecond(second);
		}

		// remove keypair with given first key
		void Remove(const T1& first)
		{
			RemoveFirst(first);
		}

		// remove keypair with given second key
		template <typename Q = T1, typename R = T2>
		typename std::enable_if<!std::is_same<Q, R>::value, void>::type
		Remove(const T2& second)
		{
			RemoveSecond(second);
		}

		// check if keypair with given first key exists
		bool Exists(const T1& first) const noexcept
		{
			return FirstExists(first);
		}

		// check if keypair with given second key exists
		template <typename Q = T1, typename R = T2>
		typename std::enable_if<!std::is_same<Q, R>::value, bool>::type
		Exists(const T2& second) const noexcept
		{
			return SecondExists(second);
		}

	private:
		Container items;
		TMap<const T1*, typename Container::iterator, TMapArgs<T1>...> map1;
		TMap<const T2*, typename Container::iterator, TMapArgs<T2>...> map2;

		void BuildMaps()
		{
			for (auto it = items.begin(); it != items.end(); ++it)
			{
				map1.emplace(&(it->first), it);
				map2.emplace(&(it->second), it);
			}
		}

		bool ChangeFirstKey(T1&& first, T2&& second)
		{
			assert(SecondExists(second));
			auto it1 = map1.find(&first);
			auto itItem = map2.find(&second)->second;
			// if first key already exists
			if (it1 != map1.end())
			{
				// if key is already assigned to the new first key, return false
				if (it1->second == itItem)
					return false;
				throw std::invalid_argument("First key is already assigned to another second key.");
			}
			// current first key must be removed from map1
			map1.erase(&itItem->first);
			// change first key in the pair
			itItem->first = std::forward<T1>(first);
			// new first key must be created
			map1.emplace(&(itItem->first), itItem);
			return true;
		}

		bool ChangeSecondKey(T1&& first, T2&& second)
		{
			assert(FirstExists(first));
			auto it2 = map2.find(&second);
			auto itItem = map1.find(&first)->second;
			// if second key already exists
			if (it2 != map2.end())
			{
				// if key is already assigned to the new second key, return false
				if (it2->second == itItem)
					return false;
				throw std::invalid_argument("Second key is already assigned to another first key.");
			}
			// current second key must be removed from map2
			map2.erase(&itItem->second);
			// change second key in the pair
			itItem->second = std::forward<T2>(second);
			// new second key must be created
			map2.emplace(&(itItem->second), itItem);
			return true;
		}

		bool PairExists(const T1& first, const T2& second) const noexcept
		{
			auto it1 = map1.find(&first);
			auto it2 = map2.find(&second);
			return it1 != map1.end() && it2 != map2.end() && it1->second == it2->second;
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
