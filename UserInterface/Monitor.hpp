#pragma once

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#pragma comment(lib, "glfw3")

#include <memory>

namespace loser_ui{
	//Functor for std::unique_ptr<GLFWmonitor>
	struct MonitorDestoryer final{
	public:
		inline constexpr void operator()(GLFWmonitor* const monitor) const noexcept{
			if(monitor != nullptr){
			}
			return;
		}
	};

	class Monitor final{
	private:
		static constexpr const float GAMMA_VALUE_ = 1.0f;

		std::unique_ptr<GLFWmonitor, const MonitorDestoryer> fw_ptr_ = nullptr;

		int		width_				= 0; //[-]
		int		height_				= 0; //[-]

		int		red_bit_depth_		= 0; //[bit]
		int		green_bit_depth_	= 0; //[bit]
		int		blue_bit_depth_		= 0; //[bit]

		int		refresh_rate_		= 0; //[/s]

		bool	is_enable_			= false;

	private:
		//Event Callback
		static void callbackMonitor(GLFWmonitor* const monitor, const int is_connected) noexcept;

	public:
		Monitor() = delete;
		explicit Monitor(GLFWmonitor* const new_monitor) noexcept(false);

		Monitor(const Monitor&) = delete;
		Monitor(Monitor&&)		= default;

		Monitor& operator=(const Monitor&)	= delete;
		Monitor& operator=(Monitor&&)		= delete;

		~Monitor() noexcept;

#ifdef _DEBUG
	private:
		static bool reportMonitorInfo(GLFWmonitor* const monitor) noexcept;
#endif
	public:
		inline int getWidth() const noexcept{
			return width_;
		}
		inline int getHeight() const noexcept{
			return height_;
		}
		inline int getRedBitDepth() const noexcept{
			return red_bit_depth_;
		}
		inline int getGreenBitDepth() const noexcept{
			return green_bit_depth_;
		}
		inline int getBlueBitDepth() const noexcept{
			return blue_bit_depth_;
		}
		inline int getRefreshRate() const noexcept{
			return refresh_rate_;
		}
		inline constexpr bool isEnable() const noexcept{
			return is_enable_;
		}
	};
}
