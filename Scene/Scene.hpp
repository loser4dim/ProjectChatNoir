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







		void zoomCamera(const loser_math::RealNumber x) noexcept;

		void moveCamera(const loser_math::RealNumber x, const loser_math::RealNumber y) noexcept;
		void moveViewPointVertical(const loser_math::RealNumber y) noexcept;
		void moveViewPointHorizontal(const loser_math::RealNumber x, const loser_math::RealNumber y) noexcept;
		void computeProjectionMatrix(const loser_math::RealNumber width, const loser_math::RealNumber height) noexcept;
	private:


	public:
		inline const loser_math::RealNumber* const getProjectionMatrixData() const noexcept{
			return main_camera_.getProjectionMatrixData();
		}
		inline const loser_math::RealNumber* const  getViewMatrixData() const noexcept{
			return main_camera_.getViewMatrixData();
		}

		inline const loser_math::RealNumber* const getAxesData() const noexcept{
			return axes_.getData();
		}


	};
}
