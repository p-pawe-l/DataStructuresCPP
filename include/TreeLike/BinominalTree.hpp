#pragma once

#include <vector>
#include "TreeConcepts.hpp"
#include <cmath>
#include "NodeLike/Node.hpp"

template <tree_concepts::ComparableType ComparableVariable>
class binominal_tree {
public:
      binominal_tree() = default;
      explicit binominal_tree(ComparableVariable&& __root):
      m_root{std::move(__root)},
      m_keys{std::move(__root)}
      {}
      explicit binominal_tree(const ComparableVariable&& __root):
      m_root{__root},
      m_keys{__root}
      {}

      auto push(ComparableVariable&& __value) -> void {
            m_keys.push_back(std::move(__value));
      }
      auto push(const ComparableVariable& __value) -> void {
            m_keys.push_back(__value);
      }
      [[nodiscard]]auto root() const noexcept -> ComparableVariable {
            return m_root;
      }
      [[nodiscard]]auto keys() const noexcept -> std::vector<ComparableVariable> {
            return m_keys;
      }
      [[nodiscard]]auto degree() const noexcept {
            return std::floor(std::log(m_keys.size()));
      }

private:
      ComparableVariable m_root;
      std::vector<ComparableVariable> m_keys;
};