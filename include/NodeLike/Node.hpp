#pragma once

#include <utility>
#include "NodeConcepts.hpp"
#include <vector>
#include <optional>

namespace nodes {
	
	/**
	* @brief Basic node build for storing numeric key and provided data to store
	*/
	template <typename NumericVariable, typename StoredData>
	class basic_node {
	public:
		basic_node(NumericVariable&& __key, StoredData&& __data):
		m_numeric_key{std::move(__key)},
		m_data{std::move(__data)}
		{}
		basic_node(NumericVariable&& __key, const StoredData& __data):
		m_numeric_key{std::move(__key)},
		m_data{__data}
		{}

		auto key() const noexcept -> NumericVariable {
			return m_numeric_key;
		}
		auto data() const noexcept -> StoredData {
			return m_data;
		}
		auto change_key(NumericVariable&& new_key) -> void {
			m_numeric_key = std::move(new_key);
		}
		auto change_data(StoredData&& new_data) -> void {
			m_data = std::move(new_data);
		}
		auto change_data(const StoredData& new_data) -> void {
			m_data = new_data;
		}


	protected:
		NumericVariable m_numeric_key;
		StoredData m_data;
	};

	/**
	* @brief Specialized node for applying relations beetwen nodes
	*/

	template <typename NumericVariable, typename StoredData>
	class edge_node final : public basic_node<NumericVariable, StoredData> {
	public:
		edge_node(NumericVariable&& __key, StoredData&& __data):
		basic_node<NumericVariable, StoredData>(std::move(__key), std::move(__data))
		{}
		edge_node(NumericVariable&& __key, const StoredData& __data):
		basic_node<NumericVariable, StoredData>(std::move(__key), __data)
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
		requires node_concepts::EdgeNodeContainer<Container, edge_node<NumericVariable, StoredData>>
		auto mulit_connect(Container&& __container) -> void {

		}
		/**
		* @brief Connects collection of edge_nodes to yours
		* @tparam Container Collection of edge_nodes
		* @param __container Collection of node to be connected
		*/
		template <typename Container>
		requires node_concepts::EdgeNodeContainer<Container, edge_node<NumericVariable, StoredData>>
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

	template <typename NumericVariable, typename StoredData>
	class related_node final : public basic_node<NumericVariable, StoredData> {
	public:
		related_node(NumericVariable&& __key, StoredData&& __data):
		basic_node<NumericVariable, StoredData>(std::move(__key), std::move(__data)),
		m_parent{std::nullopt},
		m_children{}
		{}
		related_node(NumericVariable&& __key, const StoredData& __data):
		basic_node<NumericVariable, StoredData>(std::move(__key), __data),
		m_parent{std::nullopt},
		m_children{}
		{}

		auto add_child(related_node&& __other) -> void {

		}
		auto add_child(const related_node& __other) -> void {
			
		}

		template <typename Container>
		requires node_concepts::RelatedNodeContainer<Container, related_node<NumericVariable, StoredData>>
		auto add_children(Container&& __container) -> void {

		}
		template <typename Container>
		requires node_concepts::RelatedNodeContainer<Container, related_node<NumericVariable, StoredData>>
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