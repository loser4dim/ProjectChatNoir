#include "Cursor.hpp"

#include <string>
#include <stdexcept>

namespace loser_ui{
	Cursor::Cursor(GLFWcursor* const new_cursor) noexcept(false){
		if(new_cursor == nullptr){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Create GLFW Cursor Instance."));
		}
		fw_ptr_.reset(new_cursor);
	}

	Cursor::~Cursor() noexcept{
		fw_ptr_.release();
	}
}