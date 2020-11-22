#pragma once

#include "Camera.hpp"
#include "Axes.hpp"

namespace loser_scene{
	class Scene final{
	private:
		Camera	main_camera_;
		Axes	axes_;

	public:
		Scene() = default;

		Scene(const Scene&) = delete;
		Scene(Scene&&)		= delete;

		Scene& operator=(const Scene&)	= delete;
		Scene& operator=(Scene&&)		= delete;

		~Scene() = default;

	public:







		void zoomCamera(const std::float_t x) noexcept;

		void moveCamera(const std::float_t x, const std::float_t y) noexcept;
		void moveViewPointVertical(const std::float_t y) noexcept;
		void moveViewPointHorizontal(const std::float_t x, const std::float_t y) noexcept;
		void computeProjectionMatrix(const std::float_t width, const std::float_t height) noexcept;
	private:


	public:
		inline const std::float_t* const getProjectionMatrixData() const noexcept{
			return main_camera_.getProjectionMatrixData();
		}
		inline const std::float_t* const  getViewMatrixData() const noexcept{
			return main_camera_.getViewMatrixData();
		}

		inline const loser_math::RealNumber* const getAxesData() const noexcept{
			return axes_.getData();
		}


		void update() noexcept{
			main_camera_.update();
			return;
		}

	};
}
