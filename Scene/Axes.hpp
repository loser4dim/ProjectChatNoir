#pragma once

#include "LoserMath.hpp"
#include <array>

namespace loser_scene{
	class Axes final{
	private:
		static constexpr const loser_math::RealNumber LENGTH_ = 150.0;

		

		std::array<loser_math::Vector3D, 4> vertices_{
			loser_math::Vector3D{0.0, 0.0, 0.0},
			loser_math::Vector3D{LENGTH_, 0.0, 0.0},
			loser_math::Vector3D{0.0, LENGTH_, 0.0},
			loser_math::Vector3D{0.0, 0.0, LENGTH_}
		};

		std::array<std::array<std::size_t, 2>, 3> lines{
			{
				{0, 1},
				{0, 2},
				{0, 3}
			}
		};

		static constexpr const std::array<loser_math::RealNumber, 18> data{
				0.0, 0.0, 0.0,
				LENGTH_, 0.0, 0.0,
				0.0, 0.0, 0.0,
				0.0, LENGTH_, 0.0,
				0.0, 0.0, 0.0,
				0.0, 0.0, LENGTH_
		};
	public:
		inline const loser_math::RealNumber* const getData() const noexcept{
			return data.data();
		}
	};
}