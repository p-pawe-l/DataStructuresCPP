#pragma once

#include <utility>
#include "NodeConcepts.hpp"
#include <vector>
#include <optional>

namespace nodes {
	
	/**
	* @brief Basic node build for storing comparable type of data
	*/
	template <node_concepts::ComparableType ComparableVariable>
	class basic_node {
	public:
		explicit basic_node(ComparableVariable&& __data):
		m_data{std::move(__data)}
		{}
		explicit basic_node(const ComparableVariable&& __data):
		m_data{__data}
		{}

		auto data() const noexcept -> ComparableVariable {
			return m_data;
		}
		auto change_data(ComparableVariable&& new_data) -> void {
			m_data = std::move(new_data);
		}
		auto change_data(const ComparableVariable& new_data) -> void {
			m_data = new_data;
		}

		auto operator==(basic_node<ComparableVariable>&& __other) -> bool {
			return (this->m_data == std::move(__other).m_data);
		}
		auto operator==(const basic_node<ComparableVariable>& __other) -> bool {
			return (this->m_data == __other.m_data);
		}

		auto operator!=(basic_node<ComparableVariable>&& __other) -> bool {
			return !(*this == std::move(__other));
		}
		auto operator!=(const basic_node<ComparableVariable>& __other) -> bool {
			return !(*this == __other);
		}

		auto operator<(basic_node<ComparableVariable>&& __other) -> bool {
			return (this->m_data < std::move(__other).m_data);
		}
		auto operator<(const basic_node<ComparableVariable>& __other) -> bool {
			return (this->m_data < __other.m_data);
		}

		auto operator<=(basic_node<ComparableVariable>&& __other) -> bool {
			return *this < std::move(__other) || *this == std::move(__other);
		}
		auto operator<=(const basic_node<ComparableVariable>& __other) -> bool {
			return *this < __other || *this == __other;
		}

		auto operator>(basic_node<ComparableVariable>&& __other) -> bool {
			return !(*this <= std::move(__other));
		}
		auto operator>(const basic_node<ComparableVariable>& __other) -> bool {
			return !(*this <= __other);
		}

		auto operator>=(basic_node<ComparableVariable>&& __other) -> bool {
			return !(*this < std::move(__other));
		}
		auto operator>=(const basic_node<ComparableVariable>& __other) -> bool {
			return !(*this < __other);
		}

	protected:
		ComparableVariable m_data;
	};

	/**
	* @brief Specialized node for applying relations beetwen nodes
	*/
	template <node_concepts::ComparableType ComparableVariable>
	class edge_node final : public basic_node<ComparableVariable> {
	public:
		explicit edge_node(ComparableVariable&& __data):
		basic_node<ComparableVariable>(std::move(__data))
		{}
		explicit edge_node(const ComparableVariable& __data):
		basic_node<ComparableVariable>(std::move(__data), __data)
		{}

		/**
		* @brief Connects other edge_node object to yours
		* @param __other Node to be connected
		*/
		auto connect(edge_node&& __other) -> void {
		
		}
		/**
		* @brief Connects other edge_node object to yours
		* @param __other Node to be connected
		*/
		auto connect(const edge_node& __other) -> void {

		}
		/**
		* @brief Connects collection of edge_nodes to yours
		* @tparam Container Collection of edge_nodes
		* @param __container Collection of node to be connected
		*/
		template <typename Container>
		requires node_concepts::EdgeNodeContainer<Container, edge_node<ComparableVariable>>
		auto mulit_connect(Container&& __container) -> void {

		}
		/**
		* @brief Connects collection of edge_nodes to yours
		* @tparam Container Collection of edge_nodes
		* @param __container Collection of node to be connected
		*/
		template <typename Container>
		requires node_concepts::EdgeNodeContainer<Container, edge_node<ComparableVariable>>
		auto mulit_connect(const Container& __container) -> void {

		}

		[[nodiscard]]auto connections() const noexcept -> std::vector<edge_node> {
			return m_connected_nodes;
		}
		[[nodiscard]]auto degree() const noexcept -> size_t {
			return m_connected_nodes.size();
		}
		[[nodiscard]]auto is_leaf() -> bool {
			return (m_connected_nodes.size() == 1);
		}
	private:
		std::vector<edge_node> m_connected_nodes;
	};

	template <node_concepts::ComparableType ComparableVariable>
	class related_node final : public basic_node<ComparableVariable> {
	public:
		related_node(ComparableVariable&& __data):
		basic_node<ComparableVariable>(std::move(__data)),
		m_parent{std::nullopt},
		m_children{}
		{}
		related_node(const ComparableVariable& __data):
		basic_node<ComparableVariable>(__data),
		m_parent{std::nullopt},
		m_children{}
		{}

		auto add_child(related_node&& __other) -> void {

		}
		auto add_child(const related_node& __other) -> void {
			
		}

		template <typename Container>
		requires node_concepts::RelatedNodeContainer<Container, related_node<ComparableVariable>>
		auto add_children(Container&& __container) -> void {

		}
		template <typename Container>
		requires node_concepts::RelatedNodeContainer<Container, related_node<ComparableVariable>>
		auto add_children(const Container& __container) -> void {
			
		}

		auto set_parent(related_node&& __parent) -> void {

		}
		auto set_parent(const related_node& __parent) -> void {

		}
		
		[[nodiscard]]auto parent() const noexcept -> std::optional<related_node> {
			return m_parent;
		}
		[[nodiscard]]auto children() const noexcept -> std::vector<related_node> {
			return m_children;
		}
		[[nodiscard]]auto degree() const noexcept -> size_t {
			return m_children.size(); 	
		}
		[[nodiscard]]auto is_leaf() const noexcept -> bool {
			return (m_children.size() == 1);
		}
	
	private:
		std::optional<related_node> m_parent;
		std::vector<related_node> m_children;
	};
}

namespace linked_list_nodes {

	/**
	* @brief Basic build for node with special purpose for implementing linked/double linked lists 
	*/
	template <typename Type>
	class basic_node {
	public:
		explicit basic_node(Type&& __data);
		explicit basic_node(const Type&& __data);

		/**
		* @brief Access stored data in node 
		*/
		auto data() const noexcept -> Type {
			return m_stored_data;
		}

 	protected:
		Type m_stored_data;
	};

	/**
	* @brief Special purpose node for implementing linked_list 
	*/
	template <typename Type>
	class forward_node final : public basic_node<Type> {
	public:
		explicit forward_node(Type&& __data):
		basic_node<Type>{std::move(__data)}
		{}
		explicit forward_node(const Type& __data):
		basic_node<Type>{__data}
		{}
		forward_node(Type&& __data, forward_node<Type> __next):
		basic_node<Type>{std::move(__data)},
		m_next{&std::move(__next)}
		{}
		forward_node(const Type& __data, const forward_node<Type> __next):
		basic_node<Type>{std::move(__data)},
		m_next{&__next}
		{}
		
		/**
		* @brief Accessing next related node
		*/
		auto next() const noexcept-> forward_node<Type>* {
			return m_next;
		}
		/**
		* @brief Setting next related node 
		*/
		auto set_next(forward_node<Type>&& __next) -> void {
			m_next = &std::move(__next);
		}
		/**
		* @brief Setting next related node 
		*/
		auto set_next(const forward_node<Type>& __next) -> void {
			m_next = &__next;
		}
		

	private:
		forward_node<Type>* m_next;
	};
	
	/**
	* @brief Special purpose node for implementing reversed_linked_list 
	*/
	template <typename Type>
	class backward_node final : public basic_node<Type> {};

	/**
	* @brief Special purpose node for implementing double_linked_list 
	*/
	template <typename Type>
	class bidirectional_node final : public basic_node<Type> {};


}