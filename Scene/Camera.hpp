#pragma once

#include "LoserMath.hpp"

namespace loser_scene{
	class Camera final{
	private:
		static constexpr const std::float_t RADIUS_MIN_ = 0.1;
		static constexpr const std::float_t RADIUS_MAX_ = 150.0;



		std::float_t radius_ = 20.0;
		std::float_t theta_ = std::numbers::pi / 3.0;
		std::float_t phi_ = std::numbers::pi / 3.0;


		loser_math::Vector<std::float_t, 3> viewpoint_{0.0, 0.0, 0.0};

		loser_math::Axis up_axis_ = loser_math::Axis::Z;

		loser_math::Matrix<std::float_t, 4, 4> projection_matrix_;
		loser_math::Matrix<std::float_t, 4, 4> view_matrix_;

	public:
		Camera() noexcept;

		Camera(const Camera&)	= delete;
		Camera(Camera&&)		= delete;

		Camera& operator=(const Camera&)	= delete;
		Camera& operator=(Camera&&)			= delete;

		~Camera() = default;

	public:
		//Event



		void computeProjectionMatrix(const std::float_t aspect) noexcept;

		void zoom(const std::float_t diff) noexcept;

		void move(const std::float_t x, const std::float_t y) noexcept;


		void moveViewPointVertical(const std::float_t y) noexcept;
		void moveViewPointHorizontal(const std::float_t x, const std::float_t y) noexcept;


		inline const std::float_t* const getProjectionMatrixData() const noexcept{
			return projection_matrix_.data()->data();
		}
		inline const std::float_t* const  getViewMatrixData() const noexcept{
			return view_matrix_.data()->data();
		}

		void update() noexcept{
			computeViewMatrix();
			return;
		}

	private:
		void computeViewMatrix() noexcept;

	};
}
