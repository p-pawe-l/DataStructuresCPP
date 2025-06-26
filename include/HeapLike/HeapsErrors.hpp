#pragma once 

#include <exception>
#include <string>
#include <utility>

namespace heaps_errors {
      class EmptyHeapError final : std::exception {
	public:
		EmptyHeapError(std::string&& error_text):
		text{std::move(error_text)}
		{}

		const char* what() const noexcept {
			return text.c_str();
		}

	private:
		std::string text;
	};
}