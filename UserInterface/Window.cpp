#include "Window.hpp"

#include <string>
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

namespace loser_ui{
	void Window::callbackClose(GLFWwindow* const window) noexcept{
		if(window != nullptr){
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		return;
	}

	void Window::callbackResize(GLFWwindow* const window, const int width, const int height) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}

		current_window->width_	= width;
		current_window->height_ = height;

		current_window->scene_->computeProjectionMatrix(width, height);

		return;
	}

	void Window::callbackFramebuffer(GLFWwindow* const window, const int width, const int height) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}

		current_window->renderer_->computeViewportMatrix(width, height);
		
		return;
	}

	void Window::callbackContentScale(GLFWwindow* const window, const float scale_x, const float scale_y) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		return;
	}

	void Window::callbackPosition(GLFWwindow* const window, const int pos_x, const int pos_y) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		return;
	}

	void Window::callbackIconfy(GLFWwindow* const window, const int iconfied) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		return;
	}

	void Window::callbackMaximize(GLFWwindow* const window, const int maximized) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		return;
	}

	void Window::callbackFocus(GLFWwindow* const window, const int focused) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		return;
	}

	void Window::callbackRefresh(GLFWwindow* const window) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}

		
		current_window->renderer_->clear();
		glfwSwapBuffers(window);

		return;
	}

	void Window::callbackKey(GLFWwindow* const window, const int key, const int scan_code, const int action, const int modifier) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		return;
	}

	void Window::callbackText(GLFWwindow* const window, const unsigned int code_point) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		return;
	}

	void Window::callbackCursorPosition(GLFWwindow* const window, const double pos_x, const double pos_y) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}

		const double diff_x = pos_x - current_window->cursor_pos_x_old_;
		const double diff_y = pos_y - current_window->cursor_pos_y_old_;

		current_window->cursor_pos_x_old_ = pos_x;
		current_window->cursor_pos_y_old_ = pos_y;

		if(current_window->clicked_left_){
			current_window->scene_->moveCamera(diff_x, diff_y);
		}
		if(current_window->clicked_right_){
			current_window->scene_->moveViewPointVertical(diff_y);
		}
		if(current_window->clicked_middle_){
			current_window->scene_->moveViewPointHorizontal(diff_x, diff_y);
		}

		return;
	}

	void Window::callbackCursorEnter(GLFWwindow* const window, const int enter) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		return;
	}

	void Window::callbackMouseButton(GLFWwindow* const window, const int button, const int action, const int modifier) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}

		if(button == GLFW_MOUSE_BUTTON_LEFT){
			if(action == GLFW_PRESS){
				current_window->clicked_left_ = true;
			}
			else if(action == GLFW_RELEASE){
				current_window->clicked_left_ = false;
			}
		}
		if(button == GLFW_MOUSE_BUTTON_RIGHT){
			if(action == GLFW_PRESS){
				current_window->clicked_right_ = true;
			}
			else if(action == GLFW_RELEASE){
				current_window->clicked_right_ = false;
			}
		}
		if(button == GLFW_MOUSE_BUTTON_MIDDLE){
			if(action == GLFW_PRESS){
				current_window->clicked_middle_ = true;
			}
			else if(action == GLFW_RELEASE){
				current_window->clicked_middle_ = false;
			}
		}
		return;
	}

	void Window::callbackScroll(GLFWwindow* const window, const double offset_x, const double offset_y) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}
		
		current_window->scene_->zoomCamera(-offset_y);

		return;
	}

	void Window::callbackJoystick(const int id, const int is_connected) noexcept{
#ifdef _DEBUG
		if(is_connected == GLFW_TRUE){
			std::clog << "Joystick" << id << std::endl;
		}
#endif
		return;
	}

	void Window::callbackDrop(GLFWwindow* const window, const int cnt, const char** const paths) noexcept{
		if(window == nullptr){
			return;
		}
		Window* const current_window = static_cast<Window* const>(glfwGetWindowUserPointer(window));
		if(current_window == nullptr){
			return;
		}

		for(int i = 0; i < cnt; ++i){
			//Read Te4
		}
		return;
	}







	Window::Window(const int w, const int h, const int r, const int g, const int b, const int fps, GLFWcursor* const cursor, loser_scene::Scene* const scene_ref, const bool vulkan_support) noexcept(false): cursor_(cursor), scene_(scene_ref){
		setupWindowHint(r, g, b, fps, vulkan_support);

		width_ = w;
		height_ = h;

		GLFWwindow* window = glfwCreateWindow(w * 3 / 4, h * 3 / 4, Window::TITLE_NAME_, nullptr, nullptr);
		if(window == nullptr){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Create GLFW Window."));
		}

		//No Icon Image
		glfwSetWindowIcon(window, 0, nullptr);

		glfwSetWindowSizeLimits(window, w / 2, h / 2, w, h);
		glfwSetWindowAspectRatio(window, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowOpacity(window, Window::OPACITY_);

		if(!setupWindowCallback(window)){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Set up Window Callback Functions."));
		}

		if(!setupInputMode(window)){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Set up Input Mode."));
		}
		if(!setupInputCallback(window)){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Set up Input Callback Functions."));
		}

		glfwSetCursor(window, cursor);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(Window::SWAP_INTERVAL_);

		fw_ptr_.reset(window);
		glfwSetWindowUserPointer(fw_ptr_.get(), this);
	}

	void Window::setupWindowHint(const int red, const int green, const int blue, const int fps, const bool vulkan_support) noexcept{
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
		glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

		constexpr const int ACCUM_BIT_DEPTH = 0;
		constexpr const int AUX_BIT_DEPTH = 0;

		glfwWindowHint(GLFW_RED_BITS, red);
		glfwWindowHint(GLFW_GREEN_BITS, green);
		glfwWindowHint(GLFW_BLUE_BITS, blue);
		glfwWindowHint(GLFW_ALPHA_BITS, GLFW_DONT_CARE);
		glfwWindowHint(GLFW_DEPTH_BITS, GLFW_DONT_CARE);
		glfwWindowHint(GLFW_STENCIL_BITS, GLFW_DONT_CARE);
		glfwWindowHint(GLFW_ACCUM_RED_BITS, ACCUM_BIT_DEPTH);
		glfwWindowHint(GLFW_ACCUM_GREEN_BITS, ACCUM_BIT_DEPTH);
		glfwWindowHint(GLFW_ACCUM_BLUE_BITS, ACCUM_BIT_DEPTH);
		glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, ACCUM_BIT_DEPTH);
		glfwWindowHint(GLFW_AUX_BUFFERS, AUX_BIT_DEPTH);

		//Hard Condition
		glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
		glfwWindowHint(GLFW_SAMPLES, GLFW_DONT_CARE);
		glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

		glfwWindowHint(GLFW_REFRESH_RATE, fps);

		if(vulkan_support){
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}
		else{
			constexpr const int GL_VERSION_MAJOR = 4;
			constexpr const int GL_VERSION_MINOR = 6;

			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#ifdef _DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#else
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
#endif
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
			glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);
			glfwWindowHint(GLFW_CONTEXT_NO_ERROR, GLFW_TRUE);
		}
#ifdef __APPLE__
		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_TRUE);
#endif
		return;
	}

	bool Window::setupWindowCallback(GLFWwindow* const window) noexcept{
		if(window == nullptr){
			return false;
		}
		glfwSetWindowCloseCallback(window, Window::callbackClose);
		glfwSetWindowSizeCallback(window, Window::callbackResize);
		glfwSetFramebufferSizeCallback(window, Window::callbackFramebuffer);
		glfwSetWindowPosCallback(window, Window::callbackPosition);
		glfwSetWindowIconifyCallback(window, Window::callbackIconfy);
		glfwSetWindowRefreshCallback(window, Window::callbackRefresh);
#ifdef _DEBUG
		
		glfwSetWindowContentScaleCallback(window, Window::callbackContentScale);
		glfwSetWindowMaximizeCallback(window, Window::callbackMaximize);
		glfwSetWindowFocusCallback(window, Window::callbackFocus);
#endif
		return true;
	}

	bool Window::setupInputCallback(GLFWwindow* const window) noexcept{
		if(window == nullptr){
			return false;
		}
		glfwSetKeyCallback(window, Window::callbackKey);
		glfwSetCursorPosCallback(window, Window::callbackCursorPosition);
		glfwSetMouseButtonCallback(window, Window::callbackMouseButton);
		glfwSetScrollCallback(window, Window::callbackScroll);
		glfwSetDropCallback(window, Window::callbackDrop);
#ifdef _DEBUG
		glfwSetCharCallback(window, Window::callbackText);
		glfwSetCursorEnterCallback(window, Window::callbackCursorEnter);
		glfwSetJoystickCallback(Window::callbackJoystick);
#endif
		return true;
	}

	bool Window::setupInputMode(GLFWwindow* const window) noexcept{
		if(window == nullptr){
			return false;
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
		glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
		glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, glfwRawMouseMotionSupported());
		return true;
	}

	bool Window::isEnable() const noexcept{
		if(fw_ptr_ != nullptr){
			return glfwWindowShouldClose(fw_ptr_.get()) != GLFW_TRUE;
		}
		return false;
	}

	void Window::update() const noexcept{
		if(widgets_ != nullptr){
			widgets_->display();
		}

		if(fw_ptr_ != nullptr){
			glfwSwapBuffers(fw_ptr_.get());
		}

		glfwPollEvents();

		return;
	}

	void Window::createWidget() noexcept{
		if(widgets_ != nullptr){
			widgets_->createParts(width_, height_);
		}
		return;
	}

	void Window::addRendererReference(loser_renderer::GLRenderer* const renderer_ref) noexcept{
		renderer_.reset(renderer_ref);
		return;
	}

	void Window::addWidget() noexcept{
		widgets_ = std::make_unique<Widget>(fw_ptr_.get(), scene_, renderer_);
		return;
	}
}