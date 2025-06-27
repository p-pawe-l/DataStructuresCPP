#pragma once 

#include <concepts>
#include <algorithm>

namespace node_concepts {
      template <typename A, typename B>
      concept EdgeNodeContainer = 
            std::ranges::range<A> &&
            std::same_as<std::ranges::range_value_t<A>, B>;

      template <typename A, typename B>
      concept RelatedNodeContainer = 
            std::ranges::range<A> && 
            std::same_as<std::ranges::range_value_t<A>, B>;

      template <typename A>
      concept ComparableType = requires (const A& a, const A& b) 
      {
            { a < b } -> std::convertible_to<bool>;
            { a > b } -> std::convertible_to<bool>;
      };
}