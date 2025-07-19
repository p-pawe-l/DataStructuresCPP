#include "TreeConcepts.hpp"
#include "../NodeLike/Node.hpp"

template <tree_concepts::ComparableType ComparableVariable>
class binary_tree {
public:
        binary_tree() = default;
        explicit binary_tree(ComparableVariable&& __root_value);
        explicit binary_tree(const ComparableVariable& __root_value);

        void insert(ComparableVariable&& __value);
        void insert(const ComparableVariable& __value);

        ComparableVariable pop_root();
        
        void delete_key(ComparableVariable&& __key);
        void delete_key(const ComparableVariable&& __key);
        
        ComparableVariable max() const noexcept;
        ComparableVariable min() const noexcept;
        ComparableVariable root() const noexcept;

        size_t height() const noexcept;

private:
        nodes::related_node<ComparableVariable> m_root_node;
};