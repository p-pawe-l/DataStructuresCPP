#pragma once

#include <concepts>

namespace heaps_concepts {
      template <typename Type>
	concept ComparableType = requires(const Type& a, const Type& b) 
	{
		{ a < b } -> std::convertible_to<bool>;
		{ a > b } -> std::convertible_to<bool>;
	};

      template <typename CompareVar, typename Type>
      concept SupportsComparison = requires (const CompareVar& compare_function, const Type& a, const Type& b) 
      {
            { compare_function(a, b) } -> std::convertible_to<bool>;
      };

}