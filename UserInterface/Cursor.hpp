#pragma once

#ifndef _DLL
#define GLEW_STATIC
#endif
#include <GL/glew.h>
//#define GLFW_INCLUDE_NONE
//#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#pragma comment(lib, "glfw3")

#include <memory>

namespace loser_ui{
	//Functor for std::unique_ptr<GLFWcursor>
	struct CursorDestroyer final{
	public:
		inline constexpr void operator()(GLFWcursor* const cursor) const noexcept{
			if(cursor != nullptr){
				glfwDestroyCursor(cursor);
			}
			return;
		}
	};
	
	class Cursor final{
	private:
		std::unique_ptr<GLFWcursor, const CursorDestroyer> fw_ptr_ = nullptr;

	public:
		Cursor() = delete;
		explicit Cursor(GLFWcursor* const new_cursor) noexcept(false);

		Cursor(const Cursor&)	= delete;
		Cursor(Cursor&&)		= delete;

		Cursor& operator=(const Cursor&)	= delete;
		Cursor& operator=(Cursor&&)			= delete;

		~Cursor() noexcept;
	};
};
