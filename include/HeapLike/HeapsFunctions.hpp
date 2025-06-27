#pragma once

#include <cstdint>
#include <algorithm>
#include <variant>

#include "Heaps.hpp"

enum class heap_type: uint8_t {
	min_heap = 1,
	max_heap = 2
};

namespace heaps_functions {
	
	template <heaps_concepts::ComparableType ComparableVariable>
	using HeapVariant = 
	std::variant<
		heaps::min_heaps::min_heap<ComparableVariable>,
		heaps::max_heaps::max_heap<ComparableVariable>
	>; 

	/** 
	* @brief Transforms container into provided type of heap
	* @param __begin Begin of container iterator
	* @param __end End of container iterator
	* @param __type Provided type of heap
	*/
	template <typename ContainerItterator>
	auto transform_to_heap(ContainerItterator&& __begin, ContainerItterator&& __end, heap_type&& __type = heap_type::min_heap) -> void {
		switch (__type) {
			case (heap_type::min_heap): {
				
				break;
			}
			case (heap_type::max_heap): {

				break;
			}
		}
	}
	/** 
	* @brief Transforms container into provided type of heap
	* @param __container Provided container 
	* @param __type Provided type of heap
	*/
	template <typename Container>
	auto transform_to_heap(Container&& __container, heap_type&& __type = heap_type::min_heap) -> void {
		switch (__type) {
			case (heap_type::min_heap): {
				
				break;
			}
			case (heap_type::max_heap): {

				break;
			}
		}
	}

	/** 
	* @brief Produce heap based of provided container and provided heap type
	* @param __begin Begin of container iterator
	* @param __end End of container iterator
	* @param __type Provided type of heap
	*/
	template <typename ContainerItterator, typename ContainerInnerType>
	auto make_heap_from(ContainerItterator&& __begin, ContainerItterator&& __end, heap_type&& __type = heap_type::min_heap) {
		switch (__type) {
			case (heap_type::min_heap): {
				heaps::min_heaps::min_heap<ContainerInnerType> new_min_heap;

				std::for_each(__begin, __end, [&](const auto& key) -> void {
					new_min_heap.push(key);
				});

				return new_min_heap;

			}
			case (heap_type::max_heap): {
				heaps::max_heaps::max_heap<ContainerInnerType> new_max_heap;

				std::for_each(__begin, __end, [&](const auto& key) -> void {
					new_max_heap.push(key);
				});
				
				return new_max_heap;
			}
		}
	}
	/** 
	* @brief Produce heap based of provided container and provided heap type
	* @param __container Provided container
	* @param __type Provided type of heap
	*/
	template <typename Container, typename ContainerInnerType>
	auto make_heap_from(Container&& __container, heap_type&& __type = heap_type::min_heap) -> HeapVariant<ContainerInnerType> {
		HeapVariant<ContainerInnerType> new_heap;

		switch (__type) {
			case (heap_type::min_heap): {
				auto _h = std::get<heaps::min_heaps::min_heap<ContainerInnerType>>(new_heap);
				std::ranges::for_each(__container, [&](const auto& key) -> void {
					_h.push(key);
				});

				return _h;
				// return static_cast<HeapVariant<ContainerInnerType>>(_h);

			}
			case (heap_type::max_heap): {
				auto _h = std::get<heaps::max_heaps::max_heap<ContainerInnerType>>(new_heap);
				std::ranges::for_each(__container, [&](const auto& key) -> void {
					_h.push(key);
				});

				return _h;
				//return static_cast<HeapVariant<ContainerInnerType>>(_h);
			}
		}
	}

	/** 
	* @brief Merge two heaps into one
	* @param __lhs First heap to be merged
	* @param __rhs Second heap to be merged
	*/
	template <typename HeapVariable>
	auto heaps_union(const HeapVariable& __lhs, const HeapVariable& __rhs) -> HeapVariable {
		HeapVariable merged_heap;

		std::ranges::for_each(__lhs.keys_list(), [&](const auto& heap_key) -> void {
			merged_heap.push(heap_key);
		});
		std::ranges::for_each(__rhs.keys_list(), [&](const auto& heap_key) -> void {
			merged_heap.push(heap_key);
		});

		return merged_heap;
	}


}