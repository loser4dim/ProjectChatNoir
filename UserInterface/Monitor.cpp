#include "Monitor.hpp"

#include <string>
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

namespace loser_ui{
	void Monitor::callbackMonitor(GLFWmonitor* const monitor, const int is_connected) noexcept{
		if(monitor == nullptr){
			return;
		}
		Monitor* const current_monitor = static_cast<Monitor* const>(glfwGetMonitorUserPointer(monitor));
		if(current_monitor == nullptr){
			return;
		}

		if(is_connected == GLFW_CONNECTED){
			current_monitor->is_enable_ = true;
		}
		else{
			current_monitor->is_enable_ = false;
		}
#ifdef _DEBUG
		if(is_connected == GLFW_CONNECTED){
			std::clog << "monitor is Connected." << std::endl;
		}
		else if(is_connected == GLFW_DISCONNECTED){
			std::clog << "monitor is Disconnected." << std::endl;
		}
		else{
			std::cerr << "Monitor Connection Error!" << std::endl;
		}
#endif
		return;
	}

	Monitor::Monitor(GLFWmonitor* const new_monitor) noexcept(false){
		if(new_monitor == nullptr){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Create GLFW Monitor Instance."));
		}
#ifdef _DEBUG
		if(!Monitor::reportMonitorInfo(new_monitor)){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Create GLFW Monitor Instance."));
		}
#endif
		glfwSetMonitorCallback(Monitor::callbackMonitor);
		glfwSetGamma(new_monitor, Monitor::GAMMA_VALUE_);
		glfwSetMonitorUserPointer(new_monitor, this);

		const GLFWvidmode* const video_mode = glfwGetVideoMode(new_monitor);
		width_				= video_mode->width;
		height_				= video_mode->height;

		red_bit_depth_		= video_mode->redBits;
		green_bit_depth_	= video_mode->greenBits;
		blue_bit_depth_		= video_mode->blueBits;

		refresh_rate_		= video_mode->refreshRate;

		fw_ptr_.reset(new_monitor);
		is_enable_			= true;
	}

	Monitor::~Monitor() noexcept{
		fw_ptr_.release();
	}

#ifdef _DEBUG
	bool Monitor::reportMonitorInfo(GLFWmonitor* const monitor) noexcept{
		if(monitor == nullptr){
			return false;
		}

		//Get Monitor Name
		std::clog << "Monitor Infomation" << std::endl;
		std::clog << "\t" << "Name         : " << glfwGetMonitorName(monitor) << std::endl;

		//Get Monitor Physical Size
		int physical_width	= 0;
		int physical_height = 0;
		glfwGetMonitorPhysicalSize(monitor, &physical_width, &physical_height);
		std::clog << "\t" << "Physical Size: " << "(" << physical_width << "[mm], " << physical_height << "[mm])" << std::endl;

		//Get Monitor Virtual Workarea
		int pos_x	= 0;
		int pos_y	= 0;
		int width	= 0;
		int height	= 0;
		glfwGetMonitorWorkarea(monitor, &pos_x, &pos_y, &width, &height);
		std::clog << "\t" << "Position     : " << "(" << pos_x << ", " << pos_y << ")" << std::endl;
		std::clog << "\t" << "Size         : " << "(" << width << ", " << height << ")" << std::endl;

		//Get Content Scale
		float scale_x = 0.0f;
		float scale_y = 0.0f;
		glfwGetMonitorContentScale(monitor, &scale_x, &scale_y);
		std::clog << "\t" << "Content Scale: " << "(" << scale_x << ", " << scale_y << ")" << std::endl;

		return true;
	}
#endif
}