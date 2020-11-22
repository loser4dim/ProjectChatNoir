#pragma once

#include "Monitor.hpp"
#include "Window.hpp"
#include <vector>

namespace loser_ui{
	class UserInteraface final{
	private:
		std::vector<Monitor> monitors_;
		std::unique_ptr<Window> main_window_;


	private:
		static void callbackError(const int code, const char* const message) noexcept;

	public:
		UserInteraface() = delete;
		UserInteraface(loser_scene::Scene* const scene_ref) noexcept(false);

		UserInteraface(const UserInteraface&) = delete;
		UserInteraface(UserInteraface&&) = delete;

		UserInteraface& operator=(const UserInteraface&) = delete;
		UserInteraface& operator=(UserInteraface&&) = delete;

		~UserInteraface() noexcept(false){
			main_window_.release();
			monitors_.clear();
			glfwTerminate();
		}

	private:
#ifdef _DEBUG
		static void checkVersionGLFW() noexcept;
#endif
		static void setupInitializeHint() noexcept;

	public:
		void createWidget() noexcept{
			if(main_window_ != nullptr){
				main_window_->createWidget();
			}
		}

		void addWidget(loser_renderer::GLRenderer* const renderer){
			if(main_window_ != nullptr){
				main_window_->addWidget(renderer);
			}
		}

		void update() const noexcept{
			if(main_window_ != nullptr){
				main_window_->update();
			}
			glfwPollEvents();
			return;
		}

		inline bool isEnable() const noexcept{
			if(monitors_.empty() || main_window_ == nullptr){
				return false;
			}
			return monitors_.front().isEnable() && main_window_->isEnable();
		}
	};
}