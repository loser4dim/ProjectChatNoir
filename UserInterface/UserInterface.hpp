#pragma once

#include "Monitor.hpp"
#include "Window.hpp"
#include <vector>

namespace loser_ui{
	class UserInterface final{
	private:
		std::vector<Monitor> monitors_;
		std::unique_ptr<Window> main_window_;

	private:
		static void callbackError(const int code, const char* const message) noexcept;

	public:
		UserInterface() = delete;
		UserInterface(loser_scene::Scene* const scene_ref) noexcept(false);

		UserInterface(const UserInterface&) = delete;
		UserInterface(UserInterface&&) = delete;

		UserInterface& operator=(const UserInterface&) = delete;
		UserInterface& operator=(UserInterface&&) = delete;

		~UserInterface() noexcept;

	private:
#ifdef _DEBUG
		static void checkVersionGLFW() noexcept;
#endif
		static void setupInitializeHint() noexcept;

	public:
		void update() const noexcept;
		void createWidget() noexcept;

		void addRendererReference(loser_renderer::GLRenderer* const renderer) noexcept;
		void addWidget() noexcept;

		inline bool isEnable() const noexcept{
			if(monitors_.empty() || main_window_ == nullptr){
				return false;
			}
			return monitors_.front().isEnable() && main_window_->isEnable();
		}

		inline std::float_t getWindowWidth() const noexcept{
			return main_window_->getWidth();
		}
		inline std::float_t getWindowHeight() const noexcept{
			return main_window_->getHeight();
		}
	};
}