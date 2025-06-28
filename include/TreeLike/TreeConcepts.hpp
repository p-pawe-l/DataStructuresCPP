#pragma once

#include <concepts>

namespace tree_concepts {
      template <typename A>
      concept ComparableType = requires (const A& a, const A& b) 
      {
            {a > b} -> std::convertible_to<bool>;
            {a < b} -> std::convertible_to<bool>;
      };
}