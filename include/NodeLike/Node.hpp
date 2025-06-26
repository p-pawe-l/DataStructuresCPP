#pragma once
#include <utility>

template <typename NumericVariable, typename StoredData>
class Node {
public:
	Node(NumericVariable&& __key, StoredData&& __data):
	m_numeric_key{std::move(__key)},
	m_data{std::move(__data)}
	{}
	Node(NumericVariable&& __key, const StoredData& __data):
	m_numeric_key{std::move(__key)},
	m_data{__data}
	{}
	
	auto KEY() const noexcept -> NumericVariable {
		return m_numeric_key;
	}
	auto DATA() const noexcept -> StoredData {
		return m_data;
	}
	auto DATA() noexcept -> StoredData& {
		return m_data;
	} 
	
	auto SET_KEY(NumericVariable&& __key) noexcept -> void {
		m_numeric_key = std::move(__key);
	}
	auto SET_DATA(StoredData&& __data) noexcept -> void {
		m_data = std::move(__data);
	}
	auto SET_DATA(const StoredData& __data) noexcept -> void {
		m_data = __data;
	}

private:
    	NumericVariable m_numeric_key;
    	StoredData m_data;
};