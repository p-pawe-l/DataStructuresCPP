#pragma once

#include <concepts>
#include <type_traits>

namespace tree_concepts {
      template <typename A>
      concept ComparableType = requires (const A& a, const A& b) 
      {
            {a > b} -> std::convertible_to<bool>;
            {a < b} -> std::convertible_to<bool>;
      };
}