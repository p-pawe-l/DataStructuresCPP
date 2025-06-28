#pragma once

template <typename Type>
class stack {
public:
      stack() = default;
      explicit stack(Type&& __first);
      explicit stack(const Type& __first);

      auto push(Type&& __value) -> void;
      auto push(const Type&& __value) -> void;

      [[nodiscard]]auto pop() -> Type;

private:
      
};