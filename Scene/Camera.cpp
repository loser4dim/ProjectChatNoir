#include "Camera.hpp"



namespace loser_scene{
	Camera::Camera() noexcept{
		computeViewMatrix();
		computeProjectionMatrix(1.0);
	}

	void Camera::computeProjectionMatrix(const loser_math::RealNumber aspect) noexcept{
		constexpr const loser_math::RealNumber FOVY = loser_math::PI / 6.0;
		constexpr const loser_math::RealNumber NEAR = 0.1;
		constexpr const loser_math::RealNumber FAR = 1000.0;

		const loser_math::RealNumber f = 1.0 / std::tan(static_cast<std::double_t>(FOVY) / 2.0);

		projection_matrix_ = loser_math::Matrix4D{
			loser_math::Vector4D{f, 0.0, 0.0, 0.0},
			loser_math::Vector4D{0.0, f * aspect, 0.0, 0.0},
			loser_math::Vector4D{0.0, 0.0, (FAR + NEAR) / (FAR - NEAR), -1.0},
			loser_math::Vector4D{0.0, 0.0, -2.0 * FAR * NEAR / (FAR - NEAR), 0.0}
		};

		std::cout << view_matrix_ << std::endl;
		std::cout << projection_matrix_ << std::endl;

		return;
	}

	void Camera::computeViewMatrix() noexcept{
		
		const loser_math::Vector3D position{
			radius_ * std::sin(static_cast<double_t>(theta_)) * std::cos(static_cast<double_t>(phi_)) + viewpoint_[loser_math::Axis::X],
			radius_ * std::sin(static_cast<double_t>(theta_)) * std::sin(static_cast<double_t>(phi_)) + viewpoint_[loser_math::Axis::Y],
			radius_ * std::cos(static_cast<double_t>(theta_)) + viewpoint_[loser_math::Axis::Z]
		};

		const loser_math::Vector3D up_vector = loser_math::Vector3D::UNIT(up_axis_);

		const loser_math::Vector3D f = normalize(viewpoint_ - position);
		const loser_math::Vector3D s = normalize(cross(f, up_vector));
		const loser_math::Vector3D u = cross(s, f);

		view_matrix_ = loser_math::Matrix4D{
			loser_math::Vector4D{s[0],						u[0],						-f[0],						0.0f},
			loser_math::Vector4D{s[1],						u[1],						-f[1],						0.0f},
			loser_math::Vector4D{s[2],						u[2],						-f[2],						0.0f},
			loser_math::Vector4D{-dot(s, position), -dot(u, position),	dot(f, position),	1.0f}
		};

		return;
	}

	void Camera::zoom(const loser_math::RealNumber diff) noexcept{
		radius_ += diff;
		if(radius_ < RADIUS_MIN_){
			radius_ = RADIUS_MIN_;
		}
		else if(radius_ > RADIUS_MAX_){
			radius_ = RADIUS_MAX_;
		}
		return;
	}

	void Camera::move(const loser_math::RealNumber horizontal, const loser_math::RealNumber vertical) noexcept{
		theta_ += vertical;
		if(theta_ > loser_math::PI){
			theta_ = loser_math::PI - loser_math::EPSILON;
		}
		else if(theta_ < 0.0){
			theta_ = 0.0;
		}

		phi_ += horizontal;
		if(phi_ > 2.0 * loser_math::PI){
			phi_ -= 2.0 * loser_math::PI;
		}
		else if(phi_ < 0.0){
			phi_ += 2.0 * loser_math::PI;
		}

		return;
	}


	void Camera::moveViewPointVertical(const loser_math::RealNumber diff) noexcept{
		constexpr const std::size_t SPACE_DIM_ = 3;

		viewpoint_[up_axis_ % SPACE_DIM_] += radius_ * diff;

		return;
	}

	void Camera::moveViewPointHorizontal(const loser_math::RealNumber x, const loser_math::RealNumber y) noexcept{
		constexpr const std::size_t SPACE_DIM_ = 3;

		viewpoint_[(up_axis_ + 1) % SPACE_DIM_] += radius_ * (x * std::sin(static_cast<std::double_t >(phi_)) - y * std::cos(static_cast<std::double_t>(phi_)));
		viewpoint_[(up_axis_ + 2) % SPACE_DIM_] += radius_ * (-x * std::cos(static_cast<std::double_t>(phi_)) - y * std::sin(static_cast<std::double_t>(phi_)));

		return;
	}
}