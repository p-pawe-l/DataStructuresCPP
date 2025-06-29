#pragma once 


#include "NodeLike/Node.hpp"
#include "ListConcepts.hpp"
#include <memory>
#include <utility>

/**
* @brief Standard version of linked list
*/
template <typename Type>
class linked_list {
public:
	linked_list() = default;
	explicit linked_list(Type&& __first_value);
	explicit linked_list(const Type& __first_value);
	
	template <typename Container>
	requires list_concepts::ContainerOf<Container, Type>
	explicit linked_list(Container&& __container);
	
	template <typename Container>
	requires list_concepts::ContainerOf<Container, Type>
	explicit linked_list(const Container&& __container);


private:
	template <typename Container>
	requires list_concepts::ContainerOf<Container, Type>
	auto create_linked_list(Container&& __container) -> void {
		std::unique_ptr<std::vector<linked_list_nodes::forward_node<Type>>> __temp;
		// 1 step:
		// Creating nodes
		this->m_start_node = linked_list_nodes::forward_node<Type>(std::move(__container.at(0)));
		std::ranges::for_each(__container.begin() + 1, __container.end(), [&](const auto& __val) -> void {
			auto __node = std::make_unique(__val);
		});
	}


	linked_list_nodes::forward_node<Type> m_start_node;	
};

/**
* @brief Reversed version of standard linked list
*/
template <typename Type>
class reversed_linked_list {
public:
	reversed_linked_list() = default;
	explicit reversed_linked_list(Type&& __first_value);
	explicit reversed_linked_list(const Type& __first_value);
	
	
private:
	linked_list_nodes::backward_node<Type> m_end_node;
};
