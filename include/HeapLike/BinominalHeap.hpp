#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>

#include "HeapLike/HeapsErrors.hpp"
#include "HeapsConcepts.hpp"
#include "NodeLike/Node.hpp"

template <heaps_concepts::ComparableType ComparableVariable>
class binominal_tree {
	typedef uint64_t degree_t;

public:
	binominal_tree() = default;
	explicit binominal_tree(ComparableVariable&& __root_value);
	explicit binominal_tree(const ComparableVariable& __root_value);

	template <typename Container>
	requires heaps_concepts::ContainerOf<Container, ComparableVariable>
	explicit binominal_tree(Container&& __container);

	template <typename Container>
	requires heaps_concepts::ContainerOf<Container, ComparableVariable>
	explicit binominal_tree(const Container& __container);

	template <typename Container>
	requires heaps_concepts::ContainerOf<Container, ComparableVariable>
	auto push(Container&& __container) -> void {}

	template <typename Container>
	requires heaps_concepts::ContainerOf<Container, ComparableVariable>
	auto push(const Container& __container) -> void {}

	[[nodiscard]]auto degree() const noexcept -> degree_t {
		return m_degree;
	}
	[[nodiscard]]auto root_node() const noexcept -> nodes::related_node<ComparableVariable> {
		return m_root_node;
	}
	[[nodiscard]]auto keys() const noexcept -> std::vector<nodes::related_node<ComparableVariable>> {
		return m_keys;
	}

private:
	degree_t m_degree;
	nodes::related_node<ComparableVariable> m_root_node;
	std::vector<nodes::related_node<ComparableVariable>> m_keys;
};


template <heaps_concepts::ComparableType ComparableVariable>
class binominal_heap {
	typedef uint64_t heap_size_t;

public:
	binominal_heap() = default;
	explicit binominal_heap(ComparableVariable &&__first_value); 
	explicit binominal_heap(const ComparableVariable &__first_value);

	template <typename Container>
	explicit binominal_heap(Container&& __container);

	/**
	* @brief Inserts new node with provided value into heap
	* @param __value New value to be inserted 
	*/
	auto push(const ComparableVariable &&__value) -> void {

	}
	/**
	* @brief Inserts new node with provided value into heap
	* @param __value New value to be inserted 
	*/
	auto push(ComparableVariable &&__value) -> void {
		
	}

	/**
	* @brief Extracts minimal value node from your heap 
	*/
	auto extract_min() -> ComparableVariable {
		auto min_tree = search_min_tree();
		auto min_root_node = min_tree.root_node();
		
		// Removing binominal tree from binominal heap
		auto iterator = std::ranges::find_if(m_root_list, [&](const auto& tree) -> bool {
			tree.root_node() == min_root_node;
		});
		m_root_list.erase(iterator);	

		// Falling apart process
		std::ranges::for_each(min_root_node.children(), [&](const auto& root_child) -> void {
			//Creating new tree from extracted root`s children
			m_root_list.emplace_back(root_child);
		});

		this->consolidate();
		return min_root_node;
	}
	/** 
	* @brief Decrease value of provided key in your heap
	* @param __heap_key Key to be decreased
	* @param __new_key New value for decreased key
	*/
	auto decrease_key(ComparableVariable&& __heap_key, ComparableVariable&& __new_key) -> void {
		auto iterator = std::ranges::find(m_keys, __heap_key);
		if (iterator) {
			__heap_key = std::move(__new_key);
			bubble_up(__heap_key);
		}
		else {
			throw heaps_errors::InvalidHeapKeyError("Your key does not exist in thi heap!");
		}
	}
	/** 
	* @brief Decrease value of provided key in your heap
	* @param __heap_key Key to be decreased
	* @param __new_key New value for decreased key
	*/
	auto decrease_key(const ComparableVariable& __heap_key, const ComparableVariable& __new_key) -> void {
		auto iterator = std::ranges::find(m_keys, __heap_key);
		if (iterator) {
			__heap_key = __new_key;
			bubble_up(__heap_key);
		}
		else {
			throw heaps_errors::InvalidHeapKeyError("Your key does not exist in thi heap!");
		}
	}

	auto merge(binominal_heap&& __other) -> void {}
	auto merge(const binominal_heap& __other) -> void {}

	template <typename HeapCollection>
	requires heaps_concepts::ContainerOf<HeapCollection, binominal_heap<ComparableVariable>>
	auto merge(HeapCollection&& __collection) -> void {}

	template <typename HeapCollection>
	requires heaps_concepts::ContainerOf<HeapCollection, binominal_heap<ComparableVariable>>
	auto merge(const HeapCollection& __collection) -> void {}

private:
	auto search_min_tree() -> binominal_tree<ComparableVariable> {
		auto binominal_tree_root_comparison = [](const binominal_tree<ComparableVariable>& x, const binominal_tree<ComparableVariable>& y) {
			return x.root_node() < y.root_node();
		};
		auto iterator = std::ranges::min_element(m_root_list, binominal_tree_root_comparison);

		return m_root_list[iterator];
	}
	auto consolidate() -> void {}
	auto bubble_up(const ComparableVariable& __decreased_node) -> void {}

	heap_size_t m_heap_size;
	std::vector<ComparableVariable> m_keys;
	std::vector<binominal_tree<ComparableVariable>> m_root_list;
};
