/* WORK IN PROGRESS*/

#include "TreeConcepts.hpp"
namespace self_balancing_trees {
      
      template <tree_concepts::ComparableType ComparableVariable>
      class avl_tree {
      public:
            avl_tree() = default;
            explicit avl_tree(ComparableVariable&& __root_value);
            explicit avl_tree(const ComparableVariable& __root_value);

            template <typename Container>
            explicit avl_tree(Container&& __container);
            
            template <typename Container>
            explicit avl_tree(const Container& __container);

            auto insert(ComparableVariable&& __value) -> void;
            auto insert(const ComparableVariable& __value) -> void;

            auto extract_root() -> ComparableVariable;
      };

      template <tree_concepts::ComparableType ComparableVariable>
      class red_black_tree {
      public:
            red_black_tree() = default;
            explicit red_black_tree(ComparableVariable&& __root_value);
            explicit red_black_tree(const ComparableVariable& __root_value);
      
            template <typename Container>
            explicit red_black_tree(Container&& __container);

            template <typename Container>
            explicit red_black_tree(const Container& __container);

            auto insert(ComparableVariable&& __value) -> void;
            auto insert(const ComparableVariable& __value) -> void;

            auto extract_root() -> ComparableVariable;
      };
}