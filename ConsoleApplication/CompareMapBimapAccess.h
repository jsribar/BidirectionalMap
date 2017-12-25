#pragma once
#include "../BidirectionalMap/BidirectionalMap.h"
#include <map>
#include <utility>
#include <vector>

template<typename TKey, typename TValue>
BidirectionalMap<TKey, TValue> GenarateBiMap(const std::vector<std::pair<TKey, TValue>>& pairs);

template<typename TKey, typename TValue>
std::map<TKey, TValue> GenarateMap(const std::vector<std::pair<TKey, TValue>>& pairs);

void CompareMapBiMapAccess();

