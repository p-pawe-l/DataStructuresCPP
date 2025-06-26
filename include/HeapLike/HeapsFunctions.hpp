#pragma once

#include <cstdint>
#include <algorithm>
#include "Heaps.hpp"

enum class heap_type: uint8_t {
	min_heap = 1,
	max_heap = 2
};

namespace heaps_functions {
	
	template <typename ContainerItterator>
	auto transform_to_heap(ContainerItterator&& __begin, ContainerItterator&& __end, heap_type&& __type = heap_type::min_heap) -> void {
		switch (__type) {
			case (heap_type::min_heap): {
				
			}
			case (heap_type::max_heap): {

			}
		}
	}

	template <typename ContainerItterator>
	auto make_heap_from(ContainerItterator&& __begin, ContainerItterator&& __end, heap_type&& __type = heap_type::min_heap) {
		switch (__type) {
			case (heap_type::min_heap): {

			}
			case (heap_type::max_heap): {
			}
		}
	}

	template <typename HeapVariable>
	auto heaps_union(const HeapVariable& lhs, const HeapVariable& rhs) -> HeapVariable {
		HeapVariable merged_heap{};

		std::ranges::for_each(lhs.keys_list(), [&](const auto& heap_key) -> void {
			merged_heap.push(heap_key);
		});
		std::ranges::for_each(rhs.keys_list(), [&](const auto& heap_key) -> void {
			merged_heap.push(heap_key);
		});

		return merged_heap;
	}


}