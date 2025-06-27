#pragma once

#include "HeapsConcepts.hpp"
#include <vector>
#include <algorithm>

template <heaps_concepts::ComparableType ComparableVariable>
class binominal_tree {
public:
      binominal_tree() = default;


private:
      size_t degree;
      
};


template <heaps_concepts::ComparableType ComparableVariable>
class binominal_heap {
public:
      binominal_heap() = default;

      auto push(const ComparableVariable&& __value) -> void {
            __root_list.push_back(__value);
            
      }
      auto push(ComparableVariable&& __value) -> void {
            
      }

      auto extract_min() -> ComparableVariable {
            return std::ranges::min_element(__root_list);
      }
      auto merge() -> binominal_heap<ComparableVariable> {
            
      }
      

private:
      auto consolidate() -> void {}

      std::vector<binominal_tree<ComparableVariable>> __root_list;
};