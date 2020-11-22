#include "Camera.hpp"



namespace loser_scene{
	Camera::Camera() noexcept{
	}

	void Camera::computeProjectionMatrix(const std::float_t aspect) noexcept{
		constexpr const std::float_t FOVY = std::numbers::pi / 3.0f;

		const std::float_t f = 1.0 / std::tan(FOVY / 2.0);


		const std::float_t NEAR = 0.1f;
		const std::float_t FAR = 1000.0f;

		/*projection_matrix_ = loser_math::Matrix<std::float_t, 4, 4>{
			loser_math::Vector<std::float_t, 4>{f / aspect, 0.0f, 0.0f, 0.0f},
			loser_math::Vector<std::float_t, 4>{0.0f, f, 0.0f, 0.0f},
			loser_math::Vector<std::float_t, 4>{0.0f, 0.0f, -(FAR + NEAR) / (FAR - NEAR), -2.0f * FAR * NEAR / (FAR - NEAR)},
			loser_math::Vector<std::float_t, 4>{0.0f, 0.0f,  -1.0f, 0.0f}
		};*/
		
		projection_matrix_ = loser_math::Matrix<std::float_t, 4, 4>{
			loser_math::Vector<std::float_t, 4>{f / aspect, 0.0f, 0.0f, 0.0f},
			loser_math::Vector<std::float_t, 4>{0.0f, f, 0.0f, 0.0f},
			loser_math::Vector<std::float_t, 4>{0.0f, 0.0f, -(FAR + NEAR) / (FAR - NEAR), -2.0f * FAR * NEAR / (FAR - NEAR)},
			loser_math::Vector<std::float_t, 4>{0.0f, 0.0f, -1.0f, 0.0f}
		};

		/*projection_matrix_ = loser_math::Matrix<std::float_t, 4, 4>{
			loser_math::Vector<std::float_t, 4>{-1.0f, 0.0f, 0.0f, 0.0f},
			loser_math::Vector<std::float_t, 4>{0.0, -1.0f, 0.0f, 0.0f},
			loser_math::Vector<std::float_t, 4>{0.0f, 0.0f, 0.0f, 1.0},
			loser_math::Vector<std::float_t, 4>{0.0, 0.0, -1.0, 0.0}
		};*/

		return;
	}


	void Camera::computeViewMatrix() noexcept{
		
		/*const loser_math::Vector<std::float_t, 3> positionk{
			radius_ * std::sin(theta_) * std::cos(phi_) + viewpoint_[loser_math::Axis::X],
			radius_ * std::sin(theta_) * std::sin(phi_) + viewpoint_[loser_math::Axis::Y],
			radius_ * std::cos(theta_) + viewpoint_[loser_math::Axis::Z]
		};

		const loser_math::Vector<std::float_t, 3> up_vectork{0.0f, 0.0f, 1.0f};

		const loser_math::Vector<std::float_t, 3> f = normalize<std::float_t, 3>(viewpoint_ - positionk);
		const loser_math::Vector<std::float_t, 3> s = normalize<std::float_t, 3>(cross(f, up_vectork));
		const loser_math::Vector<std::float_t, 3> u = normalize(cross(s, f));

		view_matrix_ = loser_math::Matrix<std::float_t, 4, 4>{
			loser_math::Vector<std::float_t, 4>{s[0],						u[0],						-f[0],						0.0f},
			loser_math::Vector<std::float_t, 4>{s[1],						u[1],						-f[1],						0.0f},
			loser_math::Vector<std::float_t, 4>{s[2],						u[2],						-f[2],						0.0f},
			loser_math::Vector<std::float_t, 4>{-dot(s, positionk), -dot(u, positionk),	dot(f, positionk),	1.0f}
		};
		std::clog << "-----------------" << std::endl;
		std::clog << view_matrix_ << std::endl;*/
		
		const loser_math::Vector<std::float_t, 3> position{
			radius_ * std::sin(theta_) * std::cos(phi_) + viewpoint_[loser_math::Axis::X],
			radius_ * std::sin(theta_) * std::sin(phi_) + viewpoint_[loser_math::Axis::Y],
			radius_ * std::cos(theta_) + viewpoint_[loser_math::Axis::Z]
		};
		const loser_math::Vector<std::float_t, 3> up_vector{0.0f, 0.0f, 1.0f};

		const loser_math::Vector<std::float_t, 3> new_z = normalize(viewpoint_ - position);
		const loser_math::Vector<std::float_t, 3> new_x = normalize(cross(new_z, up_vector));
		const loser_math::Vector<std::float_t, 3> new_y = normalize(cross(new_x, new_z));
		

		view_matrix_ = loser_math::Matrix<std::float_t, 4, 4>{
			loser_math::Vector<std::float_t, 4>{new_x[0], new_x[1], new_x[2], -dot(position, new_x)},
			loser_math::Vector<std::float_t, 4>{new_y[0], new_y[1], new_y[2], -dot(position, new_y)},
			loser_math::Vector<std::float_t, 4>{-new_z[0], -new_z[1], -new_z[2], -dot(position, -new_z)},
			loser_math::Vector<std::float_t, 4>{0.0f, 0.0f, 0.0f, 1.0f}
		};
		
		//std::clog << view_matrix_ << std::endl;

		/*std::clog << projection_matrix_ * view_matrix_ *  loser_math::Vector<std::float_t, 4>{1.0, 0.0, 0.0, 1.0} << std::endl;
		std::clog << projection_matrix_ * view_matrix_ * loser_math::Vector<std::float_t, 4>{0.0, 1.0, 0.0, 1.0} << std::endl;
		std::clog << projection_matrix_ * view_matrix_ * loser_math::Vector<std::float_t, 4>{0.0, 0.0, 1.0, 1.0} << std::endl;*/



		return;
	}

	void Camera::zoom(const std::float_t diff) noexcept{
		constexpr const std::float_t SPEED = 0.11f;
		radius_ += SPEED * diff;
		if(radius_ < RADIUS_MIN_){
			radius_ = RADIUS_MIN_;
		}
		else if(radius_ > RADIUS_MAX_){
			radius_ = RADIUS_MAX_;
		}

		return;
	}

	void Camera::move(const std::float_t horizontal, const std::float_t vertical) noexcept{
		constexpr const std::float_t SPEED = 0.001f;
		theta_ -= SPEED * vertical;

		if(theta_ > std::numbers::pi - std::numeric_limits<std::float_t>::epsilon()){
			theta_ = std::numbers::pi - std::numeric_limits<std::float_t>::epsilon();
		}
		else if(theta_ < std::numeric_limits<std::float_t>::epsilon()){
			theta_ = std::numeric_limits<std::float_t>::epsilon();
		}

		phi_ -= SPEED * horizontal;
		if(phi_ > 2.0 * std::numbers::pi){
			phi_ -= 2.0 * std::numbers::pi;
		}
		else if(phi_ < 0.0){
			phi_ += 2.0 * std::numbers::pi;
		}


		return;
	}


	void Camera::moveViewPointVertical(const std::float_t diff) noexcept{
		constexpr const std::size_t SPACE_DIM_ = 3;

		viewpoint_[up_axis_ % SPACE_DIM_] += radius_ * diff;


		return;
	}

	void Camera::moveViewPointHorizontal(const std::float_t x, const std::float_t y) noexcept{
		constexpr const std::size_t SPACE_DIM_ = 3;

		viewpoint_[(up_axis_ + 1) % SPACE_DIM_] += radius_ * (x * std::sin(phi_) - y * std::cos(phi_));
		viewpoint_[(up_axis_ + 2) % SPACE_DIM_] += radius_ * (-x * std::cos(phi_) - y * std::sin(phi_));

		return;
	}
}