#pragma once

#include <algorithm>
#include <vector>
#include <cstdint>

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

	auto push(const ComparableVariable &&__value) -> void {}
	auto push(ComparableVariable &&__value) -> void {}

	auto extract_min() -> ComparableVariable {}
	
	auto merge(binominal_heap&& __other) -> void {}
	auto merge(const binominal_heap& __other) -> void {}

	template <typename HeapCollection>
	requires heaps_concepts::ContainerOf<HeapCollection, binominal_heap<ComparableVariable>>
	auto merge(HeapCollection&& __collection) -> void {}

	template <typename HeapCollection>
	requires heaps_concepts::ContainerOf<HeapCollection, binominal_heap<ComparableVariable>>
	auto merge(const HeapCollection& __collection) -> void {}

private:
	auto consolidate() -> void {}

	heap_size_t m_heap_size;
	std::vector<binominal_tree<ComparableVariable>> m_root_list;
};
