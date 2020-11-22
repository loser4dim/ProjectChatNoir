#include "UserInterface.hpp"

#include <string>
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

namespace loser_ui{
	void UserInterface::callbackError(const int code, const char* const message) noexcept{
#ifdef _DEBUG
		std::string error(message);
		//TODO: Have to Convert UTF-8 => Shift-Jis
		std::cerr << "Error Code " << code << ": " << error << std::endl;
#endif
		return;
	}

	UserInterface::UserInterface(loser_scene::Scene* const scene_ref) noexcept(false){
#ifdef _DEBUG
		UserInterface::checkVersionGLFW();
#endif
		UserInterface::setupInitializeHint();

		glfwSetErrorCallback(UserInterface::callbackError);
#ifdef _DEBUG
		if(glfwInit() != GLFW_TRUE){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Initialize GLFW."));
		}
#endif

		int monitor_num = 0;
		GLFWmonitor* const* const new_monitors = glfwGetMonitors(&monitor_num);
		if(new_monitors == nullptr && monitor_num != 0){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "NOT Founded Monitors."));
		}
		for(int i = 0; i < monitor_num; ++i){
			monitors_.push_back(Monitor(new_monitors[i]));
		}

		const bool vulkan_support = (glfwVulkanSupported() == GLFW_TRUE);
		const Monitor& primary = monitors_.front();
		//Now Vulkan is NOT Enable
		//main_window_ = std::make_unique<Window>(primary.getWidth(), primary.getHeight(), primary.getRedBitDepth(), primary.getGreenBitDepth(), primary.getBlueBitDepth(), primary.getRefreshRate(), glfwCreateStandardCursor(GLFW_ARROW_CURSOR), scene_ref, vulkan_support);
		main_window_ = std::make_unique<Window>(primary.getWidth(), primary.getHeight(), primary.getRedBitDepth(), primary.getGreenBitDepth(), primary.getBlueBitDepth(), primary.getRefreshRate(), glfwCreateStandardCursor(GLFW_ARROW_CURSOR), scene_ref);
	}

	UserInterface::~UserInterface() noexcept{
		main_window_.release();
		monitors_.clear();
		glfwTerminate();
	}

#ifdef _DEBUG
	void UserInterface::checkVersionGLFW() noexcept{
		int glfw_major = 0;
		int glfw_minor = 0;
		int glfw_revision = 0;
		glfwGetVersion(&glfw_major, &glfw_minor, &glfw_revision);
		std::clog << "GLFW Version: " << glfw_major << "." << glfw_minor << "." << glfw_revision << std::endl;
		return;
	}
#endif

	void UserInterface::setupInitializeHint() noexcept{
		glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_TRUE);
#ifdef __APPLE__
		glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
		glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);
#endif
		return;
	}

	void UserInterface::update() const noexcept{
		if(main_window_ != nullptr){
			main_window_->update();
		}
		return;
	}

	void UserInterface::createWidget() noexcept{
		if(main_window_ != nullptr){
			main_window_->createWidget();
		}
		return;
	}

	void UserInterface::addRendererReference(loser_renderer::GLRenderer* const renderer) noexcept{
		if(main_window_ != nullptr){
			main_window_->addRendererReference(renderer);
		}
		return;
	}

	void UserInterface::addWidget() noexcept{
		if(main_window_ != nullptr){
			main_window_->addWidget();
		}
		return;
	}
}