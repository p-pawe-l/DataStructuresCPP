#pragma once

#include <vector>
#include <algorithm>

#include "HeapsConcepts.hpp"
#include "TreeLike/BinominalTree.hpp"

template <heaps_concepts::ComparableType ComparableVariable>
class binominal_heap {
public:
      binominal_heap() = default;

      auto push(const ComparableVariable&& __value) -> void {
      }
      auto push(ComparableVariable&& __value) -> void {
      }

      auto extract_min() -> ComparableVariable {
      }
      auto merge() -> binominal_heap<ComparableVariable> {
            
      }
      

private:
      auto consolidate() -> void {}

};