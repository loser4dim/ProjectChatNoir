#pragma once

#include "LoserMath.hpp"

namespace loser_scene{
	class Camera final{
	private:
		static constexpr const loser_math::RealNumber RADIUS_MIN_ = 1.0;
		static constexpr const loser_math::RealNumber RADIUS_MAX_ = 150.0;



		loser_math::RealNumber radius_ = 10.0;
		loser_math::RealNumber theta_ = loser_math::PI / 6.0;
		loser_math::RealNumber phi_ = loser_math::PI / 3.0;


		loser_math::Vector3D viewpoint_{0.0, 0.0, 0.0};

		loser_math::Axis up_axis_ = loser_math::Axis::Z;

		loser_math::Matrix4D projection_matrix_;
		loser_math::Matrix4D view_matrix_;

	public:
		Camera() noexcept;

		Camera(const Camera&)	= delete;
		Camera(Camera&&)		= delete;

		Camera& operator=(const Camera&)	= delete;
		Camera& operator=(Camera&&)			= delete;

		~Camera() = default;

	public:
		//Event



		void computeProjectionMatrix(const loser_math::RealNumber aspect) noexcept;

		void zoom(const loser_math::RealNumber diff) noexcept;

		void move(const loser_math::RealNumber x, const loser_math::RealNumber y) noexcept;


		void moveViewPointVertical(const loser_math::RealNumber y) noexcept;
		void moveViewPointHorizontal(const loser_math::RealNumber x, const loser_math::RealNumber y) noexcept;


		inline const loser_math::RealNumber* const getProjectionMatrixData() const noexcept{
			return projection_matrix_.data()->data();
		}
		inline const loser_math::RealNumber* const  getViewMatrixData() const noexcept{
			return view_matrix_.data()->data();
		}

	private:
		void computeViewMatrix() noexcept;

	};
}
