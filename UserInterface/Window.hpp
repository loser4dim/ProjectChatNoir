#pragma once

#include "Cursor.hpp"
#include "Widget.hpp"

namespace loser_ui{
	//Functor for std::unique_ptr<GLFWwindow>
	struct WindowDestroyer final{
	public:
		inline constexpr void operator()(GLFWwindow* const window) const noexcept{
			if(window != nullptr){
				glfwDestroyWindow(window);
			}
			return;
		}
	};

	class Window final{
	private:
		static constexpr const char* const	TITLE_NAME_			= "Mesh Model Viewer | Copyright: loser4dim, 2021";
		static constexpr const char* const	ICON_IMAGE_PATH_	= "./Icon/AppIcon.bin";
		static constexpr const float		OPACITY_			= 1.0f;
		static constexpr const int			SWAP_INTERVAL_		= 1;

		const Cursor cursor_;
		std::unique_ptr<GLFWwindow, WindowDestroyer> fw_ptr_ = nullptr;


		std::shared_ptr<loser_scene::Scene> scene_ = nullptr;
		std::shared_ptr<loser_renderer::GLRenderer> renderer_ = nullptr;




		std::unique_ptr<Widget> widgets_ = nullptr;


		int width_ = 0;
		int height_ = 0;

		double cursor_pos_x_old_ = 0.0;
		double cursor_pos_y_old_ = 0.0;

		bool clicked_left_ = false;
		bool clicked_right_ = false;
		bool clicked_middle_ = false;

	private:
		static void callbackClose(GLFWwindow* const window) noexcept;
		static void callbackResize(GLFWwindow* const window, const int width, const int height) noexcept;
		static void callbackFramebuffer(GLFWwindow* const window, const int width, const int height) noexcept;
		static void callbackContentScale(GLFWwindow* const window, const float scale_x, const float scale_y) noexcept;
		static void callbackPosition(GLFWwindow* const window, const int pos_x, const int pos_y) noexcept;
		static void callbackIconfy(GLFWwindow* const window, const int iconfied_status) noexcept;
		static void callbackMaximize(GLFWwindow* const window, const int maximized_status) noexcept;
		static void callbackFocus(GLFWwindow* const window, const int focused_status) noexcept;
		static void callbackRefresh(GLFWwindow* const window) noexcept;

		static void callbackKey(GLFWwindow* const window, const int key, const int scan_code, const int action, const int modifier) noexcept;
		static void callbackText(GLFWwindow* const window, const unsigned int code_point) noexcept;
		static void callbackCursorPosition(GLFWwindow* const window, const double pos_x, const double pos_y) noexcept;
		static void callbackCursorEnter(GLFWwindow* const window, const int enter) noexcept;
		static void callbackMouseButton(GLFWwindow* const window, const int button, const int action, const int modifier) noexcept;
		static void callbackScroll(GLFWwindow* const window, const double offset_x, const double offset_y) noexcept;
		static void callbackJoystick(const int id, const int is_connected) noexcept;
		static void callbackDrop(GLFWwindow* const window, const int cnt, const char** const paths) noexcept;

	public:
		Window() = delete;
		Window(const int w, const int h, const int r, const int g, const int b, const int fps, GLFWcursor* const cursor, loser_scene::Scene* const scene_ref, const bool vulkan_support = false) noexcept(false);


		/*Window(GLFWwindow* new_window, GLFWcursor* const new_cursor, quartet_scene::Scene* const scene_ref) noexcept: cursor_(new_cursor), fw_ptr_(new_window), scene_(scene_ref){
			glfwSetWindowUserPointer(fw_ptr_.get(), static_cast<void* const>(this));
		}*/

		Window(const Window&) = delete;
		Window(Window&&) = delete;

		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
	public:
		~Window() noexcept{

			renderer_.reset();
			scene_.reset();

			fw_ptr_.release();
		}

	public:
		//static Window createInstance(const Monitor& monitor, GLFWcursor* const cursor, quartet_scene::Scene& scene, const bool vulkan_support = false) noexcept(false);
	private:
		static void setupWindowHint(const int red, const int green, const int blue, const int fps, const bool vulkan_support) noexcept;
		static bool setupWindowCallback(GLFWwindow* const window) noexcept;
		static bool setupInputCallback(GLFWwindow* const window) noexcept;
		static bool setupInputMode(GLFWwindow* const window) noexcept;

	public:
		bool isEnable() const noexcept;
		void update() const noexcept;

		void createWidget() noexcept;

		void addWidget(loser_renderer::GLRenderer* const renderer_ref);
	};





}
