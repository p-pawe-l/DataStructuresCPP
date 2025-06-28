#pragma once

#include <concepts>
#include <type_traits>
#include <algorithm>

namespace list_concepts {
	template <typename A, typename B>
	concept ContainerOf =
		std::ranges::range<A> &&
		std::same_as<std::ranges::range_value_t<A>, B>; 
}
