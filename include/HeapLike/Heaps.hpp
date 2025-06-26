#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include "NodeLike/Node.hpp"
#include <type_traits>

namespace {
	template <typename Type>
	concept Numeric = std::is_arithmetic<Type>::value;

	class EmptyHeapError final : std::exception {
	public:
		EmptyHeapError(std::string&& error_text):
		text{std::move(error_text)}
		{}

		const char* what() const noexcept {
			return text.c_str();
		}

	private:
		std::string text;
	};
}

namespace {
	template <typename HeapKeyType, typename CompareType>
	class binary_heap {
	public:
		virtual ~binary_heap() = default;	
		
		auto push(HeapKeyType&& __val) -> void {
			__keys_bin.push_back(std::move(__val));
			heapify_up();
		}
		auto push(const HeapKeyType& __val) -> void {
			__keys_bin.push_back(__val);
			heapify_up();
		}
		[[nodiscard]]auto pop_root() -> HeapKeyType {
			if (empty()) {
				throw EmptyHeapError("Your heap is empty!");
			}

			auto previous_root = __keys_bin.front();
			auto last_element = __keys_bin.back();

			__keys_bin.at(0) = last_element;
			__keys_bin.pop_back();
			heapify_down();

			return previous_root;
		}
		auto pop_front() -> void {
			if (empty()) {
				throw EmptyHeapError("Your heap is empty!");
			}
			auto _ = pop_root();
		}
		auto pop_back() -> void {
			if (empty()) {
				throw EmptyHeapError("Your heap is empty!");
			}
			__keys_bin.pop_back();
		}
		[[nodiscard]]auto size() const noexcept -> size_t {
			return __keys_bin.size();
		}
		[[nodiscard]]auto empty() const noexcept -> bool {
			return __keys_bin.empty();
		}
		[[nodiscard]]auto root() const noexcept -> HeapKeyType {
			if (empty()) {
				throw EmptyHeapError("Your heap is empty!");
			}
			return __keys_bin.front();
		}
		[[nodiscard]]auto last() const noexcept -> HeapKeyType {
			return __keys_bin.back();
		}

		auto print_heap() -> void {
			for (const auto& key : __keys_bin) {
				std::cout << key << " ";
			}
			std::cout << std::endl;
		}

	protected:
		std::vector<HeapKeyType> __keys_bin;
		CompareType comparator;

	private:
		auto heapify_up() -> void {
			if (__keys_bin.size() == 1){
				return;
			}

			int pushed_idx = __keys_bin.size() - 1;
			int parent_idx = (pushed_idx - 1) / 2;

			while (true) {
				HeapKeyType pushed_val = __keys_bin.at(pushed_idx);
				HeapKeyType parent_val =  __keys_bin.at(parent_idx);
				if (comparator(pushed_val, parent_val)){
					std::swap(__keys_bin.at(pushed_idx), __keys_bin.at(parent_idx));

					pushed_idx = parent_idx;
					parent_idx = (pushed_idx - 1) / 2;
				}
				else {
					break;
				}
			}
		}
		auto heapify_down() -> void {
			if (__keys_bin.size() == 1) {
				return;
			}

			int new_root_idx = 0;
			int left_child_idx = 2 * new_root_idx + 1;
			int right_child_idx = left_child_idx + 1;
			
			HeapKeyType swap_child_val;
			int swap_child_idx;

			while (true) {
				if (left_child_idx + 1 <= static_cast<int>(__keys_bin.size())) {
					HeapKeyType left_child_val = __keys_bin.at(left_child_idx);
					swap_child_val = left_child_val;
					swap_child_idx = left_child_idx;
				}
				else {
					break;
				}
				if (right_child_idx + 1 <= static_cast<int>(__keys_bin.size())) {
					HeapKeyType right_child_val = __keys_bin.at(right_child_idx);
					if (comparator(right_child_val, swap_child_val)) {
						swap_child_val = right_child_val;
						swap_child_idx = right_child_idx;
					}

				}

				HeapKeyType new_root_val = __keys_bin.at(new_root_idx);
				if (comparator(swap_child_val, new_root_val)) {
					std::swap(__keys_bin.at(new_root_idx), __keys_bin.at(swap_child_idx));
					new_root_idx = swap_child_idx;

					left_child_idx = 2 * new_root_idx + 1;
					right_child_idx = left_child_idx + 1;
				}
				else {
					break;
				}
			}
		}
	};
}

namespace heaps {
#define HEAP_KEY Node

	namespace min_heaps {
		/** 
		* @brief Min-heap. Keeps smallest element in root.
		*/
		template <Numeric NumericVariable>
		class min_heap final : public binary_heap<NumericVariable, std::less<NumericVariable>> {
			using MIN_BIN_HEAP = binary_heap<NumericVariable, std::less<NumericVariable>>;

		public:
			explicit min_heap(NumericVariable &&__root = 0) {
				MIN_BIN_HEAP::__keys_bin.push_back(std::move(__root));
			}
			explicit min_heap(const NumericVariable &__root = 0) {
				MIN_BIN_HEAP::__keys_bin.push_back(__root);
			}

			~min_heap() {
				MIN_BIN_HEAP::__keys_bin.clear();
			}		
		}; 

		/**
		* @brief Min-heap. Keeps smallest of node objects in root. 
		*/
		template <Numeric NumericVariable, typename StoredData>
		class min_heap_ex : public binary_heap<HEAP_KEY<NumericVariable, StoredData>, std::less<HEAP_KEY<NumericVariable, StoredData>>> {
			using MIN_BIN_HEAP_EXTENDED = binary_heap<HEAP_KEY<NumericVariable, StoredData>, std::less<HEAP_KEY<NumericVariable, StoredData>>>;

		public:
			explicit min_heap_ex(HEAP_KEY<NumericVariable, StoredData>&& __root_node) {
				MIN_BIN_HEAP_EXTENDED::__keys_bin.push_back(std::move(__root_node));
			}
			explicit min_heap_ex(const HEAP_KEY<NumericVariable, StoredData>& __root_node) {
				MIN_BIN_HEAP_EXTENDED::__keys_bin.push_back(std::move(__root_node));
			}
			explicit min_heap_ex(NumericVariable&& __root_key, StoredData&& __root_data) {
				MIN_BIN_HEAP_EXTENDED::__keys_bin.emplace_back(std::move(__root_key), std::move(__root_data));
			}
			explicit min_heap_ex(NumericVariable&& __root_key, const StoredData& __root_data) {
				MIN_BIN_HEAP_EXTENDED::__keys_bin.emplace_back(std::move(__root_key), __root_data);
			}

			~min_heap_ex() {
				MIN_BIN_HEAP_EXTENDED::__keys_bin.clear();
			}

			auto push(NumericVariable&& __node_key, StoredData&& __node_data) -> void {
				MIN_BIN_HEAP_EXTENDED::__keys_bin.emplace_back(std::move(__node_key), std::move(__node_data));
				MIN_BIN_HEAP_EXTENDED::heapify_up();
			}
			auto push(NumericVariable&& __node_key, const StoredData& __node_data) -> void {
				MIN_BIN_HEAP_EXTENDED::__keys_bin.emplace_back(std::move(__node_key), __node_data);
				MIN_BIN_HEAP_EXTENDED::heapify_up();
			}

			[[nodiscard]]auto pop_root_data() -> StoredData {
				return MIN_BIN_HEAP_EXTENDED::pop_root().DATA();
			}
			[[nodiscard]]auto root_data() -> StoredData {
				return MIN_BIN_HEAP_EXTENDED::root().DATA();
			}
		};	
	}	

	namespace max_heaps {
		/** 
		* @brief Min-heap. Keeps largest element in root.
		*/
		template <Numeric NumericVariable>
		class max_heap final : public binary_heap<NumericVariable, std::greater<NumericVariable>> {
			using MAX_BIN_HEAP = binary_heap<NumericVariable, std::greater<NumericVariable>>;

		public:
			explicit max_heap(NumericVariable &&__root = 0) {
				MAX_BIN_HEAP::__keys_bin.push_back(std::move(__root));
			}
			explicit max_heap(const NumericVariable &__root = 0) {
				MAX_BIN_HEAP::__keys_bin.push_back(__root);
			}

			~max_heap() {
				MAX_BIN_HEAP::__keys_bin.clear();
			}		
		};

		/**
		* @brief Max-heap. Keeps largest of node objects in root. 
		*/
		template <Numeric NumericVariable, typename StoredData>
		class max_heap_ex : public binary_heap<HEAP_KEY<NumericVariable, StoredData>, std::greater<HEAP_KEY<NumericVariable, StoredData>>> {
			using MAX_BIN_HEAP_EXTENDED = binary_heap<HEAP_KEY<NumericVariable, StoredData>, std::greater<HEAP_KEY<NumericVariable, StoredData>>>;

		public:
			explicit max_heap_ex(HEAP_KEY<NumericVariable, StoredData>&& __root_node) {
				MAX_BIN_HEAP_EXTENDED::__keys_bin.push_back(std::move(__root_node));
			}
			explicit max_heap_ex(const HEAP_KEY<NumericVariable, StoredData>& __root_node) {
				MAX_BIN_HEAP_EXTENDED::__keys_bin.push_back(std::move(__root_node));
			}
			explicit max_heap_ex(NumericVariable&& __root_key, StoredData&& __root_data) {
				MAX_BIN_HEAP_EXTENDED::__keys_bin.emplace_back(std::move(__root_key), std::move(__root_data));
			}
			explicit max_heap_ex(NumericVariable&& __root_key, const StoredData& __root_data) {
				MAX_BIN_HEAP_EXTENDED::__keys_bin.emplace_back(std::move(__root_key), __root_data);
			}

			~max_heap_ex() {
				MAX_BIN_HEAP_EXTENDED::__keys_bin.clear();
			}

			auto push(NumericVariable&& __node_key, StoredData&& __node_data) -> void {
				MAX_BIN_HEAP_EXTENDED::__keys_bin.emplace_back(std::move(__node_key), std::move(__node_data));
				MAX_BIN_HEAP_EXTENDED::heapify_up();
			}
			auto push(NumericVariable&& __node_key, const StoredData& __node_data) -> void {
				MAX_BIN_HEAP_EXTENDED::__keys_bin.emplace_back(std::move(__node_key), __node_data);
				MAX_BIN_HEAP_EXTENDED::heapify_up();
			}

			auto pop_root_data() -> StoredData{
				return MAX_BIN_HEAP_EXTENDED::pop_root().DATA();
			}
		};
	}
}